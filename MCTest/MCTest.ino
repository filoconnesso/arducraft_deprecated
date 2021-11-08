#include "Arducraft.h"

#define pb1 0
#define pb2 1
#define pb3 2
#define pingPin 23

Minecraft mc;
Debouncer db1;
Debouncer db2;
Debouncer db3;
Debouncer ping;

void setup() {
  Serial.begin(115200);
  mc.deamonAttach(&Serial);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  db1.begin(pb1);
  db2.begin(pb2);
  db3.begin(pb3);
  ping.begin(pingPin);
}

void loop() {

  mc.run();

  String cmd = mc.readMessage();

  if (mc.ifContainsWord(cmd, "ledon")) {
    digitalWrite(13, HIGH);
    //mc.writeMessage("led is on!");
  }

  if (mc.ifContainsWord(cmd, "ledoff")) {
    digitalWrite(13, LOW);
    //mc.writeMessage("led is off!");
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

  if (mc.botIsDead()) {
    mc.writeMessage("I am dead!");
  }

  if (mc.botHealthIsChanged()) {
    mc.writeMessage("My health has changed!");
  }

  if (db1.debounce())
  {
    mc.setWeather(1);
  }

  if (db2.debounce())
  {
    mc.setWeather(2);
  }

  if (db3.debounce())
  {
    mc.setWeather(3);
  }
  if (ping.debounce())
  {
    mc.gameMode("NobleJunglist", 2);
  }
}
