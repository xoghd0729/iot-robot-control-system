# iot-robot-control-system

> Arduino + WiFi 기반 IoT 로봇 원격 제어 시스템

Arduino Uno와 WiFi 모듈을 연결해 백엔드 서버와 HTTP 통신하는 IoT 시스템입니다. 서버의 방향 명령에 따라 Stepper Motor를 제어하고, 버튼 입력으로 로봇 위치를 서버에 전송합니다.

---

## 사용 기술

- Arduino Uno / C++
- WiFiEsp 라이브러리 (SoftwareSerial, 핀 2·3)
- HTTP/1.1 (TCP 소켓 직접 구현)
- Stepper Motor 28BYJ-48 (2048 steps/rev)

---

## 시스템 흐름

```
[백엔드 서버]
    │ HTTP GET /find?id=1
    │ 응답: "UP" / "DOWN" / "LEFT" / "RIGHT" / "STOP"
    ▼
[arduino_robot.ino] → Stepper Motor 방향 제어

[arduino_gps.ino]
    ├── 버튼 (A1~A5) 입력 감지
    └── HTTP GET /robot?id=N&x=X&y=Y → 서버 전송
```

---

## 파일 구성

| 파일 | 설명 |
|------|------|
| `arduino_robot.ino` | 서버 명령 수신 → 모터 방향 제어 |
| `arduino_gps.ino` | 버튼 입력 → 위치 좌표 서버 전송 |

---

## 회로 구성

| 용도 | 핀 |
|------|----|
| WiFi RX/TX | 2, 3 (SoftwareSerial) |
| Stepper Motor | 8, 9, 10, 11 |
| 위치 버튼 | A1~A5 |

---

## 배운 점

라이브러리가 HTTP 추상화를 제공하지 않아 `GET /find?id=1 HTTP/1.1`부터 `Host:`, `Connection: close` 헤더까지 직접 문자열로 작성했습니다. 덕분에 브라우저나 axios가 자동으로 처리해주는 HTTP 프로토콜 구조를 직접 이해하게 됐고, 네트워크 통신의 기초를 실습 수준에서 체득한 경험이었습니다.

하드웨어와 소프트웨어가 함께 동작하는 시스템을 처음 구현해보면서, 코드 버그와 하드웨어 배선 문제를 동시에 디버깅하는 경험을 했습니다.

---

## 어려웠던 점

서버 응답을 `readStringUntil('\n')`으로 읽는 과정에서 HTTP 응답 헤더(`HTTP/1.1 200 OK`, `Content-Type: ...`)까지 함께 읽혀 방향 명령어를 파싱하는 데 어려움이 있었습니다. HTTP 응답 구조를 정확히 이해하지 못한 상태에서 구현하다 보니 발생한 문제였습니다.

또한 WiFi 연결이 불안정할 때 재연결 처리 로직이 없어서, 연결이 끊기면 수동으로 재시작해야 했습니다.

---

## 아쉬운 점 및 개선 방향

- 1초마다 서버에 요청하는 폴링(Polling) 방식이어서 명령 지연이 발생합니다. WebSocket 방식으로 전환하면 실시간 제어가 가능하지만, 아두이노의 메모리 제한 때문에 구현이 까다롭습니다.
- WiFi 연결 끊김 시 자동 재연결 로직이 없어 안정성이 부족합니다. `while(!client.connected()) { reconnect(); }` 형태의 재연결 루프가 필요합니다.
- HTTP 응답에서 바디만 파싱하는 로직을 추가하면 명령어 인식 정확도가 높아집니다.

---

## 추가로 공부해야 할 내용

- HTTP 응답 파싱 (헤더 / 바디 분리)
- MQTT 프로토콜 (IoT 표준 경량 메시지 프로토콜)
- 임베디드 시스템 메모리 관리
- WebSocket 기반 실시간 통신
- Raspberry Pi를 활용한 더 복잡한 IoT 시스템 구성
