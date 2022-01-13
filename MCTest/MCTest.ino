//----------------------------------------------------------------------------//
/*
 *  Copyright (C) 2021  Filo Connesso - filoconnesso.it
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
//----------------------------------------------------------------------------//

/*
 * FILO CONNESSO MINECRAFT LIBRARY
 *
 *
 * Created by Alessandro Marcon (@alessandromrc) and Mirko Pacioni
 * November 2th 2021
 *
 */

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
  //mc.debugInformations();
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

  if (mc.isRaining()) {
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
