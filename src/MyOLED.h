//
// Created by Admin on 2022/8/16.
//

#ifndef ESP32_C3_MYOLED_H
#define ESP32_C3_MYOLED_H

#include "Switch.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "MyPIN.h"

class MyOLED {
public:
    static void initOLED();

    static void clearOLED();

    static void showTemperatureViaOLED(float humidity, float temperature);

    static void showWiFiStatus(IPAddress ipAddress);
};


#endif //ESP32_C3_MYOLED_H
