/*
Cubesat Space Protocol - A small network-layer protocol designed for Cubesats
Copyright (C) 2010 Gomspace ApS (gomspace.com)
Copyright (C) 2010 AAUSAT3 Project (aausat3.space.aau.dk) 

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdio.h>
#include <stdint.h>

/* FreeRTOS includes */
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

/* CSP includes */
#include <csp/csp.h>

#include "../csp_malloc.h"
#include "../csp_semaphore.h"
#include "../csp_queue.h"

int csp_bin_sem_create(csp_bin_sem_handle_t * sem) {
    vSemaphoreCreateBinary(*sem);
    return CSP_SEMAPHORE_OK;
}

int csp_bin_sem_remove(csp_bin_sem_handle_t * sem) {
	if ((sem != NULL) && (*sem != NULL)) {
		csp_queue_remove(*sem);
	}
	return CSP_SEMAPHORE_OK;
}

int csp_bin_sem_wait(csp_bin_sem_handle_t * sem, int timeout) {
	csp_debug(CSP_LOCK, "Wait: %p\r\n", sem);
    if (xSemaphoreTake(*sem, timeout / portTICK_RATE_MS) == pdPASS) {
        return CSP_SEMAPHORE_OK;
    } else {
        return CSP_SEMAPHORE_ERROR;
    }
}

int csp_bin_sem_post(csp_bin_sem_handle_t * sem) {
	csp_debug(CSP_LOCK, "Post: %p\r\n", sem);
    if (xSemaphoreGive(*sem) == pdPASS) {
        return CSP_SEMAPHORE_OK;
    } else {
        return CSP_SEMAPHORE_ERROR;
    }
}

int csp_bin_sem_post_isr(csp_bin_sem_handle_t * sem, CSP_BASE_TYPE * task_woken) {
	csp_debug(CSP_LOCK, "Post: %p\r\n", sem);
    if (xSemaphoreGiveFromISR(*sem, (signed CSP_BASE_TYPE *)task_woken) == pdPASS) {
        return CSP_SEMAPHORE_OK;
    } else {
        return CSP_SEMAPHORE_ERROR;
    }
}

