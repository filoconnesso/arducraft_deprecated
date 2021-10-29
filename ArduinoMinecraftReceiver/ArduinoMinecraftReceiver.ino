int ledPin = 8;
String readString;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }

  if (readString.length() > 0) {
    Serial.println(readString);

    if (readString.indexOf("ledon") >= 0)
    {
      digitalWrite(ledPin, HIGH);
    }

    if (readString.indexOf("ledoff") >= 0)s
    {
      digitalWrite(ledPin, LOW);
    }

    readString = "";
  }
}