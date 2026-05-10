# iot-robot-control-system

> Arduino + Spring Boot 기반 IoT 자율 로봇 제어 시스템 — DFS 미로 탐색 알고리즘으로 경로 계산 후 모터 원격 제어

Arduino와 Spring Boot 백엔드 서버를 연결한 IoT 시스템입니다. 서버가 5×5 그리드에서 DFS 재귀 알고리즘으로 최적 경로를 계산하고, HTTP API를 통해 Arduino에 방향 명령을 전달하면 Stepper Motor가 해당 방향으로 이동합니다.

---

## 사용 기술

**백엔드 서버**
- Spring Boot / Java
- REST API (GET /find, GET /robot, GET /map)
- DFS 재귀 미로 탐색 알고리즘
- Lombok

**Arduino (임베디드)**
- Arduino Uno / C++
- WiFiEsp 라이브러리 (SoftwareSerial, 핀 2·3)
- HTTP/1.1 (TCP 소켓 직접 구현)
- Stepper Motor 28BYJ-48 (2048 steps/rev)

---

## 시스템 구조

```
[Arduino - arduino_gps.ino]
    ├── 버튼 (A1~A5) 입력 감지
    └── HTTP GET /robot?id=N&x=X&y=Y → 서버에 위치 전송

[Spring Boot 서버 - MapController]
    │ MapServiceImpl.findDirections()
    │   └── DFS 재귀로 5×5 그리드 탐색
    │   └── 현재 위치 기준 다음 칸 결정
    │   └── "UP" / "DOWN" / "LEFT" / "RIGHT" / "STOP" 반환
    ▼
[Arduino - arduino_robot.ino]
    └── HTTP GET /find?id=1  (1초 폴링)
    └── 응답에 따라 Stepper Motor 방향 제어
```

---

## 미로 탐색 알고리즘

`MapServiceImpl`의 `findMap()` 메서드는 DFS 재귀 방식으로 5×5 그리드를 탐색합니다.

| 셀 값 | 의미 |
|-------|------|
| 0 | 통로 (PATHWAY) |
| 1 | 벽 / 로봇 위치 (WALL) |
| 2 | 막힌 경로 (BLOCKED) |
| 3 | 최적 경로 (PATH) |

로봇의 현재 위치에서 출구(N-1, N-1)까지 DFS로 경로를 탐색하고, 다음 칸의 색상이 PATH(3)인 방향을 명령으로 반환합니다.

---

## 파일 구성

| 파일 | 설명 |
|------|------|
| `arduino_robot.ino` | 서버 명령 수신 → 모터 방향 제어 |
| `arduino_gps.ino` | 버튼 입력 → 위치 좌표 서버 전송 |
| `server/src/.../MapController.java` | REST API 엔드포인트 |
| `server/src/.../MapServiceImpl.java` | DFS 미로 탐색 로직 |
| `server/src/.../MapRepositoryImpl.java` | 그리드 상태 및 로봇 위치 관리 |
| `server/src/.../Robot.java` | 로봇 위치 데이터 클래스 |

---

## 회로 구성

| 용도 | 핀 |
|------|----|
| WiFi RX/TX | 2, 3 (SoftwareSerial) |
| Stepper Motor | 8, 9, 10, 11 |
| 위치 버튼 | A1~A5 |

---

## 배운 점

라이브러리가 HTTP 추상화를 제공하지 않아 `GET /find?id=1 HTTP/1.1`부터 `Host:`, `Connection: close` 헤더까지 직접 문자열로 작성했습니다. 브라우저나 axios가 자동으로 처리해주는 HTTP 프로토콜 구조를 직접 이해하게 됐습니다.

서버에서 DFS 알고리즘을 구현하면서 재귀 함수의 백트래킹(BLOCKED_COLOR 복원) 동작 원리를 실제 경로 탐색 문제로 체감했습니다. 하드웨어 배선과 소프트웨어 버그를 동시에 디버깅하는 경험도 처음이었습니다.

---

## 어려웠던 점

서버 응답을 `readStringUntil('\n')`으로 읽는 과정에서 HTTP 응답 헤더까지 함께 읽혀 방향 명령어를 파싱하는 데 어려움이 있었습니다. WiFi 연결이 불안정할 때 재연결 처리 로직이 없어서 연결이 끊기면 수동으로 재시작해야 했습니다.

---

## 현재 문제점

- **HTTP 바디 파싱 오류**: `client.readStringUntil('\n')`으로 서버 응답을 읽으면 HTTP 응답 헤더(`HTTP/1.1 200 OK`, `Content-Type` 등)까지 같이 읽힙니다. "UP" 명령어를 파싱하기 전에 헤더를 건너뛰는 로직이 없어 방향 명령이 제대로 인식되지 않을 수 있습니다.
- **WiFi 재연결 로직 없음**: WiFi 자체 연결(`WiFi.begin()`)이 끊어진 경우를 처리하지 않아 실제 환경에서 네트워크가 불안정하면 재부팅 없이 복구가 불가능합니다.
- **모터 방향 로직 오류**: `UP`/`DOWN` 모두 `stepper.step(STEPS)` 동일 방향으로 구현되어 있습니다. `DOWN`은 `-STEPS`로 역방향이어야 합니다.
- **1초 폴링 간격**: 명령을 최대 1초 뒤에 수신하므로 실시간 제어가 불가능합니다.
- **서버 상태 비영속화**: `MapRepositoryImpl`이 메모리(HashMap)에만 상태를 저장하므로 서버 재시작 시 로봇 위치와 그리드가 초기화됩니다.

## 고민해야 할 점

- **폴링 vs 이벤트 기반**: 현재는 1초마다 서버에 요청하는 방식인데, MQTT처럼 서버가 클라이언트에 메시지를 푸시하는 방식으로 바꾸면 지연 없이 실시간 제어가 가능합니다. 하지만 아두이노의 메모리(2KB SRAM)로 MQTT 클라이언트를 구동할 수 있는지가 제약 요소입니다.
- **DFS vs BFS**: 현재 서버는 DFS로 경로를 탐색하는데, DFS는 최단 경로를 보장하지 않습니다. BFS로 변경하면 항상 최단 경로를 찾을 수 있습니다. 로봇 제어에서 최단 경로가 얼마나 중요한지에 따라 알고리즘 선택이 달라집니다.
- **엣지 컴퓨팅 가능성**: 방향 판단 로직을 서버에서 처리하는 게 맞는지, 아니면 아두이노에서 센서 값을 직접 판단해 자율 제어하는 방식이 더 적합한지 설계 관점에서 고민이 필요합니다.

## 아쉬운 점 및 개선 방향

- WebSocket 방식으로 전환하면 실시간 제어가 가능하지만, 아두이노의 메모리 제한 때문에 구현이 까다롭습니다.
- WiFi 연결 끊김 시 자동 재연결 로직(`while(!client.connected()) { reconnect(); }`)이 필요합니다.
- DFS 대신 BFS를 사용하면 최단 경로를 보장할 수 있고, A* 알고리즘으로 더 효율적인 탐색도 가능합니다.

---

## 추가로 공부해야 할 내용

- HTTP 응답 파싱 (헤더 / 바디 분리)
- MQTT 프로토콜 (IoT 표준 경량 메시지 프로토콜)
- BFS / A* 경로 탐색 알고리즘
- 임베디드 시스템 메모리 관리
- WebSocket 기반 실시간 통신
- Spring Boot JPA를 활용한 상태 영속화
