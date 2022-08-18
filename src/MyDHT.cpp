//
// Created by Admin on 2022/8/16.
//

#include "MyDHT.h"

float humidity;
float temperature;
DHT dht(DHT22_PIN, DHT22);

void MyDHT::ReadTemperature() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature)) {
//        Serial.println(F("Failed to read from DHT sensor!"));
        humidity = 0;
        temperature = 0;
        return;
    }
#if DEBUG_MODE == 1
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.print(F("%  Temperature: "));
    Serial.print(temperature);
    Serial.println(F("℃"));
#endif
#if USE_OLED == 1
    MyOLED::showTemperatureViaOLED(humidity, temperature);
#endif
}
