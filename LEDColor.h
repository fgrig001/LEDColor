
#include <Arduino.h>

namespace LEDColor{

	class Color{
		public:
			Color(int red_val=0,int green_val=0,int blue_val=0);
			void setColor(int red_val,int green_val,int blue_val);
			int getRedVal(){ return redVal; }
			int getGreenVal(){ return greenVal; }
			int getBlueVal(){ return blueVal; }
		private:
			int redVal;
			int greenVal;
			int blueVal;
	};

	class LED{
		public:
			LED(int red_pin=9,int green_pin=10,int blue_pin=11);
			void setPins(int red_pin,int green_pin,int blue_pin);
			void writeColor(int red_val,int green_val,int blue_val);
			void writeColor(Color *color);
			void rainbowFade(int speed_val);
			void dualColor(Color *colorOne,Color *colorTwo,int speed_val);
			void triColor(Color *colorOne,Color *colorTwo,Color *colorThree,int speed_val);
		private:
			// Color pins
			int redPin;
			int greenPin;
			int bluePin;
	};


	Color::Color(int red_val,int green_val,int blue_val):
		redVal(red_val),
		greenVal(green_val),
		blueVal(blue_val)
	{}

	void Color::setColor(int red_val,int green_val,int blue_val){
		redVal = red_val;	
		greenVal = green_val;
		blueVal = blue_val;
	}


	LED::LED(int red_pin,int green_pin,int blue_pin):
		redPin(red_pin),
		greenPin(green_pin),
		bluePin(blue_pin)
	{
		pinMode(redPin, OUTPUT);
		pinMode(greenPin, OUTPUT);
		pinMode(bluePin, OUTPUT);
	}

	void LED::setPins(int red_pin,int green_pin,int blue_pin){
		// Setpins
		redPin = red_pin;
		greenPin = green_pin;
		bluePin = blue_pin;
		// Init pins
		pinMode(redPin, OUTPUT);
		pinMode(greenPin, OUTPUT);
		pinMode(bluePin, OUTPUT);
	}

				
	void LED::writeColor(int red_val,int green_val,int blue_val){
		analogWrite(redPin,255-red_val);
		analogWrite(greenPin,255-green_val);
		analogWrite(bluePin,255-blue_val);
	}

	void LED::writeColor(Color *color){
		analogWrite(redPin,255-color->getRedVal());
		analogWrite(greenPin,255-color->getGreenVal());
		analogWrite(bluePin,255-color->getBlueVal());
	}

	void LED::rainbowFade(int speed_val){
		static int count=0;
		if(count>=0 && count<256){
			this->writeColor(255-count,count,0);
		}
		else if(count>=256 && count<512){
			this->writeColor(0,511-count,count-256);
		}
		else{
			this->writeColor(count-512,0,767-count);
		}
		count=(count+1)%768;
		delay(speed_val);
	}

	void LED::triColor(Color *colorOne,Color *colorTwo,Color *colorThree,int speed_val){
		static int wait = 0;
		static int count = 0;
		switch(count){
			case 0:
				this->writeColor(colorOne);
				break;
			case 1:
				this->writeColor(colorTwo);
				break;
			case 2:
				this->writeColor(colorThree);
				break;
			default:
				count=0;
				break;
		}
		if(wait>=100){
			wait=0;
			count = (count+1)%3;
		}
		wait++;
		delay(speed_val);
	}

	void LED::dualColor(Color *colorOne,Color *colorTwo,int speed_val){
		static int wait = 0;
		static int count = 0;
		switch(count){
			case 0:
				this->writeColor(colorOne);
				break;
			case 1:
				this->writeColor(colorTwo);
				break;
			default:
				count=0;
				break;
		}
		if(wait>=100){
			wait=0;
			count = (count+1)%2;
		}
		wait++;
		delay(speed_val);
	}

}


