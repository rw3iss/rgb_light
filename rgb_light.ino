#include "vars.h"
#include "utils.h"
#include "Server.h"
#include "Module.h"

#define MAIN_H 1



// declare main app Module
Module module;


void setup() {
  // initialize all strip LED outputs
  for (int s = 0; s < NUM_STRIPS; s++)
  {
    pinMode(STRIPS[s][R], OUTPUT);
    pinMode(STRIPS[s][G], OUTPUT);
    pinMode(STRIPS[s][B], OUTPUT);
    //setColor(s, white);
    //delay(1000);
  }

  module.setup();
}

void loop() {
  module.loop();
}
