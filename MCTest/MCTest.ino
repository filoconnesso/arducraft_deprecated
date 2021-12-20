// Check we are using GDB Debugging and include the additional code
#ifdef VM_DEBUG_GDB
#include <TeensyDebug.h>
#endif

#include "Arducraft.h"

#define BUTTON 8
#define LED 13

Minecraft mc;
MinecraftButton mcbutton1(BUTTON, INPUT_PULLUP);
MinecraftSequencer createLine;
MinecraftSequencer createLine1;
MinecraftSequencer createLine2;
MinecraftSequencer createLine3;


void setup() {
#ifdef VM_DEBUG_GDB
  while (!SerialUSB1) {}    // Wait for Debugger connect
  debug.begin(SerialUSB1);  // Start Debug Serial e.g. COM11
#endif
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  mc.deamonAttach(&Serial);
  createLine.addTask([] { mc.placeBlock(RED_TERRACOTTA); });
  createLine.addTask([] { mc.botGoForward(); });
  createLine1.addTask([] { mc.placeBlock(GREEN_TERRACOTTA); });
  createLine1.addTask([] { mc.botGoLeft(); });
  createLine2.addTask([] { mc.placeBlock(PURPLE_TERRACOTTA); });
  createLine2.addTask([] { mc.botGoBack(); });
  createLine3.addTask([] { mc.placeBlock(BROWN_TERRACOTTA); });
  createLine3.addTask([] { mc.botGoRight(); });
}

void loop() {

  mc.run();
  createLine.run();
  createLine1.run();
  createLine2.run();
  createLine3.run();

  String cmd = mc.readMessage();

  if (cmd.indexOf("ledon") > -1) {
    digitalWrite(LED, HIGH);
  }

  if (cmd.indexOf("ledoff") > -1) {
    digitalWrite(LED, LOW);
  }

  /*mcbutton1.pressed([] {
    createLine.go(5, 500, [] {
      createLine1.go(5, 500, [] {
        createLine2.go(5, 500, [] {
          createLine3.go(5, 500, [] {
            mc.waitBot();
            mc.botJump();
          });
        });
      });
    }); //times, delay between tasks, end callback
    });*/

  static bool drawLine = false;

  /*
    static bool leverStatus = false;

    mcbutton1.pressed([] {
    leverStatus = !leverStatus;
    mc.lever(-49, 64, -221, leverStatus);
    //drawLine = true;
    });
  */

  if (drawLine) {
    for (int i = 1; i <= 5; i++) {
      mc.botGoForward();
      mc.waitBot();
      mc.placeBlock(BROWN_TERRACOTTA);
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
      mc.placeBlock(BROWN_TERRACOTTA);
      mc.waitBot();
    }
    for (int i = 1; i <= 5; i++) {
      mc.botGoRight();
      mc.waitBot();
      mc.placeBlock(BROWN_TERRACOTTA);
      mc.waitBot();
    }
    mc.botJump();
    drawLine = false;
  }

}
