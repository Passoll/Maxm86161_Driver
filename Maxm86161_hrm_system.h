#pragma once

#include "Wire.h"

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
