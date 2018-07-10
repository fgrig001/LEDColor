#include "LEDColor.h"
using namespace LEDColor;

LED led(9,10,11);
Color *color1 = new Color(200,55,0);
Color *color2 = new Color(55,0,200);
Color *color3 = new Color(0,200,0);
int BUTTON_PIN = 2;
int BUTTON_VAL;
int SELECTION=0;
int NUMBER_SETS=3;
int SPEED_VAL=20;
int TOP_SPEED=80;
int i=0;
int count=100;

enum buttonStates{START,CHECK,WAIT1,COUNT,WAIT2}buttonState;
enum LEDStates{SET1,SET2,SET3}LEDState;

void setup(){
        Serial.begin(9600);	
	pinMode(BUTTON_PIN,INPUT);
        pinMode(3,OUTPUT);
        pinMode(4,OUTPUT);
        pinMode(5,OUTPUT);
        pinMode(6,OUTPUT);

}

void loop(){
	
	// read button
	BUTTON_VAL = !digitalRead(BUTTON_PIN);
        Serial.println(BUTTON_VAL);
        Serial.println(SPEED_VAL);
	switch(buttonState){ // transitions
		case START:
                        Serial.println("START");
			buttonState = BUTTON_VAL ? CHECK : START;
			break;
		case CHECK:
                        Serial.println("CHECK");
			buttonState = BUTTON_VAL ? WAIT1 : START;
			break;
		case WAIT1:	
                        Serial.println("WAIT1");
			if(BUTTON_VAL){
				buttonState = WAIT1;
			}else{
				buttonState = COUNT;
				i=0;
			}
			break;
		case COUNT:
                        Serial.println("COUNT");
			if(!BUTTON_VAL && i<=count){
				buttonState = COUNT;
				i++;
			}
			else if(BUTTON_VAL){
				buttonState = WAIT2;
			}else{
				buttonState = START;
				SELECTION = (SELECTION+1)%NUMBER_SETS;	
			}
			break;
		case WAIT2:
                        Serial.println("WAIT2");
			if(BUTTON_VAL){
				buttonState = WAIT2;
			}else{
				buttonState = START;
				SPEED_VAL = (SPEED_VAL+10)%TOP_SPEED;
			}
                        break;
		default:
			buttonState = START;
			break;
	}

	switch(SELECTION){
		case 0:	
			led.rainbowFade(SPEED_VAL);	
			break;
		case 1:	
			led.dualColor(color1,color2,SPEED_VAL);
			break;
		case 2:	
			led.triColor(color1,color2,color3,SPEED_VAL);
			break;
		default:
			break;
	}
        
        if(SPEED_VAL<20){
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
          digitalWrite(6,HIGH);
        }else if(SPEED_VAL<40){
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
          digitalWrite(6,LOW);
        }else if(SPEED_VAL<60){
          digitalWrite(3,HIGH);
          digitalWrite(4,HIGH);
          digitalWrite(5,LOW);
          digitalWrite(6,LOW);
        }else if(SPEED_VAL<80){
          digitalWrite(3,HIGH);
          digitalWrite(4,LOW);
          digitalWrite(5,LOW);
          digitalWrite(6,LOW);
        }
        
}

