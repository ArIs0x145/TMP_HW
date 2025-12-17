#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <WiFi.h>

class Network_Manager {
    private:
        String ssid_;
        String password_;
        String identity_;
        String username_;
        String eap_password_;
        
    public:
        Network_Manager(const String& ssid, const String& password);
        Network_Manager(const String& ssid, const String& identity, const String& username, const String& eap_password);
        
        bool connect();
        bool isConnected();
};

#endif