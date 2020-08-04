#include "ESP8266.h"

#define SSID        ""
#define PASSWORD    ""
#define HOST_NAME   ""
#define HOST_PORT   23

#define BT_RXD 2 
#define BT_TXD 3 

SoftwareSerial ESP_wifi(BT_RXD, BT_TXD);
ESP8266 wifi(ESP_wifi);

void setup() {
	Serial.begin(115200);
	Serial.println("setup start");

	wifi.restart();

	if (wifi.kick()) {
		Serial.println("esp8266 is alive");
	}
	else {
		Serial.println("esp8266 is not alive");
	}

	if (wifi.setOprToStation()) {
		Serial.println("to station mode");
	}
	else {
		Serial.println("to station mode error");
	}

	if (wifi.disableMUX()) {
		Serial.println("single ok");
	}
	else {
		Serial.println("single err");
	}

	if (wifi.joinAP(SSID, PASSWORD)) {
		Serial.println("Join AP success");
		Serial.print("IP:");
		Serial.println(wifi.getLocalIP().c_str());
	}
	else {
		Serial.println("Join AP failure");
	}

	Serial.println("setup end");
	Serial.println();
}

void loop() {
	uint8_t buffer[128] = { 0 };

	if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
		Serial.println("create tcp ok");
	}
	else {
		Serial.println("create tcp err");
	}

	char* str = "Hello, this is client!";
	wifi.send((const uint8_t*)str, strlen(str));

	uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
	if (len > 0) {
		Serial.print("Received:[");
		for (uint32_t i = 0; i < len; i++) {
			Serial.print(char(buffer[i]));
		}
		Serial.println("]");
	}

	if (wifi.releaseTCP()) {
		//Serial.println("release tcp ok");
	}
	else {
		Serial.println("release tcp err");
	}
	delay(5000);
}