#include "Maxm86161_hrm_system.h"

/**************************************************************************//**
 * Local defines
 *****************************************************************************/

/**************************************************************************//**
 * Global variables
 *****************************************************************************/
/** Sensor handle for the maxm86161 hrm algorithm */


/** Heart Rate result from the si117xhrm algorithm */
static int16_t heart_rate;

/** SpO2 result from the si117xhrm algorithm */
static int16_t spo2;

static int32_t hrm_status = 0;

//static bool update_display = false;
static bool hrm_contac_status = false;

mamx86161_hrm_data_t hrm_data;

/** Flag used to indicate HRM/SpO2 state */
static volatile hrm_spo2_state_t hrm_spo2_state = HRM_STATE_IDLE;

/**************************************************************************//**
 * Local prototypes
 *****************************************************************************/
static void hrm_gpio_setup(void);

/**************************************************************************//**
 * @brief Initialize the HRM application.
 *****************************************************************************/
int32_t Maxm86161_hrm_system::hrm_init(void)
{
  /* Initialize peripherals*/
  hrm_gpio_setup();
  data_storage.spo2 = &spo2_data;
  data_storage.hrm = &hrm_data_storage;
  ////check the data id
  int err = maxm86161_hrm_initialize(&data_storage, &hrmHandle);

  if(err == MAXM86161_HRM_ERROR_INVALID_PART_ID ){
    Serial.println('No MAXM86161 is detected!');
    return err;
  }
  maxm86161_hrm_configure(hrmHandle, NULL, true);
  maxm86161_hrm_run(hrmHandle);
  return 1;
}

int32_t Maxm86161_hrm_system::hrm_pause(void)
{
  return maxm86161_hrm_pause();
}

int32_t Maxm86161_hrm_system::hrm_restart(void)
{
  return maxm86161_hrm_run(hrmHandle);;
}

/**************************************************************************//**
* @brief Setup GPIO, enable sensor isolation switch
*****************************************************************************/
static void hrm_gpio_setup(void)
{
  /* Enable GPIO clock */
  //CMU_ClockEnable(cmuClock_GPIO, true);
  pinMode(MAXM86161_EN_GPIO_PIN, OUTPUT);
  digitalWrite(MAXM86161_EN_GPIO_PIN, HIGH);
  // need delay to wait the Maxim ready before we can read and write to register
  delay(5);
}

/**************************************************************************//**
 * @brief HRM process main loop.
 *****************************************************************************/
void Maxm86161_hrm_system::hrm_loop_process(void)
{
  int16_t num_samples_processed;
  int32_t err;

  err = maxm86161_hrm_process(hrmHandle,
                              &heart_rate,
                              &spo2,
                              1,
                              &num_samples_processed,
                              &hrm_status, &hrm_data);
  
  switch (hrm_spo2_state) {
    case HRM_STATE_IDLE:
      //update_display = true;
      break;
    case HRM_STATE_ACQUIRING:
    case HRM_STATE_ACTIVE:
      if((err == MAXM86161_HRM_SUCCESS)
          && (hrm_status & MAXM86161_HRM_STATUS_FRAME_PROCESSED)) {
        hrm_status &= ~MAXM86161_HRM_STATUS_FRAME_PROCESSED;

#if (UART_DEBUG & HRM_LEVEL)
        hrm_helper_output_debug_message(heart_rate, spo2);
#endif

        //update_display = true;
        hrm_spo2_state = HRM_STATE_ACTIVE;
      }
#ifdef PROXIMITY
    else if ((hrm_status & MAXM86161_HRM_STATUS_FINGER_OFF)
        || (hrm_status & MAXM86161_HRM_STATUS_SPO2_FINGER_OFF)
        || (hrm_status & MAXM86161_HRM_STATUS_ZERO_CROSSING_INVALID)
        || (maxm86161_get_prox_mode())) {
#else
    else if ((hrm_status & MAXM86161_HRM_STATUS_FINGER_OFF)
        || (hrm_status & MAXM86161_HRM_STATUS_SPO2_FINGER_OFF)
        || (hrm_status & MAXM86161_HRM_STATUS_ZERO_CROSSING_INVALID)) {
#endif
      heart_rate = 0;
      spo2 = 0;
      //update_display = true;
      hrm_spo2_state = HRM_STATE_ACQUIRING;
    }
    break;

    default:
      break;
  }
  
}

/**************************************************************************//**
 * @brief This function returns the current heart rate.
 *****************************************************************************/
int16_t Maxm86161_hrm_system::hrm_get_heart_rate(void)
{
  return heart_rate;
}

/**************************************************************************//**
 * @brief This function returns the current finger contact status.
 *****************************************************************************/
bool Maxm86161_hrm_system::hrm_get_status(void)
{
  hrm_contac_status = (hrm_spo2_state == HRM_STATE_ACTIVE);
  return hrm_contac_status;
}

/**************************************************************************//**
 * @brief This function returns the SpO2.
 *****************************************************************************/
int16_t Maxm86161_hrm_system::hrm_get_spo2(void)
{
  return spo2;
}



