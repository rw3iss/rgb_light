#include "Colors.h";
#include <Arduino.h>

int * Colors::getColorFromRGB(String vals) {
  String strRgb = vals.substring(2, vals.indexOf(']')-1); // get "1,2,3"
  int rgb[3] = { 255, 255, 255 }; // default values

  // separate each val
  int pIdx = 0;
  int idx = 0;
  int currDigit = 0;   // which digit we're at: r=0, g=1, b=2
  while(true) {
    idx = strRgb.indexOf(',', idx);
    if (pIdx > -1) {
      // if no new entry, go to last
      String color = strRgb.substring(pIdx, idx == -1 ? strRgb.length() : idx++);
      pIdx = idx++;

      // parse color value
      rgb[currDigit++] = color.toInt();
      Serial.println("Parsed color: " + color);
    } else {
      break;
    }
  }

  return rgb;
}

int* Colors::getColorFromName(String name) {
  int lookupIdx = -1;
  for (int i = 0; i < NUM_COLORS; i++)
  {
    if (colorIdx[i] == name)
    {
      lookupIdx = i;
      break;
    }
  }
  if (lookupIdx > -1)
    return colors[lookupIdx];
  else
    return defaultColor;
}

// Get RGB values from hex or color name
int* Colors::getColor(String color)
{
  // check if hex or string
  if (color.indexOf('[') > -1) {
    // assume hex
    return getColorFromRGB(color);
  } else {
    // assume color string
    return getColorFromName(color);
  }

}
