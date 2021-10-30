#ifndef Arducraft_H
#define Arducraft_H

#include "Arduino.h"

class Minecraft{
private:
     Stream* serial;

public:
     Minecraft(){
     
     }

     void deamonAttach(Stream* newserial);
     String readMessage();
     bool ifContainsWord(String message, String word);
     void writeMessage(String message);
};

void Minecraft::deamonAttach(Stream* newserial){
    this->serial = newserial;
}

String Minecraft::readMessage(){
    delay(3);
    String r = "";
    while(this->serial->available()) {
     char c = this->serial->read();
     r += c;
    }
    return r;
}

bool Minecraft::ifContainsWord(String message, String word){
    bool response = false;
    if(message.indexOf(word) >= 0) {
      response = true;
    } else {
      response = false;
    }
    return response;
}

void Minecraft::writeMessage(String message) {
    this->serial->print("/say ");
    this->serial->print(message);
    this->serial->print("\n");
}

#endif
