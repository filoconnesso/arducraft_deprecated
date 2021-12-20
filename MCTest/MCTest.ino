#include "Arducraft.h"

#define BUTTON 8
#define LED 13

Minecraft mc;
MinecraftButton mcbutton1(BUTTON, INPUT_PULLUP);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  mc.deamonAttach(&Serial);
}

void loop() {

  mc.run();

  String cmd = mc.readMessage();

  if (mc.ifContainsWord(cmd, "ledon")) {
    digitalWrite(LED, HIGH);
  }

  if (mc.ifContainsWord(cmd, "ledoff")) {
    digitalWrite(LED, LOW);
  }

  static bool drawLine = false;

  //static bool leverStatus = false;

  /*bool statuslever = mcbutton1.toggle();

  if (mcbutton1.release()) {
    mc.lever(-59, 64, -34, statuslever);
  }*/

  /*if(mcbutton1.press()) {
    //leverStatus = !leverStatus;
    //mc.lever(-49, 64, -221, leverStatus);
    //mc.writeMessage("button pressed!");
    } */

  if (mcbutton1.click()) {
    drawLine = true;
  }

  if (drawLine) {
    for (int i = 1; i <= 5; i++) {
      mc.botGoForward();
      mc.waitBot();
      mc.placeBlock(RED_TERRACOTTA);
      mc.waitBot();
    }
    for (int i = 1; i <= 5; i++) {
      mc.botGoLeft();
      mc.waitBot();
      mc.placeBlock(BROWN_TERRACOTTA);
      mc.waitBot();
    }
    for (int i = 1; i <= 5; i++) {
      mc.botGoBack();
      mc.waitBot();
      mc.placeBlock(YELLOW_TERRACOTTA);
      mc.waitBot();
    }
    for (int i = 1; i <= 5; i++) {
      mc.botGoRight();
      mc.waitBot();
      mc.placeBlock(GREEN_TERRACOTTA);
      mc.waitBot();
    }
    mc.botJump();
    drawLine = false;
  }

  //mc.writeMessage(String(mc.getWorldTime()));

}
