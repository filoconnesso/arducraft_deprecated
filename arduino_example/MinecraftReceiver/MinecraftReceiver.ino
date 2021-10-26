//Minecraft Receiver Example

#define LED 8

class Arducraft {
  private :
    Stream* s;
  public :
    Arducraft() {}
    void begin(Stream *newSerRef);
    bool readWord(const char* w);
    String readMessage();
};

void Arducraft::begin(Stream *newSerRef) {
  s = newSerRef;
}

bool Arducraft::readWord(const char* w) {
  bool result;
  String msg = s->readStringUntil('\n');
  if (msg.indexOf(w) != -1) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

String Arducraft::readMessage() {
  return s->readStringUntil('\n');
}

Arducraft minecraftLog;

void setup() {
  Serial.begin(115200);
  minecraftLog.begin(&Serial);
  pinMode(LED, OUTPUT);
}

void loop() {

  bool cmdLedON = minecraftLog.readWord("ledon");
  bool cmdLedOFF = minecraftLog.readWord("ledoff");

  if (cmdLedON) {
    digitalWrite(LED, HIGH);
    Serial.println("ledon");
  }

  if (cmdLedOFF) {
    digitalWrite(LED, LOW);
    Serial.println("ledoff");
  }

}
