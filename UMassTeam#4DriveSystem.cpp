/* 
UMass Amherst BattleBots 2025 Team #4
10/16/2025
Program disc: Drive System 
Contributors: 
Ryder Overstreet: rooverstreet@umas.edu

*/

const int DIR = 18; // number = pin wire is connected to 
const int STEP = 19;
const int VERT = 33;
const int HORZ = 32;
const int SEL = 27;
const int DEAD = 200; // constant for 

void setup()
{
  Serial.begin(115200);
  pinMode(STEP, OUTPUT); // STEP pin controls motor steps
  pinMode(DIR, OUTPUT);  // DIR pin sets motor rotation direction
  pinMode(VERT, INPUT);  // vert axis input
  pinMode(HORZ, INPUT); // hoz axis input 
  //pinMode(SEL_PIN, INPUT_PULLUP); set SEL pin as input (allows for push button on joystick)
}

void stepMotor() 
{
  digitalWrite(STEP, LOW); 
  delayMicroseconds(500);
  digitalWrite(STEP, HIGH);
  delayMicroseconds(500);
}

void loop()
{
  int vert = analogRead(VERT); // get vert direction for controls
  int horz = analogRead(HORZ); // get horz direction for controls

  if (vert > 2048 + DEAD) // 2048 is half the analog range 
  {
    digitalWrite(DIR, HIGH); // forward direction
    stepMotor(); // while pushig up repeat function
  }
  else if (vert < 2048 - DEAD) 
  {
    digitalWrite(DIR, LOW); // reverse direction
    stepMotor(); //while pulling back repeat function
  }
}
