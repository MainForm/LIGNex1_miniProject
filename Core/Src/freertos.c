/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Point.h"
#include "MNIST_image.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for mainTask */
osThreadId_t mainTaskHandle;
uint32_t defaultTaskBuffer[ 4096 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t mainTask_attributes = {
  .name = "mainTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for touchPanelTask */
osThreadId_t touchPanelTaskHandle;
uint32_t touchPanelTaskBuffer[ 512 ];
osStaticThreadDef_t touchPanelTaskControlBlock;
const osThreadAttr_t touchPanelTask_attributes = {
  .name = "touchPanelTask",
  .cb_mem = &touchPanelTaskControlBlock,
  .cb_size = sizeof(touchPanelTaskControlBlock),
  .stack_mem = &touchPanelTaskBuffer[0],
  .stack_size = sizeof(touchPanelTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for mnistTask */
osThreadId_t mnistTaskHandle;
uint32_t mnistTaskBuffer[ 2048 ];
osStaticThreadDef_t mnistTaskControlBlock;
const osThreadAttr_t mnistTask_attributes = {
  .name = "mnistTask",
  .cb_mem = &mnistTaskControlBlock,
  .cb_size = sizeof(mnistTaskControlBlock),
  .stack_mem = &mnistTaskBuffer[0],
  .stack_size = sizeof(mnistTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for PointQueue */
osMessageQueueId_t PointQueueHandle;
uint8_t PointQueueBuffer[ 16 * sizeof( Point ) ];
osStaticMessageQDef_t PointQueueControlBlock;
const osMessageQueueAttr_t PointQueue_attributes = {
  .name = "PointQueue",
  .cb_mem = &PointQueueControlBlock,
  .cb_size = sizeof(PointQueueControlBlock),
  .mq_mem = &PointQueueBuffer,
  .mq_size = sizeof(PointQueueBuffer)
};
/* Definitions for MNIST_Queue */
osMessageQueueId_t MNIST_QueueHandle;
uint8_t MNIST_QueueBuffer[ 16 * sizeof( MNIST_image ) ];
osStaticMessageQDef_t MNIST_QueueControlBlock;
const osMessageQueueAttr_t MNIST_Queue_attributes = {
  .name = "MNIST_Queue",
  .cb_mem = &MNIST_QueueControlBlock,
  .cb_size = sizeof(MNIST_QueueControlBlock),
  .mq_mem = &MNIST_QueueBuffer,
  .mq_size = sizeof(MNIST_QueueBuffer)
};
/* Definitions for I2C3_mutex */
osMutexId_t I2C3_mutexHandle;
osStaticMutexDef_t I2C3_mutexControlBlock;
const osMutexAttr_t I2C3_mutex_attributes = {
  .name = "I2C3_mutex",
  .cb_mem = &I2C3_mutexControlBlock,
  .cb_size = sizeof(I2C3_mutexControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void mainTaskHandler(void *argument);
extern void touchPanelTaskHandler(void *argument);
extern void mnistTaskHandler(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of I2C3_mutex */
  I2C3_mutexHandle = osMutexNew(&I2C3_mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of PointQueue */
  PointQueueHandle = osMessageQueueNew (16, sizeof(Point), &PointQueue_attributes);

  /* creation of MNIST_Queue */
  MNIST_QueueHandle = osMessageQueueNew (16, sizeof(MNIST_image), &MNIST_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of mainTask */
  mainTaskHandle = osThreadNew(mainTaskHandler, NULL, &mainTask_attributes);

  /* creation of touchPanelTask */
  touchPanelTaskHandle = osThreadNew(touchPanelTaskHandler, NULL, &touchPanelTask_attributes);

  /* creation of mnistTask */
  mnistTaskHandle = osThreadNew(mnistTaskHandler, NULL, &mnistTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_mainTaskHandler */
/**
  * @brief  Function implementing the mainTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_mainTaskHandler */
__weak void mainTaskHandler(void *argument)
{
  /* USER CODE BEGIN mainTaskHandler */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END mainTaskHandler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

