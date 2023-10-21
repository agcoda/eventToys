//Pins
#define SERVO1_PIN 9
#define RESET_PIN 2
#define BTN1_PIN 4

#define MIN_DLY 10
#define SPD_DLY 100

//Servo
#define START_ANGLE 40
#define MAX_ROTATE 20
#define MIN_ANGLE START_ANGLE-MAX_ROTATE
#define MAX_ANGLE START_ANGLE+MAX_ROTATE
#define TURN_DELAY 10
#define CW 0
#define CCW 1

#include<Servo.h>


Servo servo1;
int servoLoc = START_ANGLE;
int stepSize = 1;
int speedDelay = 100;

void reset();
void rotate(int);
int checkBtn(int);

void setup() {
  
  servo1.write(servoLoc);
  
  delay(1000);
  servo1.attach(SERVO1_PIN);
  delay(1000);
  reset();
  
  //servoLoc = servo1.read(); 

  //setup buttons
  pinMode(RESET_PIN, INPUT);
  pinMode(BTN1_PIN, INPUT);
}

void loop() {
  /*
  reset();
  delay(1000);
  scroll();
  delay(1000);
  */
  /*
  servo1.write(MIN_ANGLE);
  //rotate(0);
  delay(1000);
  servo1.write(MAX_ANGLE);
  //rotate(20);
  delay(1000);
  */

  static int state = 1;

  static int btnState[2] = {0,0};
  //states 0=stationary at start, 1=back and forth

  btnState[0] = checkBtn(0);
  
  //when btn1 is pressed cycle speeds
  btnState[1] = checkBtn(1);

  //when btn0 is pressed switch states
  if(btnState[0]==1){
    state = (state+1)%2;
  }
  switch(state){
    case 0:
      reset();
      break;
    case 1:
      scroll();
      break;
  }
 
  
}

   
int checkBtn (int btnNum){
  const int btns[2] = {RESET_PIN,BTN1_PIN};
 return digitalRead(btns[btnNum]);
}

//provides stepwise rotation to a desired location
void rotate(int dir){
  //adding is CW, subtract is CCW
  if(dir==CW && servoLoc <MAX_ANGLE){
    servo1.write(servoLoc+=stepSize);
    delay(speedDelay);
    
  }
  else if(dir == CCW && servoLoc > MIN_ANGLE){
    servo1.write(servoLoc-=stepSize);
    delay(speedDelay);
  }
  //read pos at end for checking
   //servoLoc=servo1.read();
}

//get to start
void reset(){
  int tempStep = stepSize;
  stepSize=1;
  while(servoLoc != START_ANGLE){
  
    if(servoLoc>START_ANGLE){
      rotate(CCW);
    }
    else if(servoLoc<START_ANGLE){
      rotate(CW);
    }
  }
  stepSize = tempStep;
 // servoLoc = servo1.read();
  
}

void scroll(){
  //wherever you start rotate CW until max angle
  static int dir = CW;
  while(servoLoc<START_ANGLE+MAX_ROTATE){
    rotate(CW);
  }
  //then go back to min angle
  while(servoLoc>START_ANGLE-MAX_ROTATE){
    rotate(CCW);
  }
  //then return to start
  while(servoLoc<START_ANGLE){
    rotate(CW);
  }

}
