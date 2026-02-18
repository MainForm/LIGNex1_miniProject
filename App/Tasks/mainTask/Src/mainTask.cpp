#include "mainTask.hpp"
#include "FreeRTOS_Handles.h"
#include "Point.h"
#include "MNIST_image.h"

#include "Interrupts.hpp"

// Include the peripherals
#include "cmsis_os2.h"
#include "spi.h"
#include "ltdc.h"
#include "dma2d.h"
#include "fmc.h"

#include "IS42S16400J_7TL.h"

#include <cstring>

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

float inputData[INPUT_HEIGHT][INPUT_WIDTH] = {0. ,};
bool bBtnPushed = false;

void drawFrame(){
    for(uint32_t iy = 0; iy < INPUT_HEIGHT;iy++){
        for(uint32_t ix = 0; ix < INPUT_WIDTH;ix++){
            TFT_LCD::Pixel curPixel(0x1F * (float)inputData[iy][ix], 0x2F * (float)inputData[iy][ix], 0x1F * (float)inputData[iy][ix]);
            lcd.drawRectangle(ix * IMG_RECT_SIZE,iy * IMG_RECT_SIZE, IMG_RECT_SIZE - 1, IMG_RECT_SIZE - 1, 0xFFFF - curPixel,false);
        }
    }
}

Point convertToImgSize(Point pt){
    pt.x /= IMG_RECT_SIZE;
    pt.y /= IMG_RECT_SIZE;

    return pt;
}

void BluePushButton_Clicked(){
    bBtnPushed = true;
}

extern "C"
void mainTaskHandler(void *argument){
    Point recvPoint;
    uint8_t mqPriority;

    GPIO_PortA0_Callback = BluePushButton_Clicked;

    // init external SDRAM
    BSP_SDRAM_IS42S16400J_7TL_Init(&hsdram1,REFRESH_COUNT);

    lcd.initalize(reinterpret_cast<uint16_t*>(FRAME_BUFFER_ADDRESS));
    lcd.setBackFrameBuffer(reinterpret_cast<uint16_t*>(FRAME_BACK_BUFFER_ADDRESS));

    for(;;){
        if(osMessageQueueGet(PointQueueHandle,&recvPoint,&mqPriority,0x00) == osOK){
            Point imgPoint = convertToImgSize(recvPoint);

            if(imgPoint.y < INPUT_HEIGHT - 1 && imgPoint.x < INPUT_WIDTH - 1
                && imgPoint.y > 0 && imgPoint.x > 0){
                inputData[imgPoint.y][imgPoint.x] = 1.0f;
                inputData[imgPoint.y + 1][imgPoint.x] = 1.0f;
                inputData[imgPoint.y][imgPoint.x + 1] = 1.0f;
                inputData[imgPoint.y + 1][imgPoint.x + 1] = 1.0f;
            }
        }
        drawFrame();
        lcd.updateFrame();

        if(bBtnPushed == true){
            bBtnPushed = false;
            MNIST_image imgData;
            memcpy(imgData.data,inputData,28*28 * sizeof(float));

            osMessageQueuePut(MNIST_QueueHandle,&imgData,osPriorityIdle,10);

            memset(inputData,0,28*28 * sizeof(float));
        }

        osDelay(16);
    }
}