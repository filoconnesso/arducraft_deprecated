#include "Arducraft.h"

Minecraft mc;

void setup() {
  Serial.begin(115200);
  mc.deamonAttach(&Serial);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {

  mc.run();

  String cmd = mc.readMessage();

  if (mc.ifContainsWord(cmd, "ledon")) {
    digitalWrite(13, HIGH);
    mc.writeMessage("led is on!");
  }

  if (mc.ifContainsWord(cmd, "ledoff")) {
    digitalWrite(13, LOW);
    mc.writeMessage("led is off!");
  }

  if (mc.isRaining()) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

  if (mc.botIsSpawned()) {
    mc.writeMessage("I am spawned!");
    mc.writeMessage("Current World Time " + String(mc.getWorldTime()));
  }
  
  if (mc.botIsDeath()) {
    mc.writeMessage("I am dead!");
  }

  if (mc.botHealthIsChanged()) {
    mc.writeMessage("My health has changed!");
  }

}
