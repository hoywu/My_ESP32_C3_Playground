//
// Created by Admin on 2022/8/16.
//

#ifndef ESP32_C3_MYWIFI_H
#define ESP32_C3_MYWIFI_H

#include "PrivateConstants.h"
#include "Switch.h"
#if USE_OLED == 1
#include "MyOLED.h"
#endif
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <sstream>

extern WiFiClientSecure client;

class MyWiFi {
public:
    static void ConnectWiFi();
    static bool ConnectServer();
    static std::string UploadViaWiFi(std::string data);
    static void setTime();
};


#endif //ESP32_C3_MYWIFI_H
