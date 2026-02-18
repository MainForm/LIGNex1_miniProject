#ifndef __APP_MAIN_TASK_H__
#define __APP_MAIN_TASK_H__

#include "main.h"
#include "cmsis_os2.h"

// Include the drivers
#include "ILI9341.hpp"

#define FRAME_BYTE_SIZE             (TFT_LCD::ILI9341::LCD_HEIGHT * TFT_LCD::ILI9341::LCD_WIDTH * TFT_LCD::ILI9341::PIXEL_BYTE_COUNT)

#define FRAME_BUFFER_ADDRESS        ((uint32_t)0xD0000000)
#define FRAME_BACK_BUFFER_ADDRESS   (FRAME_BUFFER_ADDRESS + FRAME_BYTE_SIZE)

#define INPUT_HEIGHT                (28)
#define INPUT_WIDTH                 (28)

#define IMG_RECT_SIZE               (8)

#endif // __APP_MAIN_TASK_H__