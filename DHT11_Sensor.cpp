#include "DHT11_Sensor.h"

DHT11_Sensor::DHT11_Sensor(uint8_t pin, uint8_t type) : dht_(pin, type) {
}

void DHT11_Sensor::begin() {
    dht_.begin();
}

float DHT11_Sensor::getTemperature() {
    return dht_.readTemperature();
}

float DHT11_Sensor::getHumidity() {
    return dht_.readHumidity();
}

bool DHT11_Sensor::isValid(float temperature, float humidity) {
    return !(isnan(temperature) || isnan(humidity));
}

void DHT11_Sensor::printSensorValuesToSerial(float temperature, float humidity) {
    Serial.println("Temperature: " + String(temperature, 1) + " C");
    Serial.println("Humidity: " + String(humidity, 1) + " %");
}