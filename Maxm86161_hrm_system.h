#pragma once

#include "Wire.h"
#include "hrm_helper.h"
#include "maxm86161_spo2.h"

#define HRM_DEMO_NAME "AYSE_HRM Demo"
#define HRM_DEMO_VERSION "1.0.0"

typedef enum hrm_spo2_state
{
   HRM_STATE_IDLE,
   HRM_STATE_NOSIGNAL,
   HRM_STATE_ACQUIRING,
   HRM_STATE_ACTIVE,
   HRM_STATE_INVALID
}hrm_spo2_state_t;

class Maxm86161_hrm_system
{
private:
   /* data */
public:
   maxm_hrm_handle_t *hrmHandle;
   /** Data Storage memory bock required by the maxm86161 hrm algorithm */
   mamx86161_hrm_data_storage_t hrm_data_storage;
   maxm86161_spo2_data_storage_t spo2_data;
   maxm86161_data_storage_t data_storage;
   maxm86161_hrm_helper hrm_helper;

   /** Heart Rate result from the si117xhrm algorithm */
   int16_t heart_rate;

   /** SpO2 result from the si117xhrm algorithm */
   int16_t spo2;

   int32_t hrm_status = 0;

   bool hrm_contac_status = false;

   mamx86161_hrm_data_t hrm_data;

   /** Flag used to indicate HRM/SpO2 state */
   volatile hrm_spo2_state_t hrm_spo2_state = HRM_STATE_IDLE;

   Maxm86161_hrm_system(){};
   ~Maxm86161_hrm_system(){};

   /**************************************************************************//**
   * @brief Initialize the HRM application.
   *****************************************************************************/
   int32_t hrm_init(void);

   /**************************************************************************//**
   * @brief Restart the HRM application.
   *****************************************************************************/
   int32_t hrm_restart(void);

   /**************************************************************************//**
   * @brief Pause the HRM application, must be use after init.
   *****************************************************************************/
   int32_t hrm_pause(void);

   /**************************************************************************//**
   * @brief HRM process main loop.
   *****************************************************************************/
   void hrm_loop_process(void);

   /**************************************************************************//**
   * @brief This function returns the current heart rate.
   *****************************************************************************/
   int16_t hrm_get_heart_rate(void);

   /**************************************************************************//**
   * @brief This function returns the current finger contact status.
   *****************************************************************************/
   bool hrm_get_status(void);

   /**************************************************************************//**
   * @brief This function returns the current SpO2.
   *****************************************************************************/
   int16_t hrm_get_spo2(void);


   
};
