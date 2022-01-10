#include "Arducraft.h"

#define BUTTON 8
#define LED 13
#define LED_RAINING 7

Minecraft mc;
MinecraftButton mcbutton1(BUTTON, INPUT_PULLUP);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED_RAINING, OUTPUT);
  Serial.begin(115200);
  mc.deamonAttach(&Serial);
}

void loop() {

  mc.run();

  String cmd = mc.readMessage();

  if (cmd == "ledon") {
    digitalWrite(LED, HIGH);
  }

  if (cmd == "ledoff") {
    digitalWrite(LED, LOW);
  }

  static bool drawLine = false;

  if(mc.isRaining()) {
    digitalWrite(LED_RAINING, HIGH);
  } else {
    digitalWrite(LED_RAINING, LOW);
  }

  if (mcbutton1.click()) {
    drawLine = true;
  }

  if (drawLine) {
    for (int i = 1; i <= 5; i++) {
      mc.botGoForward();
      mc.waitBot();
      mc.placeBlock(RED_TERRACOTTA);
    }
    for (int i = 1; i <= 5; i++) {
      mc.botGoLeft();
      mc.waitBot();
      mc.placeBlock(BROWN_TERRACOTTA);
    }
    for (int i = 1; i <= 5; i++) {
      mc.botGoBack();
      mc.waitBot();
      mc.placeBlock(YELLOW_TERRACOTTA);
    }
    for (int i = 1; i <= 5; i++) {
      mc.botGoRight();
      mc.waitBot();
      mc.placeBlock(GREEN_TERRACOTTA);
    }
    mc.botJump();
    drawLine = false;
  }

}
