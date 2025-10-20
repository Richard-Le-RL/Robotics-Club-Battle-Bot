/* 
UMass Amherst BattleBots 2025 Team #4
10/16/2025
Program disc: Drive System 
Contributors: 
Ryder Overstreet: rooverstreet@umas.edu


TO DO:
- add a more intricate system for controls i.e. smoother transition into speed
and better turning controls allowing for faster turning at more drastic inputs
of the controls.
*/

// stepper right 
const int DIR_R = 18; // number = pin wire is connected to 
const int STEP_R = 19;
// controls
const int VERT = 33;
const int HORZ = 32;
const int SEL = 27;
const int DEAD = 200; // constant for deadzone 
// switch
const int SWITCH = 35; 
// stepper left 
const int DIR_L = 25;
const int STEP_L = 26;

void setup()
{
  Serial.begin(115200);
  pinMode(STEP_R, OUTPUT); // STEP pin controls motor steps
  pinMode(DIR_R, OUTPUT);  // DIR pin sets motor rotation direction
  pinMode(VERT, INPUT);  // vert axis input
  pinMode(HORZ, INPUT); // hoz axis input 
  //pinMode(SEL_PIN, INPUT_PULLUP); set SEL pin as input (allows for push button on joystick)
  pinMode(SWITCH, HIGH); // switch input 
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
}

void stepMotor() 
{
  digitalWrite(STEP_R, LOW); 
  digitalWrite(STEP_L, LOW);
  delayMicroseconds(500);
  digitalWrite(STEP_R, HIGH);
  digitalWrite(STEP_L, HIGH);
  delayMicroseconds(500);
}

void loop()
{
  int vert = analogRead(VERT); // get vert direction for controls
  int horz = analogRead(HORZ); // get horz direction for controls
  int ks = analogRead(SWITCH); // get input of switch

  if (ks == LOW)
  {
    return;
  }

  if (horz > 2048 + DEAD)
  {
    digitalWrite(DIR_R, HIGH);
    digitalWrite(DIR_L, LOW);
    stepMotor();
  }
  else if (horz < 2048 - DEAD)
  {
    digitalWrite(DIR_L, HIGH);
    digitalWrite(DIR_R, LOW);
    stepMotor();
  }

// forward and reverse controls 
  if (vert > 2048 + DEAD) // 2048 is half the analog range 
  {
    digitalWrite(DIR_R, HIGH); // forward direction
    digitalWrite(DIR_L, HIGH);
    stepMotor(); // while pushig up repeat function
  }
  else if (vert < 2048 - DEAD) 
  {
    digitalWrite(DIR_R, LOW); // reverse direction
    digitalWrite(DIR_L, LOW);
    stepMotor(); //while pulling back repeat function
  }
}
