
#include <ESP8266WiFi.h>
#include "Module.h"
#include "AppServer.h"
#include "Colors.h"

void Module::setup() {
    //server = AppServer();
}

void Module::loop() {
    appServer.checkClient();
}



// Interesting Sets to iterate through:
const int NUM_SETS = 10;
int *SETS[NUM_SETS][NUM_STRIPS] = {
    {white, yellow, orange}, // start at white
    {green, white, yellow},

    {cyan, green, white},
    {blue, cyan, green},
    {purple, blue, cyan},
    {nearblack, purple, blue},
    {magenta, nearblack, purple},

    {red, magenta, nearblack},
    {orange, red, magenta},
    {yellow, orange, red}};




// Stores the color of the current/previous playing set for each strip.
// (Acts as initial colors!)
int *prevSetColors[NUM_STRIPS] = {
    white, white, white};

// keeps track of moving fade color for each strip, start at white
int prevFadeColor[NUM_STRIPS][3] = {
    {prevSetColors[0][R], prevSetColors[0][G], prevSetColors[0][B]},
    {prevSetColors[1][R], prevSetColors[1][G], prevSetColors[1][B]},
    {prevSetColors[2][R], prevSetColors[2][G], prevSetColors[2][B]}};






// Set a specifc strip to a specific color.
// color should be a 3D-array of values from 0-100.
void setColor(int strip, int *color)
{
  Serial.println("setColor: " + strip);
  for (int i = 0; i < 3; i++)
  {
    int v = color[i];
    v = (v < 0) ? 0 : (v > 255) ? 255 : v; // clamp to 0-255
    analogWrite(STRIPS[strip][i], v);
  }
}

void fadeToSet(int *newSetColors[NUM_STRIPS])
{
  float stepDelayTime = SET_FADE_TIME / (STEP_RESOLUTION * 1.0);

  for (int i = 0; i < STEP_RESOLUTION; i++)
  {
    for (int j = 0; j < NUM_STRIPS; j++)
    {
      // grab previous and new (target) colors for this strip
      int *prevStripColor = prevSetColors[j];
      int *newStripColor = newSetColors[j];

      // calculate the the total amount to move each color value
      // based on the previous->target distance over the entire resolution
      int prevStripR = prevStripColor[R];
      int prevStripG = prevStripColor[G];
      int prevStripB = prevStripColor[B];
      int newStripR = newStripColor[R];
      int newStripG = newStripColor[G];
      int newStripB = newStripColor[B];

      double stepSizeR = ((newStripR - prevStripR) / (STEP_RESOLUTION * 1.0)); //* i+1; //(STEP_RESOLUTION / (newStripR - prevFadeColor[j][R])); /// STEP_RESOLUTION) * i;
      double stepSizeG = ((newStripG - prevStripG) / (STEP_RESOLUTION * 1.0)); // * i+1;
      double stepSizeB = ((newStripB - prevStripB) / (STEP_RESOLUTION * 1.0)); // * i+1;

      // update previous values and set new color, always base updated values on original (prevStrip*)
      prevFadeColor[j][R] = floor(prevStripR + (stepSizeR * (i + 1)));
      prevFadeColor[j][G] = floor(prevStripG + (stepSizeG * (i + 1)));
      prevFadeColor[j][B] = floor(prevStripB + (stepSizeB * (i + 1)));

      // set this strips step color
      setColor(j, prevFadeColor[j]);
    }

    delayMicroseconds(stepDelayTime * 1000);
  }

  // update previous set with the new color
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    prevSetColors[i] = newSetColors[i];

    if (i == DEBUG_STRIP)
    {
      //printf("\nSetting previous color... #%d (%d, %d, %d)\n",  i, prevSetColors[i][R], prevSetColors[i][G], prevSetColors[i][B]);
    }
  }

  delayMicroseconds(stepDelayTime * 1000);
}

void playSet(int **set)
{
  fadeToSet(set);
}

// set colors immediately
void setSetColors(int **set)
{
  for (int s = 0; s < NUM_STRIPS; s++)
  {
    setColor(s, set[s]);
  }
}


void parseSetColors(String strColors) {
  int pIdx = 0;
  int idx = 0;
  int colorNum = 0;
  String parsedColors[NUM_STRIPS]; // stores the found color for each strip
  
  while(true) {
    //only parse as many colors as supported strips
    if (colorNum == NUM_STRIPS) {
      break;
    }
    
    idx = strColors.indexOf(',', idx);
    if (idx > -1) {
      String color = strColors.substring(pIdx, idx++);
      pIdx = idx;
      parsedColors[colorNum++] = color;
      Serial.println("Parsed color: " + color);
    } else {
      // check last color:
      if (static_cast<unsigned int>(pIdx) != strColors.length()) {
        String color = strColors.substring(pIdx, strColors.length());
        Serial.println("Parsed color: " + color);
        parsedColors[colorNum++] = color;
      }
      break;
    }
  }

  for (int i=0; i < NUM_STRIPS; i++) {
    int* color = Colors::getColor(parsedColors[i]);
    setColor(i, color);
    //Serial.println("Set color for strip " + color[R] + ", " + color[G] + ", " + color[B]);
  }
}


void setMode(int strMode) {
  Serial.println("setMode " + strMode);

  switch(strMode) {
  }
}


void parseMode(String mode) {
  Serial.println("parseMode " + mode);
  setMode(random_fade);
}
