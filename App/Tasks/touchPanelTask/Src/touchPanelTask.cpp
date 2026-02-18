#include "touchPanelTask.hpp"
#include "FreeRTOS_Handles.h"

#include "ILI9341.hpp"

#include "cmsis_os2.h"

#include "i2c.h"

#include "Point.h"

TFT_LCD::STMPE811 touchPanel(
    &hi2c3
);

Point convertToLCDSize(Point pt){

    pt.x *= (TFT_LCD::ILI9341::LCD_WIDTH / (float)TP_WIDTH);
    pt.y *= (TFT_LCD::ILI9341::LCD_HEIGHT / (float)TP_HEIGHT);

    pt.x = TFT_LCD::ILI9341::LCD_WIDTH - pt.x;
    pt.y = TFT_LCD::ILI9341::LCD_HEIGHT - pt.y;

    return pt;
}

extern "C"
void touchPanelTaskHandler(void *argument){
    touchPanel.initalize();

    for(;;){
        if(touchPanel.isTouched()){
            Point curPoint;

            touchPanel.getTouchedPoint((uint32_t*)&curPoint.x, (uint32_t*)&curPoint.y);

            Point lcdPoint = convertToLCDSize(curPoint);
            osMessageQueuePut(
                PointQueueHandle,
                &lcdPoint,
                osPriorityIdle, 
                0xFFFF
            );
        }
        osDelay(16);
    }
}