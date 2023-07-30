/***************************************************************************//**
* @file hrm_helper.h
* @brief Platform independent driver for maxm86161 biometric sensor
* @version 1.0.0
*******************************************************************************
* # License
* <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
*******************************************************************************
*
* SPDX-License-Identifier: Zlib
*
* The licensor of this software is Silicon Laboratories Inc.
*
* This software is provided \'as-is\', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*******************************************************************************/

#ifndef MAXM86161_HELPER_H_
#define MAXM86161_HELPER_H_

#include "maxm86161.h"
#include "maxm86161_spo2.h"
#include "Arduino.h"

typedef void *  max86161_hrm_helper_handle_t;

class maxm86161_hrm_helper
{
 public:
    maxm86161_fifo_queue_t ppg_queue;
    maxm86161_ppg_sample_t maxm86161_irq_queue[APP_QUEUE_SIZE];
    bool maxm86161_prox_mode;

    maxm86161_hrm_helper();

    /**************************************************************************//**
    * @brief Empty the samples in queue.
    *****************************************************************************/
    void maxm86161_helper_sample_queue_clear(void);

    /**************************************************************************//**
    * @brief Query number of entries in the queue.
    *****************************************************************************/
    int32_t maxm86161_hrm_helper_sample_queue_numentries(void);

    /**************************************************************************//**
    * @brief Get sample from the queue.
    *****************************************************************************/
    int32_t maxm86161_hrm_helper_sample_queue_get(maxm86161_hrm_irq_sample_t *samples);

    /**************************************************************************//**
    * @brief Initialize and clear the queue.
    *****************************************************************************/
    int32_t maxm86161_hrm_helper_initialize(void);

    /**************************************************************************//**
    * @brief Main interrupt processing routine for MAX86161.
    *****************************************************************************/
    void maxm86161_hrm_helper_process_irq(void);

    /**************************************************************************//**
    * @brief Use to check maxm86161 in proximity mode or normal mode
    *****************************************************************************/
#ifdef PROXIMITY
    bool maxm86161_get_prox_mode(void);
#endif

    /**************************************************************************//**
    * @brief Prints heart rate and spo2 to USB debug interface
    *****************************************************************************/
    void hrm_helper_output_debug_message(int16_t heart_rate, int16_t spo2);

    /**************************************************************************//**
    * @brief Prints samples to USB debug interface
    *****************************************************************************/
    void hrm_helper_output_raw_sample_debug_message(maxm86161_hrm_irq_sample_t *sample);
};


#endif /* MAXM86161_HELPER_H_ */