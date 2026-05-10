
#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

char ssid[] = "IoT";  // WiFi 네트워크 SSID
char pass[] = "qwer1234";           // WiFi 네트워크 비밀번호
int status = WL_IDLE_STATUS;          // WiFi 모듈 상태

WiFiEspClient client;

const int buttonPin = 7;  // 버튼 핀

int robotId = 10; // 로봇 ID
int robotX = 0; // 로봇 X 위치
int robotY = 3; // 로봇 Y 위치

const int MAP_SIZE = 5;

void setup() {  
  Serial.begin(9600);
  Serial1.begin(9600);

  // WiFi 모듈 초기화
  WiFi.init(&Serial1);

  // WiFi 네트워크에 연결
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("Connected to the network");

  pinMode(buttonPin, INPUT);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  robotId = random(10,100);
  digitalWrite(8, LOW);
  if (!digitalRead(A5)){
    Serial.print("A5-8 5\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 0, 0);
    }
    delay(100);
  } 
  if (!digitalRead(A4)){
    Serial.print("A4-8 4\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 0, 1);
    }
    delay(100);
  } 
  if (!digitalRead(A3)){
    Serial.print("A4-8 3\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 0, 2);
    }
     delay(100);
  }
  if (!digitalRead(A2)){
    Serial.print("A4-8 2\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 0, 3);
    }
     delay(100);
  }
  if (!digitalRead(A1)) {
     Serial.print("A1-8 1\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 0, 4);
    }
     delay(100);
  }
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  if (!digitalRead(A5)){
    Serial.print("A5-9 5\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 1, 0);
    }
    delay(100);
  } 
  if (!digitalRead(A4)){
    Serial.print("A4-9 4\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 1, 1);
    }
    delay(100);
  } 
  if (!digitalRead(A3)){
    Serial.print("A4-9 3\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 1, 2);
    }
     delay(100);
  }
  if (!digitalRead(A2)){
    Serial.print("A4-9 2\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 1, 3);
    }
     delay(100);
  }
  if (!digitalRead(A1)) {
     Serial.print("A1-9 1\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 1, 4);
    }
     delay(100);
  }
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  if (!digitalRead(A5)){
    Serial.print("A5-8 5\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 2, 0);
    }
    delay(100);
  } 
  if (!digitalRead(A4)){
    Serial.print("A4-8 4\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 2, 1);
    }
    delay(100);
  } 
  if (!digitalRead(A3)){
    Serial.print("A4-8 3\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 2, 2);
    }
     delay(100);
  }
  if (!digitalRead(A2)){
    Serial.print("A4-8 2\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 2, 3);
    }
     delay(100);
  }
  if (!digitalRead(A1)) {
     Serial.print("A1-8 1\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 2, 4);
    }
     delay(100);
  }
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  if (!digitalRead(A5)){
    Serial.print("A5-8 5\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 3, 0);
    }
    delay(100);
  } 
  if (!digitalRead(A4)){
    Serial.print("A4-8 4\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 3, 1);
    }
    delay(100);
  } 
  if (!digitalRead(A3)){
    Serial.print("A4-8 3\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 3, 2);
    }
     delay(100);
  }
  if (!digitalRead(A2)){
    Serial.print("A4-8 2\n");
     if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 3, 3);
    }
     delay(100);
  }
  if (!digitalRead(A1)) {
     Serial.print("A1-8 1\n");
    if (robotX >= 0 && robotX < MAP_SIZE && robotY >= 0 && robotY < MAP_SIZE) {
      sendGetRequest(robotId, 4, 4);
    }
     delay(100);
  }
  digitalWrite(11, HIGH);
}


void sendGetRequest(int id, int x, int y) {
  if (client.connect("192.168.1.16", 8080)) { // 서버 주소와 포트를 수정해야 합니다.
    Serial.println("Connected to server");

    // 서버로 GET 요청 및 로봇 위치 정보 보내기
    String request = "GET /robot?id=" + String(id) + "&x=" + String(x) + "&y=" + String(y) + " HTTP/1.1";
    client.println(request);
    client.println("Host: 192.168.1.16"); // 서버 주소를 여기에 입력
    client.println("Connection: close");
    client.println();
    Serial.println("Request sent");

    // 서버 응답을 확인하고 출력
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }
    }

    client.stop();
    Serial.println("Disconnected from server");
  } else {
    Serial.println("Connection to server failed");
  }
}
