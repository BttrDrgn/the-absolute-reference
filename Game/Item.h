#pragma once

#include "Macros.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum ItemType {
	ITEMTYPE_NULL,
	ITEMTYPE_DEATHBLOCK,
	ITEMTYPE_NEGAFIELD,
	ITEMTYPE_COLORBLOCK,
	ITEMTYPE_TOPDELFIELD,
	ITEMTYPE_BOTTOMDELFIELD,
	ITEMTYPE_RIGHTMOVFIELD,
	ITEMTYPE_LEFTMOVFIELD,
	ITEMTYPE_DELEVEN,
	ITEMTYPE_180DEGREEFIELD,
	ITEMTYPE_SHOTGUN,
	ITEMTYPE_HARDBLOCK,
	ITEMTYPE_LASER,
	ITEMTYPE_ROLLROLL,
	ITEMTYPE_TRANSFORM,
	ITEMTYPE_FREEFALL,
	ITEMTYPE_XRAY,
	ITEMTYPE_EXCHGFIELD,
	ITEMTYPE_MIRRORBLOCK,
	ITEMTYPE_DARKBLOCK,
	NUMITEMTYPES = ITEMTYPE_DARKBLOCK,
	ITEMTYPE_GAMEOVER = 0xFF // Not actually an item.
} ItemType;
#define TOITEMNUM(itemType) ((uint8_t)((itemType) - 1))
#define TOITEMTYPE(itemNum) ((ItemType)((itemNum) + 1))

typedef enum ItemMiscFlag {
	ITEMMISC_NONE,
	ITEMMISC_DEATHBLOCK = 1 << 0,
	ITEMMISC_ROTATE = 1 << 1,
	ITEMMISC_BIT10 = 1 << 10
} ItemMiscFlag;

typedef enum ItemBagFlag {
	ITEMBAG_NONE = 0x00000,
	ITEMBAG_DEATHBLOCK = 1 << TOITEMNUM(ITEMTYPE_DEATHBLOCK),
	ITEMBAG_NEGAFIELD = 1 << TOITEMNUM(ITEMTYPE_NEGAFIELD),
	ITEMBAG_COLORBLOCK = 1 << TOITEMNUM(ITEMTYPE_COLORBLOCK),
	ITEMBAG_TOPDELFIELD = 1 << TOITEMNUM(ITEMTYPE_TOPDELFIELD),
	ITEMBAG_BOTTOMDELFIELD = 1 << TOITEMNUM(ITEMTYPE_BOTTOMDELFIELD),
	ITEMBAG_RIGHTMOVFIELD = 1 << TOITEMNUM(ITEMTYPE_RIGHTMOVFIELD),
	ITEMBAG_LEFTMOVFIELD = 1 << TOITEMNUM(ITEMTYPE_LEFTMOVFIELD),
	ITEMBAG_DELEVEN = 1 << TOITEMNUM(ITEMTYPE_DELEVEN),
	ITEMBAG_180DEGREEFIELD = 1 << TOITEMNUM(ITEMTYPE_180DEGREEFIELD),
	ITEMBAG_SHOTGUN = 1 << TOITEMNUM(ITEMTYPE_SHOTGUN),
	ITEMBAG_HARDBLOCK = 1 << TOITEMNUM(ITEMTYPE_HARDBLOCK),
	ITEMBAG_LASER = 1 << TOITEMNUM(ITEMTYPE_LASER),
	ITEMBAG_ROLLROLL = 1 << TOITEMNUM(ITEMTYPE_ROLLROLL),
	ITEMBAG_TRANSFORM = 1 << TOITEMNUM(ITEMTYPE_TRANSFORM),
	ITEMBAG_FREEFALL = 1 << TOITEMNUM(ITEMTYPE_FREEFALL),
	ITEMBAG_XRAY = 1 << TOITEMNUM(ITEMTYPE_XRAY),
	ITEMBAG_EXCHGFIELD = 1 << TOITEMNUM(ITEMTYPE_EXCHGFIELD),
	ITEMBAG_MIRRORBLOCK = 1 << TOITEMNUM(ITEMTYPE_MIRRORBLOCK),
	ITEMBAG_DARKBLOCK = 1 << TOITEMNUM(ITEMTYPE_DARKBLOCK),
	ITEMBAG_FULL = 0x7FFFF
} ItemBagFlag;

#define MAXITEMBARBLOCKS 20u

typedef enum ItemStatus {
	ITEMSTATUS_FREE,
	ITEMSTATUS_ACTIVE,
	ITEMSTATUS_INACTIVE
} ItemStatus;

typedef struct Item Item;
struct Item {
	ItemStatus status;
	ItemType type;

	int16_t values[3];
	uint8_t states[4];
	DATA(data, 0x800);

	Player* activatingPlayer;

	Item* previous;
	Item* next;
};

#define ITEM_DATA_PTR(type, ptr, item) type* ptr = (type*)(item)->data;

struct Player;
typedef struct Player Player;

void RemoveItems(Player* player);
bool CheckDeactivateItem(Item* item);
bool FreeFall(Player* player);
bool _0x6018584(Player* player); // Unused.
ItemCategory NoDisableGarbage(Item* item);

typedef enum ItemCategory {
	ITEMCAT_NONE,
	ITEMCAT_GOOD,
	ITEMCAT_BAD,
	ITEMCAT_NEUTRAL
} ItemCategory;

bool ItemGood(Player* player);
bool ItemBad(Player* player);
ItemCategory GetItemCategory(ItemType itemType);
bool ItemConfusing(Player* player);

void _0x601886C();
// NOTE: Unused. Not suggested to be used, since it doesn't work the same as
// UpdateItems(), and the rest of the code depends on how UpdateItems() works.
// Only included for the sake of completeness and preservation.
//void UpdateVersusItems(Player* player);
void InitItems();
Item* AllocItem();
void DeactivateItem(Item* item);
void UpdateItems();

// TODO: Define these in their own source files, only using their headers in Item.c.
void UpdateItemColorBlock(Item* item);
void UpdateItemTopDelField(Item* item);
void UpdateItemBottomDelField(Item* item);
void UpdateItemRightMovField(Item* item);
void UpdateItemLeftMovField(Item* item);
void UpdateItemDelEven(Item* item);
void UpdateItemShotgun(Item* item);
void UpdateItemFreeFall(Item* item);
void UpdateItemExchgField(Item* item);
void UpdateItemMirrorBlock(Item* item);
void UpdateItemDarkBlock(Item* item);
void UpdateItemHardBlock(Item* item);
void UpdateItemLaser(Item* item);
int16_t LaserColumn(Player* player);
void UpdateItemRollRoll(Item* item);
void UpdateItemTransform(Item* item);
void UpdateItemXRay(Item* item);
void UpdateItemFlipField(Item* item); // 180° item.
