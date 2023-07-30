## Summary
This code is for maxm86161 development in arduino/ESP32, a modified version for the maxm86161 driver by siliconlabs https://github.com/SiliconLabs/platform_hardware_drivers/tree/master/bio_sensor_maxm86161. The original repo is on other platform, this repo tranfer the driver to ESP32 or arduino platform. Test on ESP32.

## Getting Started

**hrm_init()** : Configure and initialize the device./n
**hrm_pause()** : Stop the device for now./n
**hrm_restart()** : Restart the device./n
**hrm_loop_process()** : This is process the data in the loop; Call every frame./n
**hrm_get_heart_rate()** : Get the heart rate./n
**hrm_get_spo2()** : Get the SPO2./n
**hrm_get_status()** : Get the touch status.

Config file 
APP_QUEUE_SIZE : Sample rate;
VIEW_DEBUG_SAMPLE : Show each sample data;

## Set up
- EN - Connect to High/ IO4 / set as High (Important!)
- VCC - 3.3v
- GND
- SCL
- SDA


## Reference
SiliconLabs
https://github.com/SiliconLabs/platform_hardware_drivers/tree/master/bio_sensor_maxm86161
https://github.com/SiliconLabs/bluetooth_applications/tree/master/bluetooth_explorer_kit_i2c_bio_sensor

## License
This project is licensed under the zlib License

