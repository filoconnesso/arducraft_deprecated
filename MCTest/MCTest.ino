#include "Arducraft.h"

bool draw_square = false;

#define BUTTON_PIN1 12
#define BUTTON_PIN2 11
#define BUTTON_PIN3 10
#define BUTTON_PING 9

Minecraft mc;

MinecraftButton mcbutton1(BUTTON_PIN1, INPUT_PULLUP);
MinecraftButton mcbutton2(BUTTON_PIN2, INPUT_PULLUP);
MinecraftButton mcbutton3(BUTTON_PIN3, INPUT_PULLUP);
MinecraftButton mcbuttonping(BUTTON_PING, INPUT_PULLUP);

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
    mc.writeMessage("Current World Time = " + String(mc.getWorldTime()));
    mc.writeMessage("My coords are x = " + String(mc.getBotPositionX()) + " y = " + String(mc.getBotPositionY()) + " z = " + String(mc.getBotPositionZ()));
  }

  if (mc.botIsDead()) {
    mc.writeMessage("I am dead!");
  }

  if (mc.botHealthIsChanged()) {
    mc.writeMessage("My health has changed!");
  }

  if (mcbutton1.pressed())
  {
    mc.setWeather(CLEAR);
    draw_square = true;
  }

  if (mcbutton2.pressed())
  {
    mc.setWeather(RAIN);
  }

  if (mcbutton3.pressed())
  {
    mc.setWeather(THUNDER);
  }

  if (mcbuttonping.pressed())
  {
    mc.writeMessage(String(mc.PingValue()));
  }

  if (draw_square) {
    for (int i = 0; i <= 9; i++) {
      mc.botGoForward();
      delay(300);
      mc.placeBlock(RED_TERRACOTTA);
      delay(100);
    }
    for (int i = 0; i <= 9; i++) {
      mc.botGoLeft();
      delay(300);
      mc.placeBlock(YELLOW_TERRACOTTA);
      delay(100);
    }
    for (int i = 0; i <= 9; i++) {
      mc.botGoBack();
      delay(300);
      mc.placeBlock(ORANGE_TERRACOTTA);
      delay(100);
    }
    for (int i = 0; i <= 9; i++) {
      mc.botGoRight();
      delay(300);
      mc.placeBlock(PINK_TERRACOTTA);
      delay(100);
    }
    mc.botJump();
    draw_square = false;
  }

}
