#ifndef Arducraft_H
#define Arducraft_H

#include "Arduino.h"

//Weather status
#define CLEAR 1
#define RAIN 2
#define THUNDER 3

//Game Mode
#define ADVENTURE 1
#define CREATIVE 2
#define SPECTATOR 3
#define SURVIVAL 4

//Alias
#define ALL_PLAYER "@a"
#define ALL_ENTITIES "@e"
#define CLOSEST_PLAYER "@p"
#define RANDOM_PLAYER "@r"
#define BOT "@s"

//Entities
#define AXOLOTL "minecraft:axolotl"
#define BAT "minecraft:bat"
#define BEE "minecraft:bee"
#define BLAZE "minecraft:blaze"
#define CAT "minecraft:cata"
#define CAVE_SPIDER "minecraft:cave_spider"b
#define CHICKEN "minecraft:chicken"
#define COD "minecraft:cod"
#define COW "minecraft:cow"
#define CREEPER "minecraft:creeper"
#define DOLPHIN "minecraft:dolphin"
#define DONKEY "minecraft:donkey"
#define DROWNED "minecraft:drowned"
#define ELDER_GUARDIAN "minecraft:elder_guardian"
#define ENDER_DRAGON "minecraft:ender_dragon"
#define ENDERMAN "minecraft:enderman"
#define EVOKER "minecraft:evoker"
#define FOX "minecraft:fox"
#define GHAST "minecraft:ghast"
#define GIANT "minecraft:giant"
#define GOAT "minecraft:goat"
#define GUARDIAN "minecraft:guardian"
#define HOGLIN "minecraft:hoglin"
#define HORSE "minecraft:horse"
#define HUSK "minecraft:husk"
#define ILLUSIONER "minecraft:illusioner"
#define IRON_GOLEM "minecraft:iron_golem"
#define LLAMA "minecraft:llama"
#define LLAMA_SPIT "minecraft:llama_spit"
#define MOOSHROOM "minecraft:mooshroom"
#define MULE "minecraft:mule"
#define OCELOT "minecraft:ocelot"
#define PANDA "minecraft:panda"
#define PARROT "minecraft:parrot"
#define PHANTOM "minecraft:phantom"
#define PIG "minecraft:pig"
#define PIGLIN "minecraft:piglin"
#define PIGLIN_BRUTE "minecraft:piglin_brute"
#define PILLAGER "minecraft:pillager"
#define POLAR_BEAR "minecraft:polar_bear"
#define PUFFERFISH "minecraft:pufferfish"
#define RABBIT "minecraft:rabbit"
#define RAVAGER "minecraft:ravager"
#define SALMON "minecraft:salmon"
#define SHEEP "minecraft:sheep"
#define SHULKER "minecraft:shulker"
#define SKELETON "minecraft:skeleton"
#define SKELETON_HORSE "minecraft:skeleton_horse"
#define SLIME "minecraft:slime"
#define SNOW_GOLEM "minecraft:snow_golem"
#define SPIDER "minecraft:spider"
#define SQUID "minecraft:squid"
#define STRAY "minecraft:stray"
#define STRIDER "minecraft:strider"
#define TROPICAL_FISH "minecraft:tropical_fish"
#define TURTLE "minecraft:turtle"
#define VEX "minecraft:vex"
#define VILLAGER "minecraft:villager"
#define VINDICATOR "minecraft:vindicator"
#define WANDERING_TRADER "minecraft:wandering_trader"
#define WITCH "minecraft:witch"
#define WITHER "minecraft:wither"
#define WITHER_SKELETON "minecraft:wither_skeleton"
#define WITHER_SKULL "minecraft:wither_skull"
#define WOLF "minecraft:wolf"
#define ZOGLIN "minecraft:zoglin"
#define ZOMBIE "minecraft:zombie"
#define ZOMBIE_HORSE "minecraft:zombie_horse"
#define ZOMBIE_VILLAGER "minacraft:zombie_villager"
#define ZOMBIFIED_PIGLIN "minecraft:zombified_piglin"

class Minecraft {
    private:
    unsigned long curMillis = millis();
    unsigned long prevMillis = millis();
    unsigned long timerMillis = 10;
    unsigned long worldtime = 0;
    String lastMessage = "";
    public:
    Stream * serial;
    Minecraft() {
      prevMillis = millis();
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
    void gameMode(String entity, int mode_value);
    void createEntity(String entity);
    int getTime();
    void writeDaemonCommand(String message);
    void run();
};

void Minecraft::deamonAttach(Stream * newserial) {
  this -> serial = newserial;
}

String Minecraft::readMessage() {
  return lastMessage;
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

void Minecraft::writeDaemonCommand(String message) {
  this -> serial -> print("[DAEMON-CMD] ");
  this -> serial -> print(message);
  this -> serial -> print("\n");
}

int Minecraft::getTime() {
  return worldtime;
}

void Minecraft::run() {
  curMillis = millis();
  if((unsigned long)curMillis - prevMillis >= timerMillis) {
    lastMessage =  this -> serial -> readStringUntil('\n');
    if (ifContainsWord(lastMessage, "[TIME-RESPONSE] ")) {
      lastMessage.replace("[TIME-RESPONSE] ", "");
      worldtime = lastMessage.toInt();
    }
  }
}


#endif
