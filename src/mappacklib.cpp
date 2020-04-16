#include "mappacklib.h"

int mapgroupbuff[4][8]={
    { 0 , 1 , 2 , 3 , 4 , 5 , -1, -1 },
    { 6 , 7 , 8 , 9 , 10, 11, -1, -1 },
    { 12, 13, 14, 15, 16, 17, 18, -1 },
    { 19, 20, 21, 22, -1, -1, -1, -1 },
};

uint8_t *mapliblist[22] = {
    (uint8_t *)nullptr,  //0
    (uint8_t *)nullptr,  //1
    (uint8_t *)nullptr,  //2
    (uint8_t *)nullptr,  //3
    (uint8_t *)nullptr,   //4
    (uint8_t *)nullptr,   //5
    (uint8_t *)nullptr,   //6
    (uint8_t *)nullptr,   //7
    (uint8_t *)nullptr,   //8
    (uint8_t *)nullptr,   //9
    (uint8_t *)nullptr,    //10
    (uint8_t *)nullptr,    //11
    (uint8_t *)map_Outside_A1data,  //12
    (uint8_t *)map_Outside_A2data,  //13
    (uint8_t *)map_Outside_A3data,  //14
    (uint8_t *)map_Outside_A4data,  //15
    (uint8_t *)map_Outside_A5data,  //16
    (uint8_t *)map_Outside_Bdata,   //17
    (uint8_t *)map_Outside_Cdata,   //18
    (uint8_t *)nullptr,    //19
    (uint8_t *)nullptr,    //20
    (uint8_t *)nullptr,     //21
};
/*
uint8_t *mapliblist[22] = {
    (uint8_t *)map_Dungeon_A1data,  //0
    (uint8_t *)map_Dungeon_A2data,  //1
    (uint8_t *)map_Dungeon_A4data,  //2
    (uint8_t *)map_Dungeon_A5data,  //3
    (uint8_t *)map_Dungeon_Bdata,   //4
    (uint8_t *)map_Dungeon_Cdata,   //5
    (uint8_t *)map_Inside_A1data,   //6
    (uint8_t *)map_Inside_A2data,   //7
    (uint8_t *)map_Inside_A4data,   //8
    (uint8_t *)map_Inside_A5data,   //9
    (uint8_t *)map_Inside_Bdata,    //10
    (uint8_t *)map_Inside_Cdata,    //11
    (uint8_t *)map_Outside_A1data,  //12
    (uint8_t *)map_Outside_A2data,  //13
    (uint8_t *)map_Outside_A3data,  //14
    (uint8_t *)map_Outside_A4data,  //15
    (uint8_t *)map_Outside_A5data,  //16
    (uint8_t *)map_Outside_Bdata,   //17
    (uint8_t *)map_Outside_Cdata,   //18
    (uint8_t *)map_World_A1data,    //19
    (uint8_t *)map_World_A2data,    //20
    (uint8_t *)map_World_Bdata,     //21
};
*/
uint16_t *indexList[22] = {
    (uint16_t *)Dungeon_A1_index,
    (uint16_t *)Dungeon_A2_index,
    (uint16_t *)Dungeon_A4_index,
    (uint16_t *)Dungeon_A5_index,
    (uint16_t *)Dungeon_B_index,
    (uint16_t *)Dungeon_C_index,
    (uint16_t *)Inside_A1_index,
    (uint16_t *)Inside_A2_index,
    (uint16_t *)Inside_A4_index,
    (uint16_t *)Inside_A5_index,
    (uint16_t *)Inside_B_index,
    (uint16_t *)Inside_C_index,
    (uint16_t *)Outside_A1_index,
    (uint16_t *)Outside_A2_index,
    (uint16_t *)Outside_A3_index,
    (uint16_t *)Outside_A4_index,
    (uint16_t *)Outside_A5_index,
    (uint16_t *)Outside_B_index,
    (uint16_t *)Outside_C_index,
    (uint16_t *)World_A1_index,
    (uint16_t *)World_A2_index,
    (uint16_t *)World_B_index,
};

