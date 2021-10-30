#include "Arducraft.h"

#define LED 13
#define LED2 12
#define BUTTON 8

Minecraft mc;

void setup() {
  Serial.begin(115200);
  mc.deamonAttach(&Serial);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {

  String cmd = mc.readMessage();

  bool led2on = mc.ifContainsWord(cmd, "led2on");
  bool led2off = mc.ifContainsWord(cmd, "led2off");

  if(cmd.indexOf("ledon") >= 0) {
    digitalWrite(LED, HIGH);
  }
  if(cmd.indexOf("ledoff") >= 0) {
    digitalWrite(LED, LOW);
  }

  if(led2on) {
    digitalWrite(LED2, HIGH);
  }
  if(led2off) {
    digitalWrite(LED2, LOW);
  }

  if(digitalRead(BUTTON) == LOW) {
    mc.writeMessage("hello, world!");
  }
  
}
