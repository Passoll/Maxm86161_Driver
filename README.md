## Summary
This code is for maxm86161 development in arduino/ESP32, a modified version for the maxm86161 driver by siliconlabs https://github.com/SiliconLabs/platform_hardware_drivers/tree/master/bio_sensor_maxm86161. The original repo is on other platform, this repo tranfer the driver to ESP32 or arduino platform. Test on ESP32.
![image](https://github.com/Passoll/Maxm86161_Driver/assets/25281954/518df049-8f55-42f3-8fc2-4e7bd419df5c)

## Getting Started

**hrm_init()** : Configure and initialize the device.   
**hrm_pause()** : Stop the device for now.   
**hrm_restart()** : Restart the device.   
**hrm_loop_process()** : This is process the data in the loop; Call every frame.   
**hrm_get_heart_rate()** : Get the heart rate.   
**hrm_get_spo2()** : Get the SPO2.   
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

## Author
Peixi, Kaiming

## Reference
SiliconLabs
https://github.com/SiliconLabs/platform_hardware_drivers/tree/master/bio_sensor_maxm86161
https://github.com/SiliconLabs/bluetooth_applications/tree/master/bluetooth_explorer_kit_i2c_bio_sensor

## License
This project is licensed under the zlib License

