/*
* Connects to a Wifi network and sends UDP messages based on 4 buttons.
*/

#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define PIN_BTN_1 D2
#define PIN_BTN_2 D3
#define PIN_BTN_3 D0
#define PIN_BTN_4 D1
#define PIN_LED D10

const char ssid[] = "Headrush Servant";
const char pass[] = "dG4=ZWgXDaaj2Q-5";
const char* servantIP = "192.168.169.1";
const int servantPort = 18788;
const char* MSG_SCENE1 = "button_scene1";
const char* MSG_SCENE2 = "button_scene2";
const char* MSG_SCENE3 = "button_scene3";
const char* MSG_SCENE4 = "button_scene4";

int btn1;
int btn2;
int btn3;
int btn4;

WiFiUDP Udp;

bool buttonPressed = false;

void blink(int times = 1, int millis = 200) {
  while (times-- > 0) {
    // Serial.print("Blink " + times);
    digitalWrite(PIN_LED, LOW);
    delay(millis);
    digitalWrite(PIN_LED, HIGH);
  }
}

void sendUdpMessage(const char* message) {
  // Serial.println("Sending UDP message '" + message + "'");
  if (!buttonPressed) {
    Udp.beginPacket(servantIP, servantPort);
    int i = 0;
    while (message[i] != 0)
      Udp.write((uint8_t) message[i++ ]);
    Udp.endPacket();
    // Serial.println("'" + message + "' sent!");
    blink();
    buttonPressed = true;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setting pins");
  pinMode(PIN_BTN_1, INPUT_PULLUP);
  pinMode(PIN_BTN_2, INPUT_PULLUP);
  pinMode(PIN_BTN_3, INPUT_PULLUP);
  pinMode(PIN_BTN_4, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);

  // WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(200);
  }
  blink(5);
  const char* msg = "Remote connected!";
  sendUdpMessage(msg);
  Serial.println("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  btn1 = digitalRead(PIN_BTN_1);
  btn2 = digitalRead(PIN_BTN_2);
  btn3 = digitalRead(PIN_BTN_3);
  btn4 = digitalRead(PIN_BTN_4);
  if (btn1 == LOW) {
    sendUdpMessage(MSG_SCENE1);
  } else if (btn2 == LOW) {
    sendUdpMessage(MSG_SCENE2);
  } else if (btn3 == LOW) {
    sendUdpMessage(MSG_SCENE3);
  } else if (btn4 == LOW) {
    sendUdpMessage(MSG_SCENE4);
  } else {
    buttonPressed = false;
  }

  delay(100);
}
