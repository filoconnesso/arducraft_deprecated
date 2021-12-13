#ifndef Arducraft_H
#define Arducraft_H

#include "Arduino.h"
#include "definitions/blocks.h"
#include "definitions/weather.h"
#include "definitions/game_modes.h"
#include "definitions/aliases.h"
#include "definitions/entities.h"


class MinecraftButton
{
  private:
    uint8_t btn;
    uint16_t state;
  public:
    MinecraftButton(uint8_t button, uint8_t mode) {
      btn = button;
      state = 0;
      pinMode(btn, mode);
    }
    bool pressed() {
      state = (state << 1) | digitalRead(btn) | 0xfe00;
      return (state == 0xff00);
    }
};


class Minecraft {
  private:
    unsigned long curMillis = millis();
    unsigned long prevMillis = millis();
    unsigned long timerMillis = 5;
    String lastMessage = "";
    bool HandShakeBoot = false;
    bool spawn, kicked, end, death, health, error = false;
    String errorMessage = "";
    unsigned long worldTime = 0;
    int botExperience, botHealth, botFood, botOxygen = 0;
    String botGameMode = "";
    bool raining = false;
    int pingValue;
    String Arduino_Cmd = "[ARDUINO CMD] ";
    String splitString(String string, char separator, int index)
    {
      int found = 0;
      int strIndex[] = {0, -1};
      int maxIndex = string.length() - 1;
      for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (string.charAt(i) == separator || i == maxIndex) {
        found++;
        strIndex[0] = strIndex[1] + 1;
        strIndex[1] = (i == maxIndex) ? i + 1 : i;
      }
    }
    return found > index ? string.substring(strIndex[0], strIndex[1]) : "";
  }
  public:
    Stream * serial;
    Minecraft() {
      prevMillis = millis();
    }
    float botPositionX, botPositionY, botPositionZ = 0;
    void deamonAttach(Stream * newserial);
    String readMessage();
    bool ifContainsWord(String message, String word);
    void writeMessage(String message);
    void setWorldTime(int value);
    void addWorldTime(int value);
    void setWeather(int weather_value);
    void teleportBotToPosition(float x, float y, float z);
    void teleportEntityToPosition(String entity, float x, float y, float z);
    void teleportBotToEntity(String entity);
    void teleportEntityToEntity(String f_entity, String s_entity);
    void gameMode(String entity, int mode_value);
    void createEntity(String entity);
    void run();
    int getWorldTime();
    String getErrorMessage();
    bool botIsSpawned();
    bool botIsKicked();
    bool botIsEnded();
    bool botIsDead();
    bool botHealthIsChanged();
    bool botErrorOccurred();
    int getBotExperienceLevel();
    int getBotHealthLevel();
    int getBotFoodLevel();
    int getBotOxygenLevel();
    String getBotGameMode();
    bool isRaining();
    bool botReady();
    int PingValue();
    double getBotPositionX();
    double getBotPositionY();
    double getBotPositionZ();
    void placeBlock(String block);
    void botGoForward();
    void botGoBack();
    void botGoLeft();
    void botGoRight();
    void botStop();
    void botJump();
};

void Minecraft::deamonAttach(Stream * newserial) {
  this -> serial = newserial;
}

String Minecraft::readMessage() {
  return lastMessage;
}

bool Minecraft::ifContainsWord(String message, String word) {
  bool response;
  if (message.indexOf(word) > -1) {
    response = true;
  } else {
    response = false;
  }
  return response;
}

void Minecraft::writeMessage(String message) {
  this -> serial -> print("/say ");
  this -> serial -> print(message);
  this -> serial -> print("\n");
}

void Minecraft::setWorldTime(int value) {
  this -> serial -> print("/time set ");
  this -> serial -> print(value);
  this -> serial -> print("\n");
}

void Minecraft::addWorldTime(int value) {
  this -> serial -> print("/time add ");
  this -> serial -> print(value);
  this -> serial -> print("t\n");
}

void Minecraft::setWeather(int weather_value) {
  String switched_weather;
  switch (weather_value) {
    case 1:
      switched_weather = "clear";
      break;
    case 2:
      switched_weather = "rain";
      break;
    case 3:
      switched_weather = "thunder";
      break;
  }
  this -> serial -> print("/weather ");
  this -> serial -> print(switched_weather);
  this -> serial -> print("\n");
}

void Minecraft::teleportBotToPosition(float x = 0, float y = 0, float z = 0) {
  this -> serial -> print("/tp ");
  this -> serial -> print(BOT);
  this -> serial -> print(" ");
  this -> serial -> print(x);
  this -> serial -> print(" ");
  this -> serial -> print(y);
  this -> serial -> print(" ");
  this -> serial -> print(z);
  this -> serial -> print("\n");
}

void Minecraft::teleportEntityToPosition(String entity, float x = 0, float y = 0, float z = 0) {
  this -> serial -> print("/tp ");
  this -> serial -> print(entity);
  this -> serial -> print(" ");
  this -> serial -> print(x);
  this -> serial -> print(" ");
  this -> serial -> print(y);
  this -> serial -> print(" ");
  this -> serial -> print(z);
  this -> serial -> print("\n");
}

void Minecraft::teleportBotToEntity(String entity) {
  this -> serial -> print("/tp ");
  this -> serial -> print(BOT);
  this -> serial -> print(" ");
  this -> serial -> print(entity);
  this -> serial -> print("\n");
}

void Minecraft::teleportEntityToEntity(String f_entity, String s_entity) {
  this -> serial -> print("/tp ");
  this -> serial -> print(f_entity);
  this -> serial -> print(" ");
  this -> serial -> print(s_entity);
  this -> serial -> print("\n");
}

void Minecraft::gameMode(String entity, int mode_value) {
  String switched_mode;
  switch (mode_value) {
    case 1:
      switched_mode = "adventure";
      break;
    case 2:
      switched_mode = "creative";
      break;
    case 3:
      switched_mode = "spectator";
      break;
    case 4:
      switched_mode = "survival";
      break;
  }
  this -> serial -> print("/gamemode ");
  this -> serial -> print(" ");
  this -> serial -> print(switched_mode);
  this -> serial -> print(" ");
  this -> serial -> print(entity);
  this -> serial -> print("\n");
}

void Minecraft::createEntity(String entity) {
  this -> serial -> print("/summon ");
  this -> serial -> print(entity);
  this -> serial -> print("\n");
}

void Minecraft::placeBlock(String block) {
  this -> serial -> print(Arduino_Cmd + "bot placeblock ");
  this -> serial -> print(block);
  this -> serial -> print("\n");
}

void Minecraft::botGoForward() {
  this -> serial -> print(Arduino_Cmd + "bot walk forward\n");
}

void Minecraft::botGoBack() {
  this -> serial -> print(Arduino_Cmd + "bot walk back\n");
}

void Minecraft::botGoLeft() {
  this -> serial -> print(Arduino_Cmd + "bot walk left\n");
}

void Minecraft::botGoRight() {
  this -> serial -> print(Arduino_Cmd + "bot walk right\n");
}

void Minecraft::botStop() {
  this -> serial -> print(Arduino_Cmd + "bot walk stop\n");
}


void Minecraft::botJump() {
  this -> serial -> print(Arduino_Cmd + "bot jump\n");
}

bool Minecraft::botIsSpawned() {
  return spawn;
}

bool Minecraft::botIsKicked() {
  return kicked;
}

bool Minecraft::botIsEnded() {
  return end;
}

bool Minecraft::botIsDead() {
  return death;
}

bool Minecraft::botHealthIsChanged() {
  return health;
}

bool Minecraft::botErrorOccurred() {
  return error;
}

String Minecraft::getErrorMessage() {
  return errorMessage;
}

int Minecraft::getWorldTime() {
  return worldTime;
}

int Minecraft::getBotExperienceLevel() {
  return botExperience;
}

int Minecraft::getBotHealthLevel() {
  return botHealth;
}

int Minecraft::getBotFoodLevel() {
  return botFood;
}

int Minecraft::getBotOxygenLevel() {
  return botOxygen;
}

String Minecraft::getBotGameMode() {
  return botGameMode;
}

bool Minecraft::isRaining() {
  return raining;
}

int Minecraft::PingValue() {
  return pingValue;
}

double Minecraft::getBotPositionX() {
  return botPositionX;
}

double Minecraft::getBotPositionY() {
  return botPositionY;
}

double Minecraft::getBotPositionZ() {
  return botPositionZ;
}

void Minecraft::run() {
  curMillis = millis();
  if ((unsigned long)curMillis - prevMillis >= timerMillis) {

    lastMessage =  this -> serial -> readStringUntil('\n');

    if (ifContainsWord(lastMessage, "[DEAMON-CMD] datas ")) {
      lastMessage.replace("[DEAMON-CMD] datas ", "");

      String spawnValue = splitString(lastMessage, ';', 0);
      String kickedValue = splitString(lastMessage, ';', 1);
      String endValue = splitString(lastMessage, ';', 2);
      String deathValue = splitString(lastMessage, ';', 3);
      String healthValue = splitString(lastMessage, ';', 4);
      String errorValue = splitString(lastMessage, ';', 5);

      spawnValue == "true" ? spawn = true : spawn = false;
      kickedValue == "true" ? kicked = true : kicked = false;
      endValue == "true" ? end = true : end = false;
      healthValue == "true" ? health = true : health = false;
      deathValue == "true" ? death = true : death = false;
      errorValue == "true" ? error = true : error = false;

      errorMessage = splitString(lastMessage, ';', 6);
      worldTime = splitString(lastMessage, ';', 7).toInt();
      botExperience = splitString(lastMessage, ';', 8).toInt();
      botHealth = splitString(lastMessage, ';', 9).toInt();
      botFood = splitString(lastMessage, ';', 10).toInt();
      botOxygen = splitString(lastMessage, ';', 11).toInt();
      botGameMode = splitString(lastMessage, ';', 12);

      String rainingValue = splitString(lastMessage, ';', 13);

      rainingValue == "true" ? raining = true : raining = false;

      pingValue = splitString(lastMessage, ';', 14).toInt();

      botPositionX = splitString(lastMessage, ';', 15).toFloat();
      botPositionY = splitString(lastMessage, ';', 16).toFloat();
      botPositionZ = splitString(lastMessage, ';', 17).toFloat();

    }

    this->serial->flush();
    prevMillis = curMillis;

  }
}

#endif
