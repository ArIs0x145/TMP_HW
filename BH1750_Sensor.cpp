#include "BH1750_Sensor.h"

BH1750_Sensor::BH1750_Sensor(uint8_t address) : lightMeter_(address) {
}

bool BH1750_Sensor::begin(int sda_pin, int scl_pin) {
    Wire.begin(sda_pin, scl_pin);
    return lightMeter_.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
}

float BH1750_Sensor::getLightLevel() {
    return lightMeter_.readLightLevel();
}

bool BH1750_Sensor::isValid(float lux) {
    if (isnan(lux)) return false;
    if (lux < 0) return false;

    return true;
}

void BH1750_Sensor::printSensorValueToSerial(float lux) {
    Serial.println("Light: " + String(lux, 0) + " lux");
}