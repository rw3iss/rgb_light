#ifndef MODULE_H
#define MODULE_H

#include "AppServer.h"

/*
 * Manages main app state.
 */
class Module 
{
    public:
        void setup();
        void loop();

    private:
        AppServer appServer;
};

#endif
