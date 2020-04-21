#include <M5Stack.h>
#include "esp_spi_flash.h"

#include "mappacklib.h"

extern uint16_t map_maplayer0[30][30];
extern uint16_t map_maplayer1[30][30];
extern uint16_t map_maplayer2[30][30];

TFT_eSprite Disbuff = TFT_eSprite(&M5.Lcd);
TFT_eSprite Disbuff0 = TFT_eSprite(&M5.Lcd);
TFT_eSprite Disbuff1 = TFT_eSprite(&M5.Lcd);

const char *WifiSSID = "M5-5G";
const char *WifiPWD = "Office@888888";

uint8_t imagedata[576];

#define DISPLAY_WIDTH   320
#define DISPLAY_HEIGHT  24


SemaphoreHandle_t xdisbuffUser = nullptr;

struct display
{
    TFT_eSprite* disclassptr[2];
    uint16_t* displayptr[2];
    uint8_t buffNumber;
    bool    drawReady[2];

}disbuff_str;

void drawMapPack(int x, int y, uint16_t group, uint16_t mapPackData, uint8_t buffflag)
{
    int disx,disy;
    if( !( mapPackData & 0x8000 )) return;

    uint16_t mapnumber = ( mapPackData >> 12 ) & 0x07;

    uint16_t *colorindex = indexList[mapgroupbuff[group][mapnumber]];
    uint16_t color = 0;
    spi_flash_read(0x420000 + addrList[mapgroupbuff[group][mapnumber]] + ( mapPackData & 0x3ff ) * 576,imagedata,sizeof(uint8_t) * 576);
    for (int i = 0; i < 576; i++)
    {
        disx =  x + i % 24;
        disy =  y + i / 24;
        if( ( imagedata[i] == 0xff )||\
            ( disx < 0 ) || ( disx > DISPLAY_WIDTH ) ||\
            ( disy < 0 ) || ( disy > DISPLAY_HEIGHT )) continue;

        color = ( colorindex[imagedata[i]] >> 8 ) | ( colorindex[imagedata[i]] << 8 );
        //disbuff_str.disclassptr[buffflag]->drawPixel16(disx,disy,colorindex[imagedata[i]]);
        disbuff_str.displayptr[buffflag][disx + disy * DISPLAY_WIDTH] = color;
    }
}
uint16_t *maplayerbuff[3] = {
    (uint16_t*) map_maplayer0,
    (uint16_t*) map_maplayer1,
    (uint16_t*) map_maplayer2,
};

uint8_t isReady(uint8_t number)
{
    bool readyFlag;
    xSemaphoreTake(xdisbuffUser, portMAX_DELAY);
    readyFlag = disbuff_str.drawReady[number];
    xSemaphoreGive(xdisbuffUser);
    return readyFlag;
}

void setReady( uint8_t number, bool flag )
{
    xSemaphoreTake(xdisbuffUser, portMAX_DELAY);
    disbuff_str.drawReady[number] = flag;
    xSemaphoreGive(xdisbuffUser);
}

uint8_t getDrawBuffNumber()
{
    uint8_t num;
    xSemaphoreTake(xdisbuffUser, portMAX_DELAY);
    num = disbuff_str.buffNumber;
    xSemaphoreGive(xdisbuffUser);
    return num;
}

void setDrawBuffNumber( uint8_t num )
{
    xSemaphoreTake(xdisbuffUser, portMAX_DELAY);
    disbuff_str.buffNumber = num;
    xSemaphoreGive(xdisbuffUser);
}


void drawdisWindows(int posx,int posy)
{
    int drawRect_x,drawRect_y,drawRect_w,drawRect_h;
    drawRect_w = ( DISPLAY_WIDTH % 24 == 0 ) ? DISPLAY_WIDTH : DISPLAY_WIDTH + DISPLAY_WIDTH % 24;
    drawRect_h = ( DISPLAY_HEIGHT % 24 == 0 ) ? DISPLAY_HEIGHT : DISPLAY_HEIGHT + DISPLAY_HEIGHT % 24;
    int mapposx,mapposy;
    uint8_t buffflag = 0;

    if( posx % 24 == 0 )
    {
        mapposx = posx / 24;
        drawRect_x = 0;
        drawRect_w = drawRect_w / 24 + 1;
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
        drawRect_h = drawRect_h / 24 + 1;
    }
    else
    {
        mapposy = posy / 24 ;
        drawRect_y = 0 - ( posy % 24 ); 
        drawRect_h = ( drawRect_h + drawRect_y ) < DISPLAY_HEIGHT ? drawRect_h  / 24 + 2 : drawRect_h / 24 + 1;
        //drawRect_h = drawRect_h / 24 + 2;
    }

    buffflag = getDrawBuffNumber();

    while (isReady(buffflag) == true) delay(10);

    uint16_t (*maplayerptr)[30] = nullptr;

    for( int n = 0; n < 3; n++ )
    {
        maplayerptr = (uint16_t (*)[30])maplayerbuff[n];
        for( int y = 0 ; y < drawRect_h ; y++ )
        {
            for( int x = 0 ; x < drawRect_w ; x++ )
            {
                drawMapPack(drawRect_x + x * 24,drawRect_y + y * 24,2,maplayerptr[y + mapposy][x + mapposx],buffflag);
            }
        }
    }
    setReady(buffflag,true);

    
}

void displaybuff(void *arg)
{
    uint8_t buffflag = 0;
    bool BusyFlag = false;
    while(1)
    {
        xSemaphoreTake(xdisbuffUser, portMAX_DELAY);
        buffflag = ( disbuff_str.buffNumber == 1 ) ? 0 : 1; 
        xSemaphoreGive(xdisbuffUser);

        //disbuff_str.disclassptr[buffflag]->drawNumber(buffflag,0,0);
        disbuff_str.disclassptr[buffflag]->pushSprite(0,0);
        
        do
        {
            xSemaphoreTake(xdisbuffUser, portMAX_DELAY);
            disbuff_str.drawReady[buffflag] = false;
            BusyFlag = disbuff_str.drawReady[disbuff_str.buffNumber];
            xSemaphoreGive(xdisbuffUser);
            delay(10);
        } while (BusyFlag == false);

        xSemaphoreTake(xdisbuffUser, portMAX_DELAY);
        disbuff_str.buffNumber = buffflag;
        xSemaphoreGive(xdisbuffUser);
        delay(1);
    }
}
uint64_t time_os;
void setup()
{
    // put your setup code here, to run once:

    M5.begin();
    Wire.begin();
    spi_flash_init();
    M5.Lcd.setSwapBytes(false);
    M5.Lcd.setBrightness(40);

    Disbuff0.createSprite(320, 240);
    Disbuff1.createSprite(320, 240);

    disbuff_str.disclassptr[0] = &Disbuff0;
    disbuff_str.disclassptr[1] = &Disbuff1;
    disbuff_str.displayptr[0] = Disbuff0.getBuffptr();
    disbuff_str.displayptr[1] = Disbuff1.getBuffptr();
    disbuff_str.buffNumber = 1;
    disbuff_str.disclassptr[0]->fillRect(0,0,320,240,BLUE);
    disbuff_str.disclassptr[1]->fillRect(0,0,320,240,BLUE);

    disbuff_str.disclassptr[0]->pushSprite(0,0);
    
    disbuff_str.disclassptr[0]->setSwapBytes(true);
    disbuff_str.disclassptr[1]->setSwapBytes(true);

    disbuff_str.drawReady[0] = false;
    disbuff_str.drawReady[1] = false;

    xdisbuffUser = xSemaphoreCreateMutex();
    
    xSemaphoreTake(xdisbuffUser, 100 / portTICK_RATE_MS);
    xSemaphoreGive(xdisbuffUser);
    drawdisWindows(0,0);

    xTaskCreatePinnedToCore(displaybuff, "displaybuff", 1024 * 2, nullptr, 2, nullptr,0);
    time_os = micros();

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
    //if( isReady() == true );
    posx += 1;
    posx = ( posx > 296 ) ? 0 : posx;
    drawdisWindows(posx,posy);
    Serial.printf("Time : %d\n",micros() - time_os);
    
    time_os = micros();
    
    //Disbuff.pushSprite(0,0);

    //Disbuff.pushImage(120,120,48,48,(uint16_t*)qwbuff[dir * 3 + state]);
    //Disbuff.pushSprite(0, 0);
    
    delay(1);
}