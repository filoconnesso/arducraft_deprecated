class Debouncing {
private:
  int btn;
  int curState, prevState, debState;
  unsigned long curMillis;
  unsigned long prevMillis;
  unsigned long debounceMillis = 20;
  unsigned long curClickMillis;
  unsigned long prevClickMillis;
  unsigned long clickTimerOffMillis = 1;
  unsigned long curReleaseMillis;
  unsigned long prevReleaseMillis;
  unsigned long releaseTimerOffMillis = 0;
  bool pressedState = false;
  bool toggleState = false;
  bool pressing = false;
  bool clicking = false;
  bool releasing = false;
  bool released = true;
  int pinModeState;

public:
  Debouncing(int button, int mode) {
    if (mode == INPUT) {
      curState = HIGH;
      prevState = LOW;
      debState = LOW;
    } else {
      curState = LOW;
      prevState = LOW;
      debState = HIGH;
    }
    btn = button;
    pinMode(btn, mode);
    pinModeState = mode;
    prevMillis = millis();
  }
  bool press();
  bool toggle();
  bool click();
  bool release();
};

bool Debouncing::press() {
  curMillis = millis();
  curState = digitalRead(btn);
  if (curState != prevState) {
    prevMillis = curMillis;
  }
  if ((unsigned long)curMillis - prevMillis > debounceMillis) {
    if (curState != debState) {
      debState = curState;
      if (pinModeState == INPUT) {
        if (debState == HIGH) {
          pressedState = true;
        } else {
          pressedState = false;
        }
      } else {
        if (debState == LOW) {
          pressedState = true;
        } else {
          pressedState = false;
        }
      }
    }
    prevMillis = curMillis;
  }
  prevState = curState;
  return pressedState;
}

bool Debouncing::toggle() {
  if (press()) {
    if (!pressing) {
      toggleState = !toggleState;
      pressing = true;
    }
  } else {
    pressing = false;
  }
  return toggleState;
}

bool Debouncing::click() {
  curClickMillis = millis();
  if ((unsigned long)curClickMillis - prevClickMillis > clickTimerOffMillis &&
      !released && clicking) {
    clicking = false;
    prevClickMillis = curClickMillis;
  }
  if (press()) {
    if (released) {
      clicking = true;
      released = false;
      prevClickMillis = curClickMillis;
    }
  } else {
    released = true;
  }
  return clicking;
}

bool Debouncing::release() {
  curReleaseMillis = millis();
  if ((unsigned long)curReleaseMillis - prevReleaseMillis >
          releaseTimerOffMillis &&
      released && !releasing) {
    releasing = true;
    prevReleaseMillis = curReleaseMillis;
  }
  if (press()) {
    if (!released) {
      releasing = false;
      released = true;
      prevReleaseMillis = curReleaseMillis;
    }
  } else {
    released = false;
  }
  return releasing;
}
