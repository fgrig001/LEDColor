#include "LEDColor.h"

LEDColor LED(9,10,11);
int count=0;

void setup(){
		
}

void loop(){
	LED.rainbowFade(40);
        //LED.writeColor(0,255,0);
}

