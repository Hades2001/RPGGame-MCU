#ifndef MAPPACKLIB_H
#define MAPPACKLIB_H
#include <Arduino.h>

extern const uint8_t map_Dungeon_A1data[768][1152];
extern const uint8_t map_Dungeon_A2data[768][1152];
extern const uint8_t map_Dungeon_A4data[960][1152];
extern const uint8_t map_Dungeon_A5data[512][1152];
extern const uint8_t map_Dungeon_Bdata[1024][1152];
extern const uint8_t map_Dungeon_Cdata[1024][1152];
extern const uint8_t map_Inside_A1data[768][1152];
extern const uint8_t map_Inside_A2data[768][1152];
extern const uint8_t map_Inside_A4data[960][1152];
extern const uint8_t map_Inside_A5data[512][1152];
extern const uint8_t map_Inside_Bdata[1024][1152];
extern const uint8_t map_Inside_Cdata[1024][1152];
extern const uint8_t map_Outside_A1data[768][1152];
extern const uint8_t map_Outside_A2data[768][1152];
extern const uint8_t map_Outside_A3data[512][1152];
extern const uint8_t map_Outside_A4data[960][1152];
extern const uint8_t map_Outside_A5data[512][1152];
extern const uint8_t map_Outside_Bdata[1024][1152];
extern const uint8_t map_Outside_Cdata[1024][1152];
extern const uint8_t map_SF_Inside_A4data[960][1152];
extern const uint8_t map_SF_Inside_Bdata[1024][1152];
extern const uint8_t map_SF_Inside_Cdata[1024][1152];
extern const uint8_t map_SF_Outside_A3data[512][1152];
extern const uint8_t map_SF_Outside_A4data[960][1152];
extern const uint8_t map_SF_Outside_A5data[512][1152];
extern const uint8_t map_SF_Outside_Bdata[1024][1152];
extern const uint8_t map_SF_Outside_Cdata[1024][1152];
extern const uint8_t map_World_A1data[768][1152];
extern const uint8_t map_World_A2data[768][1152];
extern const uint8_t map_World_Bdata[1024][1152];
extern const uint8_t map_World_Cdata[1024][1152];

extern uint8_t *mapliblist[31];
extern int mapgroupbuff[6][8];

#endif
