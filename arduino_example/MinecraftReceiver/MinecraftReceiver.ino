void setup() {
  Serial.begin(115200);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
}

void loop() { 
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    if(message.indexOf("ledon") != -1) {
      digitalWrite(6, 1);
    }
    if(message.indexOf("ledoff") != -1) {
      digitalWrite(6, 0);
    }
  }
}
