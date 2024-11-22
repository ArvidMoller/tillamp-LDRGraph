#include "functions.h"
#include <Arduino.h>
#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);


int LDRAverage(int raw) {
  const int ldrLength = 10;
  static int ldrArr[ldrLength] = {0};

  int sum = 0;
  float average;

  for (int i = 1; i < ldrLength; i++) {
    ldrArr[i - 1] = ldrArr[i];
  }
  ldrArr[ldrLength - 1] = raw;

  for (int i = 0; i < ldrLength; i++) {
    sum = sum + ldrArr[i];
  }

  average = sum / ldrLength;

  return average;
}



void oledGraph(int average) {
  const int oledlength = 128;
  static int oledArr[oledlength] = {0};

  int max = 0;
  int min = 1023;

  for (int i = 1; i < oledlength; i++) {
    oledArr[i - 1] = oledArr[i];
  }
  oledArr[oledlength - 1] = map(average, 0, 1023, 0, 63);

  u8g.firstPage();

  do {
    for (int i = 1; i < oledlength; i++) {
      u8g.drawLine(i-1, oledArr[i-1], i, oledArr[i]);
    }
  } while (u8g.nextPage());
}