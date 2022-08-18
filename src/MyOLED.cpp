//
// Created by Admin on 2022/8/16.
//

#include "MyOLED.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
float previous_humidity;
float previous_temperature;

unsigned char wifi1_icon16x16[] =
        {
                0b00000000, 0b00000000, //
                0b00000111, 0b11100000, //      ######
                0b00011111, 0b11111000, //    ##########
                0b00111111, 0b11111100, //   ############
                0b01110000, 0b00001110, //  ###        ###
                0b01100111, 0b11100110, //  ##  ######  ##
                0b00001111, 0b11110000, //     ########
                0b00011000, 0b00011000, //    ##      ##
                0b00000011, 0b11000000, //       ####
                0b00000111, 0b11100000, //      ######
                0b00000100, 0b00100000, //      #    #
                0b00000001, 0b10000000, //        ##
                0b00000001, 0b10000000, //        ##
                0b00000000, 0b00000000, //
                0b00000000, 0b00000000, //
                0b00000000, 0b00000000, //
        };

void MyOLED::initOLED() {
    Wire.setPins(OLED_SDA_PIN, OLED_SCL_PIN);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    clearOLED();
}

void MyOLED::clearOLED() {
    display.clearDisplay();
    display.setTextSize(1, 1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
}

void MyOLED::showTemperatureViaOLED(float humidity, float temperature) {
    if (!isnan(humidity)) {
        display.setTextColor(SSD1306_BLACK);
        display.setCursor(54, 19);
        display.print(previous_humidity);
        display.print("%");
        display.setCursor(72, 27);
        display.print(previous_temperature);
        display.print("C");

        display.setTextColor(SSD1306_WHITE);
        display.setCursor(54, 19);
        display.print(humidity);
        display.println("%");
        display.setCursor(72, 27);
        display.print(temperature);
        display.println("C");
        display.display();
    }
    // clearOLED();
    display.setCursor(0, 19);
    display.print("Humidity:");
    display.print(humidity);
    display.println("%");
    display.print("Temperature:");
    display.print(temperature);
    display.println("C");
    display.display();

    previous_humidity = humidity;
    previous_temperature = temperature;
}

void MyOLED::showWiFiStatus(IPAddress ipAddress) {
    display.drawBitmap(112, 0, wifi1_icon16x16, 16, 16, SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("WiFi Connected");
    display.println(ipAddress);
    display.display();
}
