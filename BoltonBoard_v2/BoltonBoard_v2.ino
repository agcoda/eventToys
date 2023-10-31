#include<FastLED.h>

//PINS
//Strips
#define STRIP_CHANNELS_PIN 	12
#define STRIP_LEFT_PIN      13
#define STRIP_RIGHT_PIN     11
//Buttons
#define BTN1_PIN            7
#define BTN2_PIN            6
#define BTN3_PIN            5
#define BTN4_PIN            4
#define BTN5_PIN            3

//LED PROPERTIES
#define MIN_BRIGHTNESS      0
#define MAX_BRIGHTNESS      255
#define STRIP_CHANNELS      0
#define STRIP_LEFT          1
#define STRIP_RIGHT         2
#define NUM_LEDS_CHANNEL    38
#define NUM_LEDS_SIDES      40
#define NUM_LEDS_MAX        (NUM_LEDS_CHANNEL>NUM_LEDS_SIDES) ? NUM_LEDS_CHANNEL : NUM_LEDS_SIDES

//colors
#define WHITE 48
#define R_DEF 48
#define G_DEF 48
#define B_DEF 48

//intensity
#define BRIGHT              20
#define DIM                 1
#define OFF                 0

//TIMING
#define DELAY               10
#define MIN_BTN_DELAY       200

//general 
#define OFF                 0
#define ON                  1
#define NUM_STRIPS          3
#define NUM_BTNS            5
#define NUM_STATES          2

CRGB channelLEDs[NUM_LEDS_CHANNEL];
CRGB leftLEDs[NUM_LEDS_SIDES];
CRGB rightLEDs[NUM_LEDS_SIDES];

//colors
//RED,GREEN,BLUE
const int RED[3]          = {BRIGHT,0,0};
const int GREEN[3]        = {0,BRIGHT,0};
const int BLUE[3]         = {0,0,BRIGHT};
const int YELLOW[3]       = {BRIGHT,BRIGHT,0};
//R, G, B, Y
const int COLOR_ARRAY[4][3] = {{BRIGHT,0,0}, {0,BRIGHT,0}, {0,0,BRIGHT}, {BRIGHT,BRIGHT,0} };
const int WHITE_ARR[3]    = {BRIGHT,BRIGHT,BRIGHT};
const int WHITE_DIM[3]    = {DIM,DIM,DIM};
const int OFF_ARR[3]      = {OFF,OFF,OFF};

//strips
int strips[NUM_STRIPS] = {0,0,0} ;

//state control
int state = 0;
static int currTime = millis();
static int lastPress = 0;
int initFlag = 1;

//when btn 5 is pressed update the value of state
void btn5ISR(){
  Serial.println("b5 Interrupted");
  state = (state+1)%NUM_STATES;
  Serial.println(state);
  if(state == 1){ initFlag = 1;}

}


void setup(){

  FastLED.addLeds<WS2812, STRIP_CHANNELS_PIN, GRB>(channelLEDs, NUM_LEDS_CHANNEL);
  FastLED.addLeds<WS2812, STRIP_LEFT_PIN, GRB>(leftLEDs, NUM_LEDS_SIDES);
  FastLED.addLeds<WS2812, STRIP_RIGHT_PIN, GRB>(rightLEDs, NUM_LEDS_SIDES);

	int strRed = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	int strGreen = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	int strBlue = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);

 pinMode(BTN1_PIN,INPUT);
 pinMode(BTN2_PIN,INPUT);
 pinMode(BTN3_PIN,INPUT);
 pinMode(BTN4_PIN,INPUT);
 pinMode(BTN5_PIN,INPUT);

 
 attachInterrupt(digitalPinToInterrupt(BTN5_PIN), btn5ISR, RISING);

 Serial.begin(9600);

 
}

void loop(){

  int btnState[NUM_BTNS] = {0,0,0,0,0};
  bool recent;

  //peripheral checks
  btnState[0] = digitalRead(BTN1_PIN);
  btnState[1] = digitalRead(BTN2_PIN);
  btnState[2] = digitalRead(BTN3_PIN);
  btnState[3] = digitalRead(BTN4_PIN);
  btnState[4] = digitalRead(BTN5_PIN);

  //TWO STATES
  //dark pulsing S0 and ready for ball drop S1
  //btn 4 interrupt switches states with ISR

  //if in S0 pulse dark purple on all strips
  if(state==0){
    Serial.println(state);
    darkPulse();
  }
  else if(state==1){ 
    if(initFlag == 1){
      channelStripSet();
      strips[0]=0;
      strips[1] = 1;
      strips[2] = 1;
      colorChange(strips, WHITE_DIM);
      initFlag = 0;
    }
    
    if (btnState[0] != 0){
    //set channel strip to red
    colorChange(strips, RED);
    delay(2000);
    colorChange(strips, WHITE_DIM);
    }
  
      if (btnState[1] != 0){
    //set channel strip to blue
    colorChange(strips, BLUE);
    delay(2000);
    colorChange(strips, WHITE_DIM);
    }
    
    if (btnState[2] != 0){
    //set channel strip to Green
    colorChange(strips, GREEN);
    delay(2000);
    colorChange(strips, WHITE_DIM);
    }
    
    if (btnState[3] != 0){
    //set channel strip to yellow
    colorChange(strips, YELLOW);
    delay(2000);
    colorChange(strips, WHITE_DIM);
    }
  }
  else{
    //should never get here
  }

  //delay to not double read buttons
  delay(100);
}

void darkPulse(){
  int allStrips[NUM_STRIPS] = {1,1,1};
  int i=DIM;
  for(i;i<BRIGHT;i++){
    if(state == 1){return;}
    int color[3] = {i,0,i+2};
    delay(1);
    
    colorChange(allStrips, color);
  }
    for(i;i>DIM;i--){
    if(state == 1){return;}
    int color[3] = {i,0,i+2};
    
    delay(1);
    colorChange(allStrips, color);
  }
}

//change an entire strip to the noted rgb
//assumes sides have more leds than strip
void colorChange(int strips[NUM_STRIPS], int rgb[3]){
  for(int column=0;column<NUM_LEDS_SIDES;column++){
    if(strips[STRIP_CHANNELS] == 1){    
      if(column < NUM_LEDS_CHANNEL){  
          ledSwitch(STRIP_CHANNELS,column,rgb);
      }
    }
    if(strips[STRIP_LEFT] == 1){      
        ledSwitch(STRIP_LEFT,column,rgb);
    }
    if(strips[STRIP_RIGHT] == 1){      
        ledSwitch(STRIP_RIGHT,column,rgb);
    }
  }
}

//switch them all off/on to white
void switchAll(int strip, int state){
    switch(state){
		case OFF:
			for(int column=0;column<NUM_LEDS_MAX;column++){
				ledSwitch(strip,column,OFF_ARR);
			}
			break;
		case ON:
			for(int column=0;column<NUM_LEDS_MAX;column++){
				ledSwitch(strip,column,WHITE_ARR);
			}			
			break;
		default:
			break;
	}
  FastLED.show();
}

//switch any individual LED
void ledSwitch(int strip, int column, int rgb[3]){
	switch(strip){
		case STRIP_CHANNELS:
			channelLEDs[column]=CRGB(rgb[0],rgb[1],rgb[2]);
			break;
		case STRIP_LEFT:
			leftLEDs[column]=CRGB(rgb[0],rgb[1],rgb[2]);
			break;
		case STRIP_RIGHT:
			rightLEDs[column]=CRGB(rgb[0],rgb[1],rgb[2]);
			break;
	}
  FastLED.show();
}

void channelStripSet(){
//These are the LEDS to denote the drop slots
//only every other LED is actually in a slot so only turn on odds


  for(int i=1; i<NUM_LEDS_CHANNEL;i+=2){
    ledSwitch(STRIP_CHANNELS, i, OFF_ARR);
  }
  
  for(int i=0; i<NUM_LEDS_CHANNEL/2;i++){
    ledSwitch(STRIP_CHANNELS, 2*i, COLOR_ARRAY[i%4]);
  }
}
