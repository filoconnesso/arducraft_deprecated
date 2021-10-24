//Minecraft Receiver Example

#define LED 6

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

Arducraft minecraft;

void setup() {
  Serial.begin(115200);
  minecraft.begin(&Serial);
  pinMode(LED, OUTPUT);
}

void loop() {

  bool cmdLedON = minecraft.readWord("ledon");
  bool cmdLedOFF = minecraft.readWord("ledoff");

  if (cmdLedON) {
    digitalWrite(LED, HIGH);
  }

  if (cmdLedOFF) {
    digitalWrite(LED, LOW);
  }

}
