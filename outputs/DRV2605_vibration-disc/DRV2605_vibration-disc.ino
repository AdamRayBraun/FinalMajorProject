#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);
}

uint8_t effect = 1;

void loop() {
    Serial.println("NEW LOOP");

    for (effect = 1; effect < 118; effect++) {
      Serial.print("Effect #"); Serial.println(effect);

      // set the effect to play
      drv.setWaveform(0, effect);  // play effect
      drv.setWaveform(1, 0);       // end waveform

      // play the effect!
      drv.go();
      delay(1000);
    }

  delay(1500);
}
