#include <M5Stack.h>
#include "esp_spi_flash.h"

#include "mappacklib.h"

extern uint16_t map_maplayer0[30][30];
extern uint16_t map_maplayer1[30][30];
extern uint16_t map_maplayer2[30][30];

TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);
TFT_eSprite Disbuff1 = TFT_eSprite(&M5.Lcd);

const char *WifiSSID = "M5-5G";
const char *WifiPWD = "Office@888888";

uint8_t imagedata[576];

#define DISPLAY_WIDTH   320
#define DISPLAY_HEIGHT  240

void drawMapPack(int x, int y, uint16_t group, uint16_t mapPackData)
{
    int disx,disy;
    if( !( mapPackData & 0x8000 )) return;

    uint16_t mapnumber = ( mapPackData >> 12 ) & 0x07;

    uint16_t *colorindex = indexList[mapgroupbuff[group][mapnumber]];
    spi_flash_read(0x420000 + addrList[mapgroupbuff[group][mapnumber]] + ( mapPackData & 0x3ff ) * 576,imagedata,sizeof(uint8_t) * 576);
    for (int i = 0; i < 576; i++)
    {
        disx =  x + i % 24;
        disy =  y + i / 24;
        if( ( imagedata[i] == 0xff )||\
            ( disx < 0 ) || ( disx > DISPLAY_WIDTH ) ||\
            ( disy < 0 ) || ( disy > DISPLAY_HEIGHT )) continue;

        Disbuff.drawPixel16(    disx,
                                disy,
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

void drawdisWindows(int posx,int posy)
{
    int drawRect_x,drawRect_y,drawRect_w,drawRect_h;
    drawRect_w = ( DISPLAY_WIDTH % 24 == 0 ) ? DISPLAY_WIDTH : DISPLAY_WIDTH + DISPLAY_WIDTH % 24;
    drawRect_h = ( DISPLAY_HEIGHT % 24 == 0 ) ? DISPLAY_HEIGHT : DISPLAY_HEIGHT + DISPLAY_HEIGHT % 24;
    int mapposx,mapposy;

    if( posx % 24 == 0 )
    {
        mapposx = posx / 24;
        drawRect_x = 0;
        drawRect_w /= 24;
    }
    else
    {
        mapposx = posx / 24 ;
        drawRect_x = 0 - ( posx % 24 ); 
        drawRect_w = ( drawRect_w + drawRect_x ) < DISPLAY_WIDTH ? drawRect_w / 24 + 2 : drawRect_w / 24 + 1;
        //drawRect_w = drawRect_w / 24 + 2;
    }
    
    if( posy % 24 == 0 )
    {
        mapposy = posy / 24;
        drawRect_y = 0;
        drawRect_h /= 24;
    }
    else
    {
        mapposy = posy / 24 ;
        drawRect_y = 0 - ( posy % 24 ); 
        drawRect_h = ( drawRect_h + drawRect_y ) < DISPLAY_HEIGHT ? drawRect_h  / 24 + 2 : drawRect_h / 24 + 1;
        //drawRect_h = drawRect_h / 24 + 2;
    }

    uint16_t (*maplayerptr)[30] = nullptr;
    for( int n = 0; n < 3; n++ )
    {
        maplayerptr = (uint16_t (*)[30])maplayerbuff[n];
        for( int y = 0 ; y < drawRect_h ; y++ )
        {
            for( int x = 0 ; x < drawRect_w ; x++ )
            {
                drawMapPack(drawRect_x + x * 24,drawRect_y + y * 24,2,maplayerptr[y + mapposy][x + mapposx]);
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
    drawdisWindows(0,0);
    Disbuff.pushSprite(0,0);
}
// start | select | a | b | down | right | left | up
char bitbuff[9];
uint8_t dir = 0,state = 0;
int posx = 0, posy = 0;

void loop()
{
    /*
    M5.update();
    Wire.requestFrom(0x08,1);
    uint8_t data = ~Wire.read();

    if( data & 0x08 )       //down
    {
        dir = 0;
        state ++;
        state = state % 3;
        posy ++;
        //posy = posy > 20 ? 20 : posy;
    }
    else if( data & 0x04 )  //right
    {
        dir = 2;
        state ++;
        state = state % 3;
        posx ++;
        //posx = posx > 17 ? 17 : posx;
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
    */
    posx ++;
    posx = ( posx > 296 ) ? 0 : posx;
    drawdisWindows(posx,posy);
    //Disbuff.pushSprite(0,0);

    //Disbuff.pushImage(120,120,48,48,(uint16_t*)qwbuff[dir * 3 + state]);
    //Disbuff.pushSprite(0, 0);

    //delay(10);
}