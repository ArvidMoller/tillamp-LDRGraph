#include <U8glib.h>
#include "functions.h"

const int LDRPin = A0;

void setup() {
  pinMode(LDRPin, INPUT);
}

void loop() {
  oledGraph(LDRAverage(analogRead(LDRPin)));
}