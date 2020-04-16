#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "mappacklib.h"

TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);

const char *WifiSSID = "M5-5G";
const char *WifiPWD = "Office@888888";


void drawMapPack(uint16_t x, uint16_t y, uint16_t group, uint16_t mapPackData)
{
    //uint8_t (*mapptr)[1152] = (uint8_t (*)[1152])mapliblist[mapgroupbuff[group][0]];
    for( int posY = 0; posY < 24; posY ++ )
    {
        for( int posX = 0; posX < 24; posX ++ )
        {
            Disbuff.drawPixel(x + posX,y + posY,Outside_A1_index[map_Outside_A1data[mapPackData][posY * 24 + posX]]);
        }
    }
    Disbuff.pushSprite(0,0);
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
    Disbuff.setColorDepth(16);
    Disbuff.fillRect(0,0,320,240,BLUE);
    Disbuff.setSwapBytes(true);

    Disbuff.pushSprite(0,0);
    //Disbuff.pushImage(0,0,48,48,(uint16_t*)qwbuff[0]);
    //Disbuff.pushSprite(136, 96);

    Serial.println("Init Wifi");
    
    drawMapPack( 0 ,0 ,1 ,0 );
    drawMapPack( 24,0 ,1 ,1 );
    drawMapPack( 48,0 ,1 ,2 );
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

    //Disbuff.pushImage(120,120,48,48,(uint16_t*)qwbuff[dir * 3 + state]);
    Disbuff.pushSprite(0, 0);

    delay(150);
}