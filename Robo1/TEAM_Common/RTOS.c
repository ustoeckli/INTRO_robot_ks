/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "Application.h"
#include "LED.h"

/**
 * Blink-Task: Blinkt im 100ms-Takt mit LED2
 */
static void BlinkyTask(void *pvParameters){
	for(;;){
		LED1_Neg();
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

/**
 * Startet RTOS-Tasks (Tasks werden vorwiegend in entsprechendem Treiber gestartet -> Shell.c, Application.c usw.)
 */
void RTOS_Init(void) {
	/* Blink-Task starten */
	if (xTaskCreate(BlinkyTask, "Blinky", 300/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS){
	    for(;;);
	}
}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

#endif /* PL_CONFIG_HAS_RTOS */
