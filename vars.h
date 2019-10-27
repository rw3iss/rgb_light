#ifndef VARS_H
#define VARS_H 1


/* SETUP WIFI */
const char *ssid = "the_internet_2.4G"; // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "wifimenow";     // The password of the Wi-Fi network

//ESPRotary enc(13, 15);

// RGB array lookups
const int DEBUG_STRIP = 0; // monitor a single strip (debug logic)
const int R = 0;
const int G = 1;
const int B = 2;
const int NUM_STRIPS = 3;        // Number of independent LED strips we're handling
const int SET_PAUSE_TIME = 1000; // time to pause at each set
const int STEP_RESOLUTION = 999; // always this many steps in between fades
const int SET_FADE_TIME = 999;   //333; // how long it takes to fade between sets
const int SET_DIRECTION = 0;     // 0 (cw) or 1 (ccw)

// exact GPIO pin # assignments for each strip
// I do a little re-arranging because LED strip is in order of: g,r,b instead of r,g,b...
int STRIPS[NUM_STRIPS][3] = {
    {3, 5, 1},   // strip 1: D1, RX, TX (g, r, b) (GP5, GP3, GP1)
    {4, 0, 2},   // strip 2: D3, D2, D4 (g, r, b) (GP0, GP4, GP2)
    {16, 14, 12} // strip 3: D5, D0, D6 (g, r, b) (GP14, GP16, GP12)
};

#endif
