#include "utils.h"
#include "vars.h"
#include "colors.h"


void blinkTest()
{
  for (int n = 0; n < 5; n++)
  {
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      //setColor(i, white);
    }
    delay(50);
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      //setColor(i, black);
    }
    delay(50);
  }
}

void testAllRGB()
{
  int *testColors[4] = {red, green, blue, white};

  for (int t = 0; t < 4; t++)
  {
    //int *color = testColors[t];
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      //setColor(i, color);
    }
    delay(650);
  }

  // reset
  for (int s = 0; s < NUM_STRIPS; s++)
  {
    //setColor(s, white);
  }
}
