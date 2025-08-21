#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "symbols.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Array of pointers to bitmaps
const uint8_t* symbols[] = {
  arrow_up, arrow_45, arrow_right, arrow_135,
  arrow_down, arrow_225, arrow_left, arrow_315,
  dot, exclamation, question
};

const char* labels[] = {
  "Up", "Up-Right", "Right", "Down-Right",
  "Down", "Down-Left", "Left", "Up-Left",
  "Dot", "Exclamation", "Question"
};

void setup() {

  Serial.begin(115200);
  while( !Serial) {
    delay(100);
  }
  Serial.println("\nESP32-SH1106-BITMAP started");

  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default
  Serial.println("display initialized");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
}

void loop() {
  for (int i = 0; i < 11; i++) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(labels[i]);
    display.drawBitmap((SCREEN_WIDTH - 16) / 2, (SCREEN_HEIGHT - 16) / 2, symbols[i], 16, 16, SH110X_WHITE);
    display.display();
    delay(2000); // Show each symbol for 3 seconds
  }

  display.clearDisplay();
  display.display();
  delay(2000);
}
