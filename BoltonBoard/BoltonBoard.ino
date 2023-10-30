//Pins
#define SERVO1_PIN 9
#define RESET_PIN 2
#define BTN1_PIN 4

#define MIN_DLY 10
#define SPD_DLY 100

//Servo
#define CLOSED_ANGLE 0
#define OPEN_ANGLE 90
#include<Servo.h>


Servo drainServo;


void setup() {
  //start closed
  drainServo.write(CLOSED_ANGLE);
  
  delay(1000);
  drainServo.attach(SERVO1_PIN);
  delay(1000);
  reset();
   

  //setup buttons
  pinMode(RESET_PIN, INPUT);
  pinMode(BTN1_PIN, INPUT);
}

void loop() {
  //v1 was replaced since the board being retrofit was built incorrectly
  //v2 updated board requirements:
  /*
   * Servo to control holding board 
   *  release into bin after completion of demo
   *  button controlled
   * LED control on either side
   *  update LED color based on where it passes
   */
  

  static int state = 1;

  static int btnState[2] = {0,0};
 
  //when btn0 is pressed open the drain
  btnState[0] = checkBtn(0);
  
  //when btn1 is pressed cycle speeds
  btnState[1] = checkBtn(1);

  //when btn0 is pressed switch states
  if(btnState[0]==1){
    state = (state+1)%2;
  }

 
  
}

   
int checkBtn (int btnNum){
  const int btns[2] = {RESET_PIN,BTN1_PIN};
 return digitalRead(btns[btnNum]);
}

void drain(){
  servo1.write(

}
