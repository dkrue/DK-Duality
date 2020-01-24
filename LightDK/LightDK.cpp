/*
  LightDK.cpp - Library for simple rgb leds
*/

#include "Arduino.h"
#include "LightDK.h"

#define COMMON_ANODE

LightDK::LightDK(int redPin, int greenPin, int bluePin)
{
    pinMode(redPin, OUTPUT);
    _redPin = redPin;
    pinMode(greenPin, OUTPUT);
    _greenPin = greenPin;
    pinMode(bluePin, OUTPUT);
    _bluePin = bluePin;    
}

LightDK::LightDK(int pin, bool on)
{
  pinMode(pin, OUTPUT);
  _pin = pin;

  digitalWrite(_pin, on);
}

// RGB output for PWM output
void LightDK::setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  
  analogWrite(_redPin, red);
  analogWrite(_greenPin, green);
  analogWrite(_bluePin, blue);  
}

void LightDK::setColor(bool red, bool green, bool blue)
{
  #ifdef COMMON_ANODE
    red = !red;
    green = !green;
    blue = !blue;
  #endif
  
  digitalWrite(_redPin, red);
  digitalWrite(_greenPin, green);
  digitalWrite(_bluePin, blue); 
}

void LightDK::toggle(bool on)
{
    digitalWrite(_pin, on);
}