#pragma once

// Functions to access EEPROM. Definitions provided by frontends.
//
// A frontend has to do conversion of EEPROM data to guarantee the save data
// format matches the PS5V2 version. The code directly stores structs with
// bitfields in EEPROM, so layout can't be guaranteed to match the original's.
// The bitfields might mismatch the original's, even on big endian
// architectures. Though testing of a frontend on a big endian archicture could
// be done, and if the format ends up matching the original's, the conversion
// could be omitted.
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define EEPROM_SIZE 0x100

typedef enum Region {
	REGION_JAPAN = 0,
	REGION_USACANADA = 1 << 0,
	REGION_KOREA = 1 << 1,
	REGION_HONGKONG = 1 << 2,
	REGION_TAIWAN = 1 << 3,
	REGION_SETTING = 0xF
} Region;

void PushEepromBit(bool bit);
void UNK_602F704();
void UNK_602F7DC();
void UNK_602F8BC();
void UNK_602FA7E();
void WriteSettings();
uint8_t ReadEepromByte(uint8_t offset);
void ReadEeprom(uint8_t offset, void* destination, size_t size);
void WriteEepromByte(uint8_t offset, uint8_t data);
void WriteEeprom(uint8_t offset, void* source, size_t size);
