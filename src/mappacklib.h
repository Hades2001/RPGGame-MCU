#ifndef MAPPACKLIB_H
#define MAPPACKLIB_H
#include <Arduino.h>

extern const uint8_t map_Dungeon_A1data[384][576];
extern const uint8_t map_Dungeon_A2data[672][576];
extern const uint8_t map_Dungeon_A4data[840][576];
extern const uint8_t map_Dungeon_A5data[512][576];
extern const uint8_t map_Dungeon_Bdata[1024][576];
extern const uint8_t map_Dungeon_Cdata[1024][576];
extern const uint8_t map_Inside_A1data[384][576];
extern const uint8_t map_Inside_A2data[768][576];
extern const uint8_t map_Inside_A4data[960][576];
extern const uint8_t map_Inside_A5data[512][576];
extern const uint8_t map_Inside_Bdata[1024][576];
extern const uint8_t map_Inside_Cdata[1024][576];
extern const uint8_t map_Outside_A1data[384][576];
extern const uint8_t map_Outside_A2data[768][576];
extern const uint8_t map_Outside_A3data[512][576];
extern const uint8_t map_Outside_A4data[960][576];
extern const uint8_t map_Outside_A5data[512][576];
extern const uint8_t map_Outside_Bdata[1024][576];
extern const uint8_t map_Outside_Cdata[1024][576];
extern const uint8_t map_World_A1data[384][576];
extern const uint8_t map_World_A2data[768][576];
extern const uint8_t map_World_Bdata[1024][576];

extern const uint16_t Dungeon_A1_index[256];
extern const uint16_t Dungeon_A2_index[256];
extern const uint16_t Dungeon_A4_index[256];
extern const uint16_t Dungeon_A5_index[256];
extern const uint16_t Dungeon_B_index[256];
extern const uint16_t Dungeon_C_index[256];
extern const uint16_t Inside_A1_index[256];
extern const uint16_t Inside_A2_index[256];
extern const uint16_t Inside_A4_index[256];
extern const uint16_t Inside_A5_index[256];
extern const uint16_t Inside_B_index[256];
extern const uint16_t Inside_C_index[256];
extern const uint16_t Outside_A1_index[256];
extern const uint16_t Outside_A2_index[256];
extern const uint16_t Outside_A3_index[256];
extern const uint16_t Outside_A4_index[256];
extern const uint16_t Outside_A5_index[256];
extern const uint16_t Outside_B_index[256];
extern const uint16_t Outside_C_index[256];
extern const uint16_t World_A1_index[256];
extern const uint16_t World_A2_index[256];
extern const uint16_t World_B_index[256];

extern uint16_t *indexList[22];
extern uint8_t *mapliblist[22];
extern int mapgroupbuff[4][8];

#endif
