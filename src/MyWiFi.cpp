//
// Created by Admin on 2022/8/16.
//

#include "MyWiFi.h"

WiFiClientSecure client;

void MyWiFi::ConnectWiFi() {
    const char *ssid = MyWiFiSSID;
    const char *password = MyWiFiPWD;
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
#if DEBUG_MODE == 1
    Serial.println("WiFi Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
#endif
#if USE_OLED == 1
    MyOLED::showWiFiStatus(WiFi.localIP());
#endif
    setTime();
}

bool MyWiFi::ConnectServer() {
    client.stop();
    client = WiFiClientSecure();
#if INSECURE_TLS == 1
    client.setInsecure();
#elif INSECURE_TLS == 0
    client.setCACert(MyRootCA);
#endif
    if (!client.connect(MyHost, 443)) {
        return false;
    }
    return true;
}

std::string MyWiFi::UploadViaWiFi(std::string data) {
    if (!client.connected()) {
        if (!ConnectServer()) {
            return "";
        }
    }

    // We now create a URI for the request
    String url = MyPostURL;

#if DEBUG_MODE == 1
    Serial.print("Requesting URL: ");
    Serial.println(url);
#endif

    // This will send the request to the server
    String httpRequest = String("POST ") + url + " HTTP/1.1\r\n" +
                         "Host: " + MyHost + "\r\n" +
                         "User-Agent: ESP32-C3/1.0\r\n" +
                         "Connection: keep-alive\r\n" +
                         "Content-Length: " + data.length() + "\r\n" +
                         "\r\n" +
                         data.data() + "\r\n";
//#if DEBUG_MODE == 1
//    Serial.println(httpRequest);
//#endif
    client.print(httpRequest);

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
#if DEBUG_MODE == 1
            Serial.println(">>> Client Timeout !");
#endif
            client.stop();
            return "";
        }
    }

    std::stringstream receiveData;
    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
        String line = client.readStringUntil('\r');
        receiveData << line.c_str();
//#if DEBUG_MODE == 1
//        Serial.print(line);
//#endif
    }

    //client.stop();

    std::string ret = receiveData.str();
    if (ret.find("HTTP/1.1 200 OK") == std::string::npos) {
        return "";
    }
    if (ret.find("\n\n") + 2 >= ret.size()) {
        return "";
    }
    ret.erase(0, ret.find("\n\n") + 2);
    if (ret.at(ret.size() - 1) != '\n') {
        ret.append("\n");
    } else {
        if (ret.at(ret.size() - 2) == '\n') {
            ret.erase(ret.size() - 1);
        }
    }
    return ret;
}

void MyWiFi::setTime() {
    configTime(0, 0, "ntp1.aliyun.com", "ntp2.aliyun.com", "ntp3.aliyun.com");
}
