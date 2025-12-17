#include "Config.h"
#include "DHT11_Sensor.h"
#include "BH1750_Sensor.h"
#include "Network_Manager.h"
#include "TFT_Display.h"
#include <ThingSpeak.h>

DHT11_Sensor dhtSensor(DHT_PIN, DHT_TYPE);
BH1750_Sensor lightSensor(BH1750_ADDRESS);
Network_Manager network(WIFI_SSID, WIFI_PASSWORD);
// Network_Manager network(WIFI_SSID, WIFI_IDENTITY, WIFI_USERNAME, WIFI_EAP_PASSWORD); // 802.1x 備用

TFT_Display tftDisplay;
WiFiClient wifiClient;

unsigned long lastTime = 0; // 非阻塞計時

// --- 讀取感測器 ---
SensorData readSensors() {
    SensorData data;
    data.temperature = dhtSensor.getTemperature();
    data.humidity = dhtSensor.getHumidity();
    data.lux = lightSensor.getLightLevel();
    
    bool dhtValid = dhtSensor.isValid(data.temperature, data.humidity);
    bool luxValid = lightSensor.isValid(data.lux);
    
    data.isValid = dhtValid && luxValid;
    
    if (dhtValid) dhtSensor.printSensorValuesToSerial(data.temperature, data.humidity);
    else Serial.println("DHT Read Error");
    
    if (luxValid) lightSensor.printSensorValueToSerial(data.lux);
    else Serial.println("BH1750 Read Error");
    
    return data;
}

// --- UI ---
void refreshUI(const SensorData& data) {
    tftDisplay.clear();

    String tempStr = "Temp: " + String(data.temperature, 1) + String((char)247) + "C";
    String humStr = "Humi: " + String(data.humidity, 1) + " %";
    String luxStr = "Lite: " + String(data.lux, 0) + " lux";

    uint16_t tempColor = data.isValid ? TFT_RED : TFT_DARKGREY;

    tftDisplay.showText(tempStr, 10, 20, tempColor, 4);
    tftDisplay.showText(humStr,  10, 50, TFT_BLUE, 4);
    tftDisplay.showText(luxStr,  10, 80, TFT_YELLOW, 4);
}

// --- 上傳雲端 ---
void uploadToCloud(const SensorData& data) {
    ThingSpeak.setField(6, data.lux);
    ThingSpeak.setField(7, data.temperature);
    ThingSpeak.setField(8, data.humidity);

    int httpCode = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_KEY);

    if (httpCode == 200) {
        Serial.println("[Cloud] Channel update successful.");
    } else {
        Serial.println("[Cloud] Update failed. HTTP Code: " + String(httpCode));
    }
}

// --- Setup ---
void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    
    dhtSensor.begin();
    lightSensor.begin(BH1750_SDA_PIN, BH1750_SCL_PIN);
    tftDisplay.begin(TFT_ROTATION);
    
    tftDisplay.showText("System Starting...", 10, 50, TFT_GREEN, 2);

    Serial.println("Connecting to WiFi...");
    if (network.connect()) {
        Serial.println("WiFi Connected!");
        tftDisplay.clear();
        tftDisplay.showText("WiFi Connected!", 10, 50, TFT_GREEN, 2);
    } else {
        Serial.println("WiFi Failed!");
        tftDisplay.showText("WiFi Failed!", 10, 50, TFT_RED, 2);
    }
    
    ThingSpeak.begin(wifiClient);
    
    delay(1000); 
}

// --- Loop ---
void loop() {
    if (!network.isConnected()) {
        Serial.println("WiFi lost, reconnecting...");
        network.connect();
    }

    if (millis() - lastTime > LOOP_DELAY_MS) {
        lastTime = millis();
        
        Serial.println("\n--- Sampling ---");

        // 1. 讀取
        SensorData currentData = readSensors();

        // 2. 顯示
        refreshUI(currentData);

        // 3. 上傳
        if (currentData.isValid && network.isConnected()) {
            uploadToCloud(currentData);
        } else {
            if(!currentData.isValid) Serial.println("Skipping upload: Invalid Sensor Data");
        }
    }
}