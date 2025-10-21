#include <Servo.h>
/* 
UMass Amherst BattleBots 2025 Team #4
10/16/2025
Program disc: Spinner System
Contributors: 
Richard Le: richardle@umass.edu

TO DO:
Not sure, 
*/
Servo esc;

int escPin = 5;        // ESC signal pin
int potPin = 34;        // potentiometer input (ADC)
int killSwitchPin = 14; // kill switch (push button)

int potValue = 0;       // raw ADC reading, initialize to 0 
int throttle = 1000;    // ESC signal (1000–2000 µs), initialize to 1000
bool killed = false;    // initialize killed to false 

void setup() {
  Serial.begin(115200);
  esc.attach(escPin, 1000, 2000);

  pinMode(killSwitchPin, INPUT_PULLUP); // button active LOW, 

  Serial.println("Arming ESC...");
  esc.writeMicroseconds(1000);
  delay(3000); // 3000 us/3 ms delay 
  Serial.println("ESC armed.");
}

void loop() {
  // check kill switch
  if (digitalRead(killSwitchPin) == LOW) {
    // if button pressed — kill motor
    killed = true;
    esc.writeMicroseconds(1000);
    Serial.println("KILL SWITCH ACTIVATED! Motor stopped.");
    delay(100); // debounce, prevent multiple detections of button press
    return;
  } else { // otherwise - keep going
    killed = false;
  }

  // read potentiometer then map to esc range
  potValue = analogRead(potPin);
  throttle = map(potValue, 0, 4095, 1000, 2000);

  // send throttle signal
  esc.writeMicroseconds(throttle);

  // debug info
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  ->  ESC signal: ");
  Serial.println(throttle);

  delay(50);
}
