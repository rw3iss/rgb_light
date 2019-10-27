#ifndef APPSERVER_H
#define APPSERVER_H 1

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "vars.h"

class AppServer 
{
    public:
        AppServer();
        void checkClient();
        void handleClient(WiFiClient client);
        
    private:
        void setupWifiServer();
};

#endif
