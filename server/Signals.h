#pragma once

#include "Arduino.h"

class Signals {
  public:
    static const int MI, RI, II, AI, BI, OI, FI;

    void init();
    void setReadMode();
    void setWriteMode();
    void setBus(char data[]);
    void enableManualClock();
    void disableManualClock();
    void pulseClock();
    void pulsePin(int pin);
};
