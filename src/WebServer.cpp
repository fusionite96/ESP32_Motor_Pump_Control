
#include "WebServer.h"
#include "MotorControl.h"
#include "UserManagement.h"
#include "LogManagement.h"
#include "Variables.h"
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
String authToken = "secure-token";  // simplified token

void handleLogin() {
  if (server.method() == HTTP_POST) {
    DynamicJsonDocument doc(256);
    deserializeJson(doc, server.arg("plain"));
    String user = doc["username"];
    String pass = doc["password"];
    if (validateUser(user, pass)) {
      DynamicJsonDocument res(128);
      res["token"] = authToken;
      res["role"] = getUserRole(user);
      String body;
      serializeJson(res, body);
      server.send(200, "application/json", body);
    } else {
      server.send(403, "text/plain", "Unauthorized");
    }
  }
}

void handleMotorStart() {
  if (server.hasHeader("Authorization")) {
    DynamicJsonDocument doc(128);
    deserializeJson(doc, server.arg("plain"));
    int timer = doc["timer"];
    start_motor("user", timer);
    server.send(200, "text/plain", "Started");
  }
}

void handleMotorStop() {
  stop_motor("user");
  server.send(200, "text/plain", "Stopped");
}

void handleLogs() {
  String logs = getFormattedLogs();
  server.send(200, "application/json", logs);
}

void initWebServer() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/api/login", handleLogin);
  server.on("/api/motor/start", handleMotorStart);
  server.on("/api/motor/stop", handleMotorStop);
  server.on("/api/logs", handleLogs);
  server.begin();

  webSocket.begin();
  webSocket.onEvent([](uint8_t num, WStype_t type, uint8_t *payload, size_t len) {
    if (type == WStype_TEXT) {
      Serial.printf("[WS] %s
", payload);
    }
  });
}

void handleWebSocket() {
  webSocket.loop();
}

void broadcastMotorStatus(bool isRunning, int timer_value) {
  DynamicJsonDocument doc(128);
  doc["type"] = "MOTOR_STATUS";
  doc["isRunning"] = isRunning;
  doc["timer"] = timer_value;
  String msg;
  serializeJson(doc, msg);
  webSocket.broadcastTXT(msg);
}
