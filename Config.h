#ifndef CONFIG_H
#define CONFIG_H

// --- 系統設定 ---
#define SERIAL_BAUD_RATE 115200
#define LOOP_DELAY_MS 20000      // 每 20 秒執行一次任務

// --- DHT11 設定 ---
#define DHT_PIN 27
#define DHT_TYPE DHT11

// --- BH1750 設定 ---
#define BH1750_ADDRESS 0x23
#define BH1750_SDA_PIN 21
#define BH1750_SCL_PIN 22

// --- TFT 顯示設定 ---
#define TFT_ROTATION 1         // 1: 橫向 (Landscape)

// --- WiFi 設定 ---
#define WIFI_SSID "{你的 WiFi SSID}"           // 你的 WiFi SSID
#define WIFI_PASSWORD "{你的 WiFi 密碼}"     // 你的 WiFi 密碼

// 學校網路 (802.1x) 設定備用 (如果需要請自行取消註解並填入)
// #define WIFI_IDENTITY    "學號@cloud.dyu.edu.tw"
// #define WIFI_USERNAME    "學號"
// #define WIFI_EAP_PASSWORD "密碼"

// --- ThingSpeak 設定---
#define SECRET_CH_ID {你的 Channel ID} // 你的 Channel ID
#define SECRET_WRITE_KEY "{你的 Write API Key}"  // 你的 Write API Key

// --- Data ---
struct SensorData {
    float temperature = 0.0;
    float humidity = 0.0;
    float lux = 0.0;
    bool  isValid = false;
};

#endif