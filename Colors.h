
#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>


// COLOR DEFINITIONS
// spectrum: WHITE, YELLOW, ORANGE, RED, MAGENTA, BLACK, PURPLE, BLUE, CYAN, GREEN
const int NUM_COLORS = 15;
int nearblack[3] = {10, 10, 10};
int black[3] = {0, 0, 0};
int purple[3] = {15, 3, 70};
int blue[3] = {0, 0, 100};
int cyan[3] = {30, 40, 100};
int green[3] = {0, 100, 0};
int white[3] = {100, 100, 100};
int yellow[3] = {75, 68, 10};
int orange[3] = {60, 45, 5};
int red[3] = {100, 0, 0};
int magenta[3] = {70, 10, 60};

// extras / not used
int teal[3] = {0, 50, 50};
int sharp[3] = {15, 58, 90};
int grey[3] = {20, 20, 20};
int midwhite[3] = {50, 50, 50};

int *defaultColor = white;

int *colors[NUM_COLORS] = {
    nearblack, black, purple, blue, cyan, green, white, yellow, orange, red, magenta, teal, sharp, grey, midwhite
};

String colorIdx[NUM_COLORS] = {
    "newblack", "black", "purple", "blue", "cyan", "green", "white", "yellow", "orange", "red", "magenta", "teal", "sharp", "grey", "midwhite"
};


class Colors {

    public:
        static int* getColorFromRGB(String val);
        static int* getColorFromName(String color);
        static int* getColor(String color);

    private:

};


enum ColorMode {
  random_fade,  // fade between random colors
  rainbow_fade, // fade through spectrum of rainbow
  sets_fade,    // fade through pre-defined sets of colors
  specific,     // show specific colors
  timer         // run time program, ie. daylight colors
};



#endif
