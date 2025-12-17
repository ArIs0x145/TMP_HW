#ifndef DHT11_SENSOR_H
#define DHT11_SENSOR_H

#include "DHT.h"

class DHT11_Sensor {
    private:
        DHT dht_;
        
    public:
        DHT11_Sensor(uint8_t pin, uint8_t type);

        void begin();
        float getTemperature();
        float getHumidity();
        bool isValid(float temperature, float humidity);
        void printSensorValuesToSerial(float temperature, float humidity);
};

#endif