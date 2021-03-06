#include "Game/Play/Item/UpdateItemNegaField.h"
#include "Game/Play/Item/ShowItemWarningNegaField.h"
#include "Game/Play/Player.h"
#include "Game/Play/Matrix.h"
#include "Game/Graphics/ShowBlockField.h"
#include "Sound/Sound.h"

enum NegaFieldState {
	STATE_START,
	STATE_DELAY,
	STATE_INIT,
	STATE_NEGAFIELD,
	STATE_CHECKLOCKBLOCK,
	STATE_DELAYDEACTIVATE,
	STATE_DEACTIVATE
};

typedef struct NegaFieldData {
	int16_t topNegaRow;
} NegaFieldData;

// STATE_DELAY
#define initRowFrames values[0]

// STATE_NEGAFIELD
#define negaRowFrames values[0]
#define negaRow values[1]

// STATE_DELAYDEACTIVATE
#define deactivateFrames values[1]

// STATE_DEACTIVATE
#define forceLockBlock values[0]

void UpdateItemNegaField(Item* item) {
	STATIC_ASSERT(sizeof(NegaFieldData) <= sizeoffield(Item, data));

	Player* activatingPlayer = item->activatingPlayer;
	Player* itemPlayer = activatingPlayer->itemPlayer;
	NegaFieldData* data = (NegaFieldData*)item->data;

	if (!CheckDeactivateItem(item)) {
		switch (item->states[0]) {
		case STATE_START:
			RemoveItems(activatingPlayer);
			if (!(itemPlayer->nowFlags & NOW_LOCKING) && activatingPlayer->activeItemType == ITEMTYPE_NULL && !ItemGood(itemPlayer)) {
				activatingPlayer->activeItemType = ITEMTYPE_NEGAFIELD;
				SetFieldBorderColor(itemPlayer, ITEMTYPE_NEGAFIELD);
				ShowItemWarningNegaField(itemPlayer);
				PlaySoundEffect(SOUNDEFFECT_BADITEM);
				itemPlayer->play.flags |= PLAYFLAG_FORCEENTRY;
				itemPlayer->nowFlags |= NOW_NOGARBAGE;
				item->initRowFrames = 60;
				item->states[0]++;
			}
			break;

		case STATE_DELAY:
			if (--item->initRowFrames == 0) {
				item->states[0]++;
			}
			break;

		case STATE_INIT:
			// Erase top row.
			for (int16_t col = 1; col < MATRIX_SINGLEWIDTH; col++) {
				MatrixBlock* matrixBlock = &MATRIX(activatingPlayer, MATRIX_HEIGHT - 1, col);
				matrixBlock->block = NULLBLOCK;
				matrixBlock->itemType = ITEMTYPE_NULL;
			}
			// Find highest row with blocks, for the next nega row.
			for (int16_t row = 1; row < MATRIX_HEIGHT - 1; row++) {
				for (int16_t col = 1; col < MATRIX_SINGLEWIDTH - 1; col++) {
					if ((MATRIX(activatingPlayer, row, col).block & BLOCK_TYPE) != BLOCKTYPE_EMPTY) {
						data->topNegaRow = row;
					}
				}
			}

			if (data->topNegaRow < 1) {
				item->deactivateFrames = 40;
				item->states[0] = STATE_DELAYDEACTIVATE;
			}
			else {
				item->negaRowFrames = 1;
				item->negaRow = 1;
				PlaySoundEffect(SOUNDEFFECT_SELECT);
				item->states[0]++;
			}
			break;

		case STATE_NEGAFIELD:
			if (item->negaRowFrames % 4 == 0) {
				PlaySoundEffect(SOUNDEFFECT_SELECT);
				for(int16_t col = 1; col < MATRIX_SINGLEWIDTH - 1; col++) {
					MatrixBlock* matrixBlock = &MATRIX(itemPlayer, item->negaRow, col);
					if (!(matrixBlock->block & BLOCK_ITEM)) {
						if ((matrixBlock->block & BLOCK_TYPE) != BLOCKTYPE_EMPTY) {
							matrixBlock->block = NULLBLOCK;
						}
						else {
							matrixBlock->block = (Block)TOBLOCKTYPE(item->negaRow % 7);
							if (activatingPlayer->modeFlags & MODE_INVISIBLE) {
								matrixBlock->block |= BLOCK_FADING;
							}
							if (activatingPlayer->grade == PLAYERGRADE_M) {
								matrixBlock->visibleFrames = 45;
							}
							else {
								matrixBlock->visibleFrames = 300;
							}
						}
					}
				}
				item->negaRow++;
			}
			item->negaRowFrames++;
			if (item->negaRow > data->topNegaRow) {
				PlaySoundEffect(SOUNDEFFECT_SELECT);
				item->states[0]++;
			}
			break;

		case STATE_CHECKLOCKBLOCK:
			item->forceLockBlock = false;
			for (int16_t row = 1; row < MATRIX_HEIGHT - 1; row++) {
				int16_t col;
				for (col = 1; col < MATRIX_SINGLEWIDTH - 1; col++) {
					if ((MATRIX(itemPlayer, row, col).block & BLOCK_TYPE) == BLOCKTYPE_EMPTY) {
						break;
					}
				}
				if (col >= MATRIX_SINGLEWIDTH - 1) {
					item->forceLockBlock = true;
				}
			}
			item->states[0]++;
			item->deactivateFrames = 40;
			break;

		case STATE_DELAYDEACTIVATE:
			if (--item->deactivateFrames == 0) {
				item->states[0]++;
			}
			break;

		case STATE_DEACTIVATE:
		default:
			itemPlayer->nowFlags &= ~NOW_NOGARBAGE;
			itemPlayer->play.flags &= ~PLAYFLAG_FORCEENTRY;
			if (item->forceLockBlock) {
				itemPlayer->play.flags |= PLAYFLAG_FORCEENTRY;
				NextPlayLock(itemPlayer);
			}
			item->states[0]++;
			activatingPlayer->activeItemType = ITEMTYPE_NULL;
			SetFieldBorderColor(itemPlayer, ITEMTYPE_NULL);
			DeactivateItem(item);
			break;
		}
	}
}
