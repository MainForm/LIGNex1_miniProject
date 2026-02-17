#include "mainTask.hpp"

#include "cmsis_os2.h"

// Include the peripherals
#include "spi.h"
#include "ltdc.h"
#include "dma2d.h"
#include "fmc.h"

#include "IS42S16400J_7TL.h"

TFT_LCD::ILI9341 lcd(
    TFT_LCD::ILI9341_Config{
        .hspi = &hspi5,
        .CS = {CSX_GPIO_Port,CSX_Pin},              // CS
        .WR = {WRX_DCX_GPIO_Port,WRX_DCX_Pin},      // WR
        .RD = {RDX_GPIO_Port,RDX_Pin},              // RD
        .hltdc = &hltdc,
        .hdma2d = &hdma2d
    }
);

extern "C"
void mainTaskHandler(void *argument){

    // init external SDRAM
    BSP_SDRAM_IS42S16400J_7TL_Init(&hsdram1,REFRESH_COUNT);

    lcd.initalize(reinterpret_cast<uint16_t*>(FRAME_BUFFER_ADDRESS));
    lcd.setBackFrameBuffer(reinterpret_cast<uint16_t*>(FRAME_BACK_BUFFER_ADDRESS));

    uint32_t sx = 0;
    uint32_t sy = 0;

    uint32_t rectSize = 8;

    for(uint32_t iy = 0; iy < 28;iy++){
        for(uint32_t ix = 0; ix < 28;ix++){
            lcd.drawRectangle(ix * rectSize,iy * rectSize, rectSize, rectSize, 0xFFFF,false);
        }
    }

    lcd.updateFrame();

    for(;;){
        osDelay(1000);
    }
}