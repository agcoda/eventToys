#include<FastLED.h>

//PINS
#define STRIP_CHANNELS_PIN 	13
#define NUM_LEDS	40

//LED PROPERTIES
#define MIN_BRIGHTNESS   0
#define MAX_BRIGHTNESS  255
#define STRIP_CHANNELS  0
#define STRIP_LEFT      1
#define STRIP_RIGHT     2

//colors
#define WHITE 48
#define R_DEF 48
#define G_DEF 48
#define B_DEF 48

//general 
#define OFF 0
#define ON  1

CRGB channelLEDs[NUM_LEDS];
CRGB leftLEDs[NUM_LEDS];
CRGB rightLEDs[NUM_LEDS];

void setup(){

  FastLED.addLeds<WS2812, STRIP_CHANNELS_PIN, GRB>(channelLEDs, NUM_LEDS);

	int strRed = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	int strGreen = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
	int strBlue = random(MIN_BRIGHTNESS, MAX_BRIGHTNESS);
}

void loop(){
	switchAll(STRIP_CHANNELS, ON);
	delay(1000);
	switchAll(STRIP_CHANNELS, OFF);
	delay(1000);

}

void switchAll(int strip, int state){
    switch(state){
		case OFF:
			for(int column=0;column<NUM_LEDS;column++){
				ledSwitch(strip,column,0,0,0);
			}
			break;
		case ON:
			for(int column=0;column<NUM_LEDS;column++){
				ledSwitch(strip,column,WHITE,WHITE,WHITE);
			}			
			break;
		default:
			break;
	}
	FastLED.show();
}

void ledSwitch(int strip, int column, int r, int g, int b){
	switch(strip){
		case STRIP_CHANNELS:
			channelLEDs[column]=CRGB(r,g,b);
			break;
		case STRIP_LEFT:
			leftLEDs[column]=CRGB(r,g,b);
			break;
		case STRIP_RIGHT:
			rightLEDs[column]=CRGB(r,g,b);
			break;
	}
}
