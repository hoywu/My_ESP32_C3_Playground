//
// Created by Admin on 2022/8/16.
//

#ifndef ESP32_C3_MYDHT_H
#define ESP32_C3_MYDHT_H

#include "Switch.h"
#if USE_OLED == 1
#include "MyOLED.h"
#endif
#include <DHT.h>
#include "MyPIN.h"

extern DHT dht;
extern float humidity;
extern float temperature;

class MyDHT {
public:
    static void ReadTemperature();
};


#endif //ESP32_C3_MYDHT_H
