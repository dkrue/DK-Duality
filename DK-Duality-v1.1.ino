#include <KnobDK.h>
#include <LightDK.h>
#include <UtilityDK.h>

#define midiChannel 1

//#define DEBUG
#define onboardLED 13

// Controller knobs (analogPin, midiCC, analogMin, analogMax)
KnobDK knob[2] = {
  KnobDK(A7, 14, 0, 1023),
  KnobDK(A8, 15, 0, 1023)
};

// RGB LEDs (redPin, greenPin, bluePin)
LightDK led[2] = {
  LightDK(6, 9, 10),
  LightDK(23, 20, 16)
};


void setup() {
  #ifdef DEBUG
    pinMode(onboardLED, OUTPUT);
  #endif
}

void loop() {

  // Analog inputs loop
  for (int i=0; i < 2; i++)
  {
    // Refresh controller value
    bool activity = knob[i].refresh();
    
    if(activity)
    {
      #ifdef DEBUG
        digitalWrite(onboardLED, HIGH);
        Serial.print("Knob ");
        Serial.print(i);
        Serial.print(" is ");
        Serial.print(knob[i].val());
        Serial.print(" sent ");
        Serial.print(knob[i].ccVal());
        Serial.print(" on CC ");
        Serial.println(knob[i].ccNum());
      #endif
      
      // Send MIDI CC value
      usbMIDI.sendControlChange(knob[i].ccNum(), knob[i].ccVal(), midiChannel);

    } else {
      #ifdef DEBUG      
        digitalWrite(onboardLED, LOW);
      #endif
    }

    // Convert knob to radians and update led color along sine curve
    double rad = UtilityDK::scale((double)knob[i].val(), 0.0, 1023.0, 0.0, 3.14);
    led[i].setColor((int)(cos(rad) * 255), (int)(sin(rad) * 128), (int)(255 - cos(rad) * 255));
  }

  // Reduce analog sampling rate for smoother action
  delay(20);

  // MIDI Controllers should discard incoming MIDI messages
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

