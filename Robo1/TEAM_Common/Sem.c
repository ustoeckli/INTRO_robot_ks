/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_CONFIG_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"

static xSemaphoreHandle sem = NULL;

static void vSlaveTask(void *pvParameters) {
  /*! \todo Implement functionality */
	for(;;){
		(void)pvParameters;
		if(FRTOS1_xSemaphoreTake(sem, 0)){
			LED1_Neg();
		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

static void vMasterTask(void *pvParameters) {
  /*! \todo send semaphore from master task to slave task */
	for(;;){
		(void)pvParameters;
		FRTOS1_xSemaphoreGive(sem);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void SEM_Deinit(void) {
	FRTOS1_vSemaphoreDelete(sem);
}

/*! \brief Initializes module */
void SEM_Init(void) {
	sem = FRTOS1_xSemaphoreCreateBinary();
	if (sem == NULL) {
		/* Faild, Heap to small? */
	}
	if (FRTOS1_xTaskCreate(vSlaveTask, "SlaveTask", 300/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS){
	    for(;;){}
	}
	if (FRTOS1_xTaskCreate(vMasterTask, "MasterTask", 300/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS){
	    for(;;){}
	}
}
#endif /* PL_CONFIG_HAS_SEMAPHORE */
