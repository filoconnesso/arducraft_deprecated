#include "Arducraft.h"

Minecraft mc;


void setup() {
  Serial.begin(115200);
  mc.deamonAttach(&Serial);
  pinMode(13, OUTPUT);
}

void loop() {
  
  mc.run();

  String cmd = mc.readMessage();

  if(mc.ifContainsWord(cmd, "led4on")) {
    digitalWrite(13, HIGH);
  }

  if(mc.ifContainsWord(cmd, "led4off")) {
    digitalWrite(13, LOW);
  }

  mc.writeMessage(String(mc.getTime()));

}
