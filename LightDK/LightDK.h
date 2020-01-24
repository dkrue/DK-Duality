/*
  LightDK.h - Library for rgb leds with pwm output
*/
#ifndef LightDK_h
#define LightDK_h

#include "Arduino.h"

class LightDK
{
  public:
    LightDK(int redPin, int greenPin, int bluePin);
    LightDK(int pin, bool on);
    void setColor(int red, int green, int blue);
    void setColor(bool red, bool green, bool blue);    
    void toggle(bool on);
  private:
    int _redPin;
    int _greenPin;
    int _bluePin;
    int _pin;
};

#endif