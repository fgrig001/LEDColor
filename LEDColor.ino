#include "LEDColor.h"
using namespace LEDColor;

LED led(9,10,11);
Color *color1 = new Color(255,0,0);
Color *color2 = new Color(0,255,0);
Color *color3 = new Color(0,0,255);

void setup(){
		
}

void loop(){
	//led.rainbowFade(40);
    //LED.writeColor(0,255,0);
	//led.triColor(color1,color2,color3,40);
	led.dualColor(color1,color2,40);
}

