#ifndef MAPPACKLIB_H
#define MAPPACKLIB_H
#include <Arduino.h>

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
extern uint32_t addrList[22];
extern int mapgroupbuff[4][8];

#endif
