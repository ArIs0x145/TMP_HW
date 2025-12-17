#include "Network_Manager.h"

Network_Manager::Network_Manager(const String& ssid, const String& password)
    : ssid_(ssid), password_(password) {
}
Network_Manager::Network_Manager(const String& ssid, const String& identity, const String& username, const String& eap_password)
    : ssid_(ssid), identity_(identity), username_(username), eap_password_(eap_password) {}

bool Network_Manager::connect() {
    WiFi.mode(WIFI_STA);
    int attempts = 0;
    
    if (identity_.length() == 0) {
        // 一般 WiFi
        WiFi.begin(ssid_, password_);
        while (WiFi.status() != WL_CONNECTED && attempts < 20) {
            delay(500);
            attempts++;
        }
    } else {
        // 802.1x WiFi (學校/企業)
        WiFi.begin(ssid_, WPA2_AUTH_PEAP, identity_, username_, eap_password_);
        while (WiFi.status() != WL_CONNECTED && attempts < 60) {
            delay(500);
            attempts++;
        }
    }
    return isConnected();
}

bool Network_Manager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}