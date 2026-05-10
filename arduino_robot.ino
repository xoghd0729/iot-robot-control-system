// IoT Robot Control System — Motor Controller
// 서버로부터 방향 명령을 받아 Stepper Motor를 제어

#include "WiFiEsp.h"
#include <Stepper.h>

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

char ssid[] = "IoT";
char pass[] = "qwer1234";
int status = WL_IDLE_STATUS;

const int STEPS = 2048;
Stepper stepper(STEPS, 8, 10, 9, 11);
WiFiEspClient client;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Connecting to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("Connected to network");
  stepper.setSpeed(15);
}

void loop() {
  if (client.connect("192.168.1.92", 8080)) {
    // HTTP GET 요청 — 서버에서 방향 명령 폴링
    client.println("GET /find?id=1 HTTP/1.1");
    client.println("Host: 192.168.1.92");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      if (client.available()) {
        String direction = client.readStringUntil('\n');
        Serial.println(direction);

        // 방향 명령에 따른 모터 제어
        if (direction == "UP")    stepper.step(STEPS);
        else if (direction == "DOWN")  stepper.step(-STEPS);
        else if (direction == "LEFT")  stepper.step(-STEPS / 2);
        else if (direction == "RIGHT") stepper.step(STEPS / 2);
        else if (direction == "STOP")  stepper.setSpeed(0);
      }
    }

    client.stop();
  } else {
    Serial.println("Connection failed");
  }

  delay(1000);
}
