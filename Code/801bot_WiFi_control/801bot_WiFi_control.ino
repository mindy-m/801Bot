#include <WiFi.h>
#include <WiFiAP.h>
#include <Arduino.h>

#include "src/ESPAsyncWebServer/ESPAsyncWebServer.h"
#include "src/ESP32-ESP32S2-AnalogWrite/Servo.h"

#include "html.h"
#include <Bonezegei_WS2812.h>

#define LED_COUNT 1

// ------ Begin User Settings ------
const char* ssid = "SECRET-AGENT";
const char* password = "your-password";

// const int rServoPin = 33;
// const int lServoPin = 34;

Bonezegei_WS2812 rgb(PIN_NEOPIXEL, LED_COUNT);

// const int rDeadzoneVal = 1500;
// const int lDeadzoneVal = 1500;

// const int turnFactor = 3;

// ------ End User Settings ------

// Servo servo = Servo();

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

int xValue = 0;
int yValue = 0;

void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  String message = (char*)data;

  if (message.startsWith("X")) {
    xValue = message.substring(1).toInt();
  } else if (message.startsWith("Y")) {
    yValue = message.substring(1).toInt();
  }

//  updateServos();
}

void setup() {
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);

  Serial.begin(115200);
  Serial.print("Begin");
  
  // Color stuff
  rgb.begin();

  // Servo stuff
  // servo.attach(lServoPin);
  // servo.attach(rServoPin);

  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not Found");
  });

  ws.onEvent(onEvent);
  server.addHandler(&ws);

  
  server.begin();

}
/*
void updateServos() {
  Serial.println("starting updateServos()");
  
  int rVal = yValue - (xValue/turnFactor);
  int lVal = yValue + (xValue/turnFactor);

  if(rVal > 100) rVal = 100;
  if(rVal < -100) rVal = -100;
  if(lVal > 100) lVal = 100;
  if(lVal < -100) lVal = -100;

  int rValue = map(rVal, -270, 270, 2000, 1000);
  int lValue = map(lVal, -270, 270, 1000, 2000);

  if((abs(rVal) > 10) || (abs(lVal) > 10)){
    servo.writeMicroseconds(lServoPin, lValue);
    servo.writeMicroseconds(rServoPin, rValue);
  }else{
    servo.writeMicroseconds(lServoPin, lDeadzoneVal);
    servo.writeMicroseconds(rServoPin, rDeadzoneVal);
    servo.pause();
  }
}
*/

/*
  Strip RGB LED Demo WS2812 LED 
  Author: Bonezegei (Jofel Batutay)
  Date: October 2023 
  Uses 24 bit Hex color format
  Note : The Colors used on this demo was not set to maximum since it will be too bright during testing
*/

void loop() {
  rgb.fill(0x0f0000);  //RED
  delay(1000);
  rgb.fill(0x0f00);  //GREEN
  delay(1000);
  rgb.fill(0x0f);  //BLUE
  delay(1000);
  rgb.fill(0x0);
  delay(1000);

  for (int a = 0; a < LED_COUNT; a++) {
    rgb.setPixel(a, 0x0f0000);
    delay(10);
  }

  for (int a = 0; a < LED_COUNT; a++) {
    rgb.setPixel(a, 0x0f00);
    delay(10);
  }

  for (int a = 0; a < LED_COUNT; a++) {
    rgb.setPixel(a, 0x0f);
    delay(10);
  }

  for (int a = 0; a < LED_COUNT; a++) {
    rgb.setPixel(a, a << 16);
    delay(20);
  }

  for (int a = 0; a < LED_COUNT; a++) {
    rgb.setPixel(a, a << 8);
    delay(20);
  }

  for (int a = 0; a < LED_COUNT; a++) {
    rgb.setPixel(a, a);
    delay(20);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill(a);  //BLUE
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill(a);  //BLUE
    delay(10);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill(a << 8);
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill(a << 8);
    delay(10);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill(a);
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill(a);
    delay(10);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill(a << 16);
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill(a << 16);
    delay(10);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill((a << 16) | (a << 8));
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill((a << 16) | (a << 8));
    delay(10);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill((a << 8) | a);
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill((a << 8) | a);
    delay(10);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill((a << 16) | a);
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill((a << 16) | a);
    delay(10);
  }

  //fade
  for (int a = 0; a < 96; a++) {
    rgb.fill((a << 8) | (a << 16) | a);
    delay(10);
  }
  for (int a = 96; a > 0; a--) {
    rgb.fill((a << 8) | (a << 16) | a);
    delay(10);
  }
}

