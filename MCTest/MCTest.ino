#include "Arducraft.h"
#include "Tweakly.h"

// Led output
#define LED 13
#define LED2 8

// Buttons
#define ThunderBtn 2
Pad Tweak(ThunderBtn, INPUT);

//Thunder Status
bool old_btn_value;
bool weather_status;

Minecraft mc;

// Encoder
int encoderPin1 = 9;
int encoderPin2 = 10;
volatile int lastEncoded = 0;
volatile int encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;


void setup() {
  Serial.begin(115200);
  mc.deamonAttach(&Serial);

  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);
  attachInterrupt(0, onEncoderChange, CHANGE);
  attachInterrupt(1, onEncoderChange, CHANGE);
}



void onEncoderChange() {
  int MSB = digitalRead(encoderPin1);
  int LSB = digitalRead(encoderPin2); 
  int encoded = (MSB << 1) | LSB;
  int sum  = (lastEncoded << 2) | encoded; 
  if (sum == 0b1000) encoderValue ++;
  if (sum == 0b0010) encoderValue --;
  lastEncoded = encoded;
}




void loop() {
  TweaklyRun();

  String cmd = mc.readMessage();

  bool led2on = mc.ifContainsWord(cmd, "led2on");
  bool led2off = mc.ifContainsWord(cmd, "led2off");

  if(cmd.indexOf("ledon") >= 0) {
    digitalWrite(LED, HIGH);
  }
  if(cmd.indexOf("ledoff") >= 0) {
    digitalWrite(LED, LOW);
  }

  if(led2on) {
    digitalWrite(LED2, HIGH);
  }
  if(led2off) {
    digitalWrite(LED2, LOW);
  }


  bool btn_value = digitalPushButton(ThunderBtn);

  if(old_btn_value != btn_value)
  {

    if(weather_status == 0)
    {
      mc.setWeather(1);
      weather_status = 1;
    }
    else {
      mc.setWeather(2);
      weather_status = 0;      
    }
    old_btn_value = btn_value;
  }


  mc.addTime(encoderValue);


}
