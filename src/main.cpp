#include <M5Stack.h>
#include "esp_spi_flash.h"

#include "mappacklib.h"

extern uint16_t map_maplayer0[30][30];
extern uint16_t map_maplayer1[30][30];
extern uint16_t map_maplayer2[30][30];

TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);

const char *WifiSSID = "M5-5G";
const char *WifiPWD = "Office@888888";

uint8_t imagedata[576];

void drawMapPack(uint16_t x, uint16_t y, uint16_t group, uint16_t mapPackData)
{
    if( !( mapPackData & 0x8000 )) return;

    uint16_t mapnumber = ( mapPackData >> 12 ) & 0x07;

    uint16_t *colorindex = indexList[mapgroupbuff[group][mapnumber]];
    spi_flash_read(0x420000 + addrList[mapgroupbuff[group][mapnumber]] + ( mapPackData & 0x3ff ) * 576,imagedata,sizeof(uint8_t) * 576);
    for (int i = 0; i < 576; i++)
    {
        if( imagedata[i] == 0xff ) continue;
        Disbuff.drawPixel(  x + i % 24,
                            y + i / 24,
                            colorindex[imagedata[i]]);
    }
}
uint16_t *maplayerbuff[3] = {
    (uint16_t*) map_maplayer0,
    (uint16_t*) map_maplayer1,
    (uint16_t*) map_maplayer2,
};
void drawmap( int posx, int posy)
{
    uint16_t (*maplayerptr)[30] = nullptr;
    for( int n = 0; n < 3; n++ )
    {
        maplayerptr = (uint16_t (*)[30])maplayerbuff[n];
        for( int y = 0 ; y < 10 ; y++ )
        {
            for( int x = 0 ; x < 13 ; x++ )
            {
                drawMapPack(x*24,y*24,2,maplayerptr[y+posy][x+posx]);
            }
        }
    }

    Disbuff.pushSprite(0,0);
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

    Serial.println("Init Wifi");
    drawmap(0,0);
    Disbuff.pushSprite(0,0);

}
// start | select | a | b | down | right | left | up
char bitbuff[9];
uint8_t dir = 0,state = 0;
int posx = 0, posy = 0;
void loop()
{
    // put your main code here, to run repeatedly:
    M5.update();
    Wire.requestFrom(0x08,1);
    uint8_t data = ~Wire.read();

    if( data & 0x08 )       //down
    {
        dir = 0;
        state ++;
        state = state % 3;
        posy ++;
        posy = posy > 20 ? 20 : posy;
    }
    else if( data & 0x04 )  //right
    {
        dir = 2;
        state ++;
        state = state % 3;
        posx ++;
        posx = posx > 17 ? 17 : posx;
    }
    else if( data & 0x02 )  //left
    {
        dir = 1;
        state ++;
        state = state % 3;
        posx --;
        posx = posx < 0 ? 0 : posx;
    }
    else if( data & 0x01 )  //up
    {
        dir = 3;
        state ++;
        state = state % 3;
        posy --;
        posy = posy < 0 ? 0 : posy;
    }
    else
    {
        state = 1;
    }
    drawmap(posx,posy);
    Disbuff.pushSprite(0,0);

    //Disbuff.pushImage(120,120,48,48,(uint16_t*)qwbuff[dir * 3 + state]);
    //Disbuff.pushSprite(0, 0);

    //delay(10);
}