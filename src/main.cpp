#include "Switch.h"
#if USE_OLED == 1
#include "MyOLED.h"
#endif
#include "MyDHT.h"
#include "MyWiFi.h"

char sendDataBuffer[20];
std::string receiveData;

void setup() {
#if DEBUG_MODE == 1
    Serial.begin(115200, SERIAL_8E1);
    delay(2000);
#endif
#if USE_OLED == 1
    MyOLED::initOLED();
#endif
    MyWiFi::ConnectWiFi();
    MyWiFi::ConnectServer();
    dht.begin();
}

void loop() {
    MyDHT::ReadTemperature();
    snprintf(sendDataBuffer, sizeof(sendDataBuffer) - 1, "t:%.2f;h:%.2f;", temperature, humidity);
    receiveData = MyWiFi::UploadViaWiFi(sendDataBuffer);
#if DEBUG_MODE == 1
    Serial.println(receiveData.c_str());
#endif
    delay(10000);
}
