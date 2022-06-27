#include "Arducraft.h"
#include "debouncing.h"

Arducraft mc;

Debouncing PSW_1(12, INPUT_PULLUP);


String minecraftChat;


void setup() {
  mc.begin();
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}




void loop() {
  mc.run();

  minecraftChat = mc.readMessage();


  if(minecraftChat.indexOf("ledron") > -1)
  {
    digitalWrite(LEDR, HIGH);
  }

  if(minecraftChat.indexOf("ledroff") > -1)
  {
    digitalWrite(LEDR, LOW);
  }

  if(minecraftChat.indexOf("ledgon") > -1)
  {
    digitalWrite(LEDG, HIGH);
  }

  if(minecraftChat.indexOf("ledgoff") > -1)
  {
    digitalWrite(LEDG, LOW);
  }

  if(minecraftChat.indexOf("ledbon") > -1)
  {
    digitalWrite(LEDB, HIGH);
  }

  if(minecraftChat.indexOf("ledboff") > -1)
  {
    digitalWrite(LEDB, LOW);
  }


  if(mc.isRaining())
  {
    Serial.println("it's raining");
  }


  if(PSW_1.press())
  {
    mc.writeMessage("button pressed");
  }


}
