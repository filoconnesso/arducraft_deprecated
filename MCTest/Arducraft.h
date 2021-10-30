#ifndef Arducraft_H
#define Arducraft_H

#include "Arduino.h"

#define CLEAR 1
#define RAIN 2
#define THUNDER 3

#define ALL_PLAYER "@a"
#define ALL_ENTITIES "@e"
#define CLOSEST_PLAYER "@p"
#define RANDOM_PLAYER "@r"
#define BOT "@s"

class Minecraft {
  private:
    Stream * serial;

  public:
    Minecraft() {

    }
    void deamonAttach(Stream * newserial);
    String readMessage();
    bool ifContainsWord(String message, String word);
    void writeMessage(String message);
    void setTime(int value);
    void addTime(int value);
    void setWeather(int weather_value);
    void teleportBotToPosition(float x, float y, float z);
    void teleportEntityToPosition(String entity, float x, float y, float z);
    void teleportBotToEntity(String entity);
    void teleportEntityToEntity(String f_entity, String s_entity);
};

void Minecraft::deamonAttach(Stream * newserial) {
  this -> serial = newserial;
}

String Minecraft::readMessage() {
  String r = "";
  while (this -> serial -> available()) {
    String c = this -> serial -> readStringUntil('\n');
    r += c;
  }
  return r;
}

bool Minecraft::ifContainsWord(String message, String word) {
  bool response;
  if (message.indexOf(word) >= 0) {
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

void Minecraft::setTime(int value) {
  this -> serial -> print("/time set ");
  this -> serial -> print(value);
  this -> serial -> print("\n");
}

void Minecraft::addTime(int value) {
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

#endif
