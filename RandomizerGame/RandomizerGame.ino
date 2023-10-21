//Pins
#define SERVO1_PIN 9
#define RESET_PIN 2
#define BTN1_PIN 4

//Servo
#define MAX_ANGLE 20
#define START_ANGLE 45
#define TURN_DELAY 10
#define RIGHT 0
#define LEFT 1

#include<Servo.h>


Servo servo1;
int servoLoc = 0;
int stepSize = 1;

void rotate(int);
int checkBtn(int);

void setup() {

//get init servo location
  servoLoc = servo1.read();  
  servo1.attach(SERVO1_PIN);

  //setup buttons
  pinMode(RESET_PIN, INPUT);
  pinMode(BTN1_PIN, INPUT);

  

}

void loop() {

  int mode = 0;

  static int btnState[2] = {0,0};
  //states 0=stationary at start, 1=back and forth
  static int state = 1; 

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

//provides stepwise rotation in either Dir up to limits
void rotate(int dir){
  if(dir == RIGHT && servoLoc<START_ANGLE+MAX_ANGLE){
    servo1.write(servoLoc+=stepSize);
  }
  else if(dir==LEFT && servoLoc<START_ANGLE-MAX_ANGLE){
    servo1.write(servoLoc-=stepSize);
  }
}

//get to start
void reset(){
  int tempStepSize = stepSize;
  stepSize = 1;
  
  while(servoLoc != START_ANGLE){
    servoLoc=servo1.read();
  if(servoLoc > START_ANGLE){
    rotate(LEFT);
  }
  else if(servoLoc < START_ANGLE){
    rotate(RIGHT);
  }
  }
  stepSize = tempStepSize;
}

void scroll(){
  //wherever you start rotate right until max angle
  static int dir = RIGHT;
  while(servoLoc<START_ANGLE+MAX_ANGLE){
    rotate(RIGHT);
  }
  while(servoLoc>START_ANGLE-MAX_ANGLE){
    rotate(LEFT);
  }
  while(servoLoc<START_ANGLE){
    rotate(RIGHT);
  }

}
