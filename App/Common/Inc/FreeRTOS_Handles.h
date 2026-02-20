#ifndef __APP_COMMON_FREERTOS_HANDLE_H__
#define __APP_COMMON_FREERTOS_HANDLE_H__

#include "cmsis_os2.h"

extern osMessageQueueId_t PointQueueHandle;
extern osMessageQueueId_t MNIST_QueueHandle;

extern osMutexId_t I2C3_mutexHandle;

#endif // __APP_COMMON_FREERTOS_HANDLE_H__