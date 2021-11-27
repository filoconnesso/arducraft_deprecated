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

//Blocks
#define AIR "minecraft:air"
#define STONE "minecraft:stone"
#define GRANITE "minecraft:granite"
#define POLISHED_GRANITE "minecraft:polished_granite"
#define DIORITE "minecraft:diorite"
#define POLISHED_DIORITE "minecraft:polished_diorite"
#define ANDESITE "minecraft:andesite"
#define POLISHED_ANDESITE "minecraft:polished_andesite"
#define GRASS_BLOCK "minecraft:grass_block"
#define DIRT "minecraft:dirt"
#define COARSE_DIRT "minecraft:coarse_dirt"
#define PODZOL "minecraft:podzol"
#define COBBLESTONE "minecraft:cobblestone"
#define OAK_PLANKS "minecraft:oak_planks"
#define SPURCE_PLANKS "minecraft:spurce_planks"
#define BIRCH_PLANKS "minecraft:birch_planks"
#define JUNGLE_PLANKS "minecraft:jungle_planks"
#define ACACIA_PLANKS "minecraft:acacia_planks"
#define DARK_OAK_PLANKS "minecraft:dark_oak_planks"
#define BEDROCK "minecraft:bedrock"
#define SAND "minecraft:sand"
#define RED_SAND "minecraft:red_sand"
#define OAK_LOG "minecraft:oak_log"
#define SPURCE_LOG "minecraft:spurce_log"
#define BIRCH_LOG "minecraft:birch_log"
#define JUNGLE_LOG "minecraft:jungle_log"
#define ACACIA_LOG "minecraft:acacia_log"
#define DARK_OAK_LOG "minecraft:dark_oak_log"
#define STRIPPED_OAK_LOG "minecraft:stripped_oak_log"
#define STRIPPED_SPURCE_LOG "minecraft:stripped_spurce_log"
#define STRIPPED_BIRCH_LOG "minecraft:stripped_birch_log"
#define STRIPPED_JUNGLE_LOG "minacraft:stripped_jungle_log"
#define STRIPPED_ACACIA_LOG "minecraft:stripped_acacia_log"
#define STRIPPED_DARK_OAK_LOG "minacraft:stripped_dark_oak_log"
#define STRIPPED_OAK_WOOD "minecraft:stripped_oak_wood"
#define STRIPPED_SPURCE_WOOD "minacraft:stripped_spurce_wood"
#define STRIPPED_BIRCH_WOOD "minecraft:stripped_birch_wood"
#define STRIPPED_JUNGLE_WOOD "minecraft:stripped_jungle_wood"
#define STRIPPED_ACACIA_WOOD "minecraft:stripped_acacia_wood"
#define STRIPPED_DARK_OAK_WOOD "minecraft:stripped_oak_wood"
#define OAK_WOOD "minecraft:oak_wood"
#define SPURCE_WOOD "minecraft:spurce_wood"
#define BIRCH_WOOD "minecraft:birch_wood"
#define JUNGLE_WOOD "minecraft:jungle_wood"
#define ACACIA_WOOD "minecraft:acacia_wood"
#define DARK_OAK_WOOD "minecraft:dark_oak_wood"
#define GLASS "minacraft:glass"
#define OAK_SLAB "minecraft:oak_slab"
#define SPURCE_SLAB "minacraft:spurce_slab"
#define BIRCH_SLAB "minecraft:birch_slab"
#define JUNGLE_SLAB "minecraft:jungle_slab"
#define ACACIA_SLAB "minacraft:acacia_slab"
#define DARK_OAK_SLAB "minecraft:dark_oak_slab"
#define STONE_SLAB "minecraft:stone_slab"
#define COBBLESTONE_SLAB "minacraft:cobblestone_slab"
#define BRICK_SLAB "minecraft:brick_slab"
#define BRICKS "minecraft:bricks"
#define TNT "minacraft:tnt"
#define BOOKSHELF "minecraft:bookshelf"
#define OBSIDIAN "minecraft:obsidian"
#define WHITE_WOOL "minecraft:white_wool"
#define ORANGE_WOOL "minecraft:orange_wool"
#define MAGENTA_WOOL "minecraft:magenta_wool"
#define LIGHT_BLUE_WOOL "minecraft:light_blue_wool"
#define YELLOW_WOOL "minecraft:yellow_wool"
#define LIME_WOOL "minecraft:live_wool"
#define PINK_WOOL "minecraft:pink_wool"
#define GRAY_WOOL "minecraft:gray_wool"
#define LIGHT_GRAY_WOOL "minacraft:light_gray_wool"
#define CYAN_WOOL "minecraft:cyan_wool"
#define PURPLE_WOOL "minecraft:purple_wool"
#define BLUE_WOOL "minecraft:blue_wool"
#define BROWN_WOOL "minacraft:brown_wool"
#define GREEN_WOOL "minacraft:green_wool"
#define RED_WOOL "minecraft:red_wool"
#define BLACK_WOOL "minecraft:black_wool"
#define WHITE_TERRACOTTA "minecraft:white_terracotta"
#define ORANGE_TERRACOTTA "minecraft:orange_terracotta"
#define MAGENTA_TERRACOTTA "minecraft:magenta_terracotta"
#define LIGHT_BLUE_TERRACOTTA "minecraft:light_blue_terracotta"
#define YELLOW_TERRACOTTA "minecraft:yellow_terracotta"
#define LIME_TERRACOTTA "minecraft:lime_terracotta"
#define PINK_TERRACOTTA "minecraft:pink_terracotta"
#define GRAY_TERRACOTTA "minecraft:gray_terracotta"
#define LIGHT_GRAY_TERRACOTTA "minecraft:light_gray_terracotta"
#define CYAN_TERRACOTTA "minecraft:cyan_terracotta"
#define PURPLE_TERRACOTTA "minecraft:purple_terracotta"
#define BLUE_TERRACOTTA "minecraft:blue_terracotta"
#define BROWN_TERRACOTTA "minecraft:brown_terracotta"
#define GREEN_TERRACOTTA "minecraft:green_terracotta"
#define RED_TERRACOTTA "minecraft:red_terracotta"
#define BLACK_TERRACOTTA "minecraft:black_terracotta"
#define TERRACOTTA "minecraft:terracotta"

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
  this -> serial -> print("[ARDUINO CMD] bot placeblock ");
  this -> serial -> print(block);
  this -> serial -> print("\n");
}

void Minecraft::botGoForward() {
  this -> serial -> print("[ARDUINO CMD] bot walk forward\n");
}

void Minecraft::botGoBack() {
  this -> serial -> print("[ARDUINO CMD] bot walk back\n");
}

void Minecraft::botGoLeft() {
  this -> serial -> print("[ARDUINO CMD] bot walk left\n");
}

void Minecraft::botGoRight() {
  this -> serial -> print("[ARDUINO CMD] bot walk right\n");
}

void Minecraft::botStop() {
  this -> serial -> print("[ARDUINO CMD] bot walk stop\n");
}


void Minecraft::botJump() {
  this -> serial -> print("[ARDUINO CMD] bot jump\n");
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
      
      if (spawnValue == "true") spawn = true;
      if (spawnValue == "false") spawn = false;

      if (kickedValue == "true") kicked = true;
      if (kickedValue == "false") kicked = false;

      if (endValue == "true") end = true;
      if (endValue == "false") end = false;

      if (healthValue == "true") health = true;
      if (healthValue == "false") health = false;

      if (deathValue == "true") death = true;
      if (deathValue == "false") death = false;

      if (errorValue == "true") error = true;
      if (errorValue == "false") error = false;

      errorMessage = splitString(lastMessage, ';', 6);
      worldTime = splitString(lastMessage, ';', 7).toInt();
      botExperience = splitString(lastMessage, ';', 8).toInt();
      botHealth = splitString(lastMessage, ';', 9).toInt();
      botFood = splitString(lastMessage, ';', 10).toInt();
      botOxygen = splitString(lastMessage, ';', 11).toInt();
      botGameMode = splitString(lastMessage, ';', 12);

      String rainingValue = splitString(lastMessage, ';', 13);

      if (rainingValue == "true") raining = true;
      if (rainingValue == "false") raining = false;

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
