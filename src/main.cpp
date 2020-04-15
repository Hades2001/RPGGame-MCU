#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "mappacklib.h"

extern uint8_t qwbuff[12][4608];
TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);

const char *WifiSSID = "M5-5G";
const char *WifiPWD = "Office@888888";


void drawMapPack(uint16_t x, uint16_t y, uint16_t mapPackData)
{
    /*
    if( mapPackData & 0x8000 )
    {

    }
    */
}

void setup()
{
    // put your setup code here, to run once:

    M5.begin();
    Wire.begin();
    M5.Lcd.setSwapBytes(false);
    M5.Lcd.setBrightness(40);

    Disbuff.createSprite(320, 240);
    Disbuff.setSwapBytes(true);

    Disbuff.setColorDepth(16);
    //Disbuff.pushImage(0,0,48,48,(uint16_t*)qwbuff[0]);
    //Disbuff.pushSprite(136, 96);

    Serial.println("Init Wifi");

    Disbuff.pushImage(0,0,24,24, (uint16_t*)map_Dungeon_A1data[0]);
    Disbuff.pushImage(24,0,24,24, (uint16_t*)map_Dungeon_A1data[1]);
    Disbuff.pushImage(48,0,24,24, (uint16_t*)map_Dungeon_A1data[2]);
    Disbuff.pushImage(72,0,24,24, (uint16_t*)map_Dungeon_A1data[3]);
    Disbuff.pushSprite(0, 0);

    /*
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.begin(WifiSSID, WifiPWD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print('.');
    }
    Serial.println("Wifi Connected");
    */

}
// start | select | a | b | down | right | left | up
char bitbuff[9];
uint8_t dir = 0,state = 0;
void loop()
{
    // put your main code here, to run repeatedly:
    M5.update();
    Wire.requestFrom(0x08,1);
    uint8_t data = ~Wire.read();
    if( data & 0x08 )
    {
        dir = 0;
        state ++;
        state = state % 3;
    }
    else if( data & 0x04 )
    {
        dir = 2;
        state ++;
        state = state % 3;
    }
    else if( data & 0x02 )
    {
        dir = 1;
        state ++;
        state = state % 3;
    }
    else if( data & 0x01 )
    {
        dir = 3;
        state ++;
        state = state % 3;
    }
    else
    {
        state = 1;
    }

    Disbuff.pushImage(120,120,48,48,(uint16_t*)qwbuff[dir * 3 + state]);
    Disbuff.pushSprite(0, 0);

    delay(150);
}