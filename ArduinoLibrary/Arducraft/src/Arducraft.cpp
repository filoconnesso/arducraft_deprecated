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
 * FILO CONNESSO ARDUCRAFT LIBRARY
 *
 *
 * Created by Alessandro Marcon (@alessandromrc) and Mirko Pacioni
 * November 2th 2021
 *
 */

#include "Arduino.h"
#include "Arducraft.h"

// command prefix from microcontroller
String ARDUCRAFT_CMD = "[ARDUCRAFT CMD]";

// function that allows you to create a clickable link and send it in the game chat

void Arducraft::createChatLink(String text, String color, String url) {
  this->serial->print(ARDUCRAFT_CMD + "chatlink=" + String(text) + "+" + String(color) + "+" + String(url)  + "\n");
}

// extract compile debug information

void Arducraft::debugInformations() {
  this->serial->print(String("Thank you for using Arducraft! " + String(VERSION) +
                             "\n\nInformations:\n") +
                             "File Name: " + String(file_name) +
                             "\nCompilation Date: " + String(compile_date) +
                             "\nCompilation Time: " + String(compile_time));
}

// start the bot and connect the tool serial

void Arducraft::begin(Stream *newserial) {
  this->serial = newserial;
  this->serial->setTimeout(0);
}

// read the last chat message of the game

String Arducraft::readMessage() { return lastMessage; }

// wait for the bot to finish performing the last action

void Arducraft::waitBot() {
  do {
    delay(500);
  } while (botMoving);
}

// write a chat message

void Arducraft::writeMessage(String message) {
  this->serial->print("/say ");
  this->serial->print(message);
  this->serial->print("\n");
}

// create and control a lever in the indicated location

void Arducraft::lever(long x, long y, long z, bool powered) {
  this->serial->print("/setblock ");
  this->serial->print(x);
  this->serial->print(" ");
  this->serial->print(y);
  this->serial->print(" ");
  this->serial->print(z);
  this->serial->print(" minecraft:lever[powered=");
  if (powered) {
    this->serial->print("true");
  } else {
    this->serial->print("false");
  }
  this->serial->print("] \n");
}

// set the time of the game

void Arducraft::setWorldTime(int value) {
  this->serial->print("/time set ");
  this->serial->print(value);
  this->serial->print("\n");
}

// add time to the current game time

void Arducraft::addWorldTime(int value) {
  this->serial->print("/time add ");
  this->serial->print(value);
  this->serial->print("t\n");
}

// set the weather condition of the game

void Arducraft::setWeather(int weather_value) {
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
  this->serial->print("/weather ");
  this->serial->print(switched_weather);
  this->serial->print("\n");
}

// teleport the bot to the desired location

void Arducraft::teleportBotToPosition(float x = 0, float y = 0, float z = 0) {
  this->serial->print("/tp ");
  this->serial->print(BOT);
  this->serial->print(" ");
  this->serial->print(x);
  this->serial->print(" ");
  this->serial->print(y);
  this->serial->print(" ");
  this->serial->print(z);
  this->serial->print("\n");
}

// teleports an entity to the desired location

void Arducraft::teleportEntityToPosition(String entity, float x = 0,
                                         float y = 0, float z = 0) {
  this->serial->print("/tp ");
  this->serial->print(entity);
  this->serial->print(" ");
  this->serial->print(x);
  this->serial->print(" ");
  this->serial->print(y);
  this->serial->print(" ");
  this->serial->print(z);
  this->serial->print("\n");
}

// teleports the bot to the location of a desired entity

void Arducraft::teleportBotToEntity(String entity) {
  this->serial->print("/tp ");
  this->serial->print(BOT);
  this->serial->print(" ");
  this->serial->print(entity);
  this->serial->print("\n");
}

// teleports an entity to the location of a desired entity

void Arducraft::teleportEntityToEntity(String f_entity, String s_entity) {
  this->serial->print("/tp ");
  this->serial->print(f_entity);
  this->serial->print(" ");
  this->serial->print(s_entity);
  this->serial->print("\n");
}

// set the game mode for a desired entity

void Arducraft::setGameMode(String entity, int mode_value) {
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
  this->serial->print("/gamemode ");
  this->serial->print(" ");
  this->serial->print(switched_mode);
  this->serial->print(" ");
  this->serial->print(entity);
  this->serial->print("\n");
}

// produce an entity at the bot's current location

void Arducraft::spawnEntity(String entity) {
  this->serial->print("/summon ");
  this->serial->print(entity);
  this->serial->print("\n");
}

// place a block in the bot's current location

void Arducraft::placeBlock(String block) {
  this->serial->print(ARDUCRAFT_CMD + "bot placeblock ");
  this->serial->print(block);
  this->serial->print("\n");
}

// move the bot one block forward

void Arducraft::botGoForward() {
  this->serial->print(ARDUCRAFT_CMD + "bot walk forward \n");
}

// move the bot back one block

void Arducraft::botGoBack() {
  this->serial->print(ARDUCRAFT_CMD + "bot walk back \n");
}

// move the bot left one block

void Arducraft::botGoLeft() {
  this->serial->print(ARDUCRAFT_CMD + "bot walk left \n");
}

// move the bot right one block

void Arducraft::botGoRight() {
  this->serial->print(ARDUCRAFT_CMD + "bot walk right \n");
}

// stop the movement of the bot

void Arducraft::botStop() {
  this->serial->print(ARDUCRAFT_CMD + "bot walk stop \n");
}

// make the bot perform a jump

void Arducraft::botJump() { this->serial->print(ARDUCRAFT_CMD + "bot jump \n"); }

// check that the bot has appeared on the map

bool Arducraft::botIsSpawned() { return spawn; }

// check if the bot gets a kick

bool Arducraft::botIsKicked() { return kicked; }

// check if the bot is closed

bool Arducraft::botIsEnded() { return end; }

// check if the bot dies

bool Arducraft::botIsDead() { return death; }

// check if the bot's health status changes

bool Arducraft::botHealthIsChanged() { return health; }

// check if the bot returns an error

bool Arducraft::botErrorOccurred() { return error; }

// check for the latest error from the game

String Arducraft::getErrorMessage() { return errorMessage; }

// take the time of the game world

int Arducraft::getWorldTime() { return worldTime; }

// get the bot's experience level

int Arducraft::getBotExperienceLevel() { return botExperience; }

// get the bot's health level

int Arducraft::getBotHealthLevel() { return botHealth; }

// get the bot's hunger level

int Arducraft::getBotHungerLevel() { return botFood; }

// get the bot's oxygen level

int Arducraft::getBotOxygenLevel() { return botOxygen; }

// get the game mode of the bot

String Arducraft::getBotGameMode() { return botGameMode; }

// check if it is raining in the game, go to true if it is raining or there is a thunderstorm

bool Arducraft::isRaining() { return raining; }

// get the ping from the game

int Arducraft::getPing() { return pingValue; }

// get the x-axis value of the bot's current position

double Arducraft::getBotPositionX() { return botPositionX; }

// get the y-axis value of the bot's current position

double Arducraft::getBotPositionY() { return botPositionY; }

// get the z-axis value of the bot's current position

double Arducraft::getBotPositionZ() { return botPositionZ; }

// run function that monitors the state of the game and allows control from the microcontroller
// during the game session the library variables are updated via serial
// the game data is sent by the tool through a string containing all the current information, from time to time the library will split the string and update the states on the microcontroller.

void Arducraft::run() {
  while (this->serial->available() > 0) {
    
    // read current serial char
    char curChar = this->serial->read();
    
    // add the char to bot datas
    lastBotDatas += curChar;

    // if the char equals \n execute all update operations
    if (curChar == '\n') {
      
      // update spawn string
      spawnValue = splitString(lastBotDatas, ';', 0);
      // update kick string
      kickedValue = splitString(lastBotDatas, ';', 1);
      // update end string
      endValue = splitString(lastBotDatas, ';', 2);
      // update death string
      deathValue = splitString(lastBotDatas, ';', 3);
      // update health string
      healthValue = splitString(lastBotDatas, ';', 4);
      // update error string
      errorValue = splitString(lastBotDatas, ';', 5);
      
      // if spawn string is true set spawn status to true
      if (spawnValue == "true")
        spawn = true;
      // if spawn string is false set spawn status to false
      if (spawnValue == "false")
        spawn = false;
      // if kick string is true set kick status to true
      if (kickedValue == "true")
        kicked = true;
      // if kick string is false set kick status to false
      if (kickedValue == "false")
        kicked = false;
      // if end string is true set end status to true
      if (endValue == "true")
        end = true;
      // if end string is false set error end to false
      if (endValue == "false")
        end = false;
      // if health string is true set health status to true
      if (healthValue == "true")
        health = true;
      // if health string is false set health status to false
      if (healthValue == "false")
        health = false;
      // if death string is true set death status to true
      if (deathValue == "true")
        death = true;
      // if death string is false set error death to false
      if (deathValue == "false")
        death = false;
      // if error string is true set error status to true
      if (errorValue == "true")
        error = true;
      // if error string is false set error status to false
      if (errorValue == "false")
        error = false;
      
      // update error message string 
      errorMessage = splitString(lastBotDatas, ';', 6);
      // update world time
      worldTime = splitString(lastBotDatas, ';', 7).toInt();
      // update bot experience level
      botExperience = splitString(lastBotDatas, ';', 8).toInt();
      // update bot health level
      botHealth = splitString(lastBotDatas, ';', 9).toInt();
      // update bot hunger level
      botFood = splitString(lastBotDatas, ';', 10).toInt();
      // update bot oxygen level
      botOxygen = splitString(lastBotDatas, ';', 11).toInt();
      // update bot game mode
      botGameMode = splitString(lastBotDatas, ';', 12);
      
      // update rain status
      rainingValue = splitString(lastBotDatas, ';', 13);
      
      // if rain string is true set rain status to true
      if (rainingValue == "true")
        raining = true;
      // if rain string is false set rain status to false
      if (rainingValue == "false")
        raining = false;
      
      // update ping value
      pingValue = splitString(lastBotDatas, ';', 14).toInt();
      
      // update x-axis position
      botPositionX = splitString(lastBotDatas, ';', 15).toFloat();
      // update y-axis position
      botPositionY = splitString(lastBotDatas, ';', 16).toFloat();
      // update z-axis position
      botPositionZ = splitString(lastBotDatas, ';', 17).toFloat();
      
      // update moving status
      botMovingValue = splitString(lastBotDatas, ';', 18);

      // if move string is true set move status to true
      if (botMovingValue == "true")
        botMoving = true;
      // if move string is false set move status to false
      if (botMovingValue == "false")
        botMoving = false;

      // update last message string
      lastMessage = splitString(lastBotDatas, ';', 19);
    
      // reset the bot datas string for another communication
      lastBotDatas = "";
      
      //clear serial buffer
      this->serial->flush();
    }
  }
}