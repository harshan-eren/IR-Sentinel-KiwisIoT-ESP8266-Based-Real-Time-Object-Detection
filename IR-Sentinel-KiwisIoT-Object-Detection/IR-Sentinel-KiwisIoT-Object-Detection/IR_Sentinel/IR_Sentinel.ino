/*
 * Project: IR Sentinel KiwisIoT
 * Board: ESP8266 NodeMCU
 * Sensor: IR obstacle detection module (digital output on D6)
 *
 * NOTE: Adjust the logic below to match your module. Most IR obstacle
 * modules pull DO LOW when an object is detected.
 */

#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

const char* ssid  = "YOUR_WIFI_NAME";
const char* pass  = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_DASHBOARD_TOPIC_ID";

#define IR_PIN D6

KiwisIoT kiwisiot(ssid, pass, topic);

void sendIRStatus() {
  int state = digitalRead(IR_PIN);
  String status = (state == LOW) ? "DETECTED" : "NOT DETECTED";

  Serial.print("IR Status: ");
  Serial.println(status);

  kiwisiot.send("0", status);
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);

  Serial.println("Connecting to KiwisIoT...");
  kiwisiot.begin();
  Serial.println("Starting IR monitoring...");
}

void loop() {
  kiwisiot.run();

  static unsigned long lastSend = 0;
  if (millis() - lastSend >= 1000) {
    lastSend = millis();
    sendIRStatus();
  }

  delay(50);
}
