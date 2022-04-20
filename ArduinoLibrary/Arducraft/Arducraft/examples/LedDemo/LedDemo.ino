#include <Arducraft.h>

Arducraft mc;

String minecraftChat;

void setup() {

  Serial.begin(115200);
  mc.begin(&Serial);

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  mc.run();  
  
  minecraftChat = mc.readMessage();

  if(minecraftChat.indexOf("ledon") > -1) {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if(minecraftChat.indexOf("ledoff") > -1) {
    digitalWrite(LED_BUILTIN, LOW);
  }

}
