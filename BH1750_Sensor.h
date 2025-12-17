#ifndef BH1750_SENSOR_H
#define BH1750_SENSOR_H

#include <BH1750.h>
#include <Wire.h>

class BH1750_Sensor {
private:
    BH1750 lightMeter_;
    
public:
    BH1750_Sensor(uint8_t address = 0x23);
    
    bool begin(int sda_pin = 21, int scl_pin = 22);
    float getLightLevel();
    bool isValid(float lux);
    void printSensorValueToSerial(float lux);
};

#endif