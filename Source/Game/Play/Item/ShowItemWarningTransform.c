#include "Game/Play/Item/ShowItemWarningTransform.h"
#include "Game/Graphics/Entity.h"
#include "Game/Graphics/DisplayObject.h"
#include "Main/Frame.h"

#define warningFrames values[0]

static void UpdateEntityItemWarningTransform(Entity* entity);

void ShowItemWarningTransform(Player* player) {
	Entity* entity;
	if ((entity = AllocEntity()) != NULL) {
		entity->update = UpdateEntityItemWarningTransform;
		entity->data.unionData.player = player;
		ENTITY_INST_DATA_PTR(BasicEntityInstanceData, data, entity);
		entity->warningFrames = 0;
		data->x = 4;
		data->x =
			player->screenPos[0] + player->screenOffset[0] -
			(player->matrixWidth / 2) * 8 + (data->x + 2) * 8;
		data->y = player->screenPos[1] + player->screenOffset[1] - 96;
		data->objectTable = OBJECTTABLE_ITEMWARNINGTRANSFORM;
		data->palNum = 183u;
	}
}

static void UpdateEntityItemWarningTransform(Entity* entity) {
	STATIC_ASSERT(sizeof(BasicEntityInstanceData) <= sizeoffield(Entity, buffer));

	ENTITY_INST_DATA_PTR(BasicEntityInstanceData, data, entity);
	DisplayObject(&data->objectTable[entity->warningFrames], data->y, data->x, (uint8_t)data->palNum, 124u);

	if (CurrentPauseMode < PAUSEMODE_GAME && ++entity->warningFrames >= 64) {
		FreeEntity(entity);
	}
}
