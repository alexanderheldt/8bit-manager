#pragma once

#include "Arduino.h"

class Signals {
  public:
    static const int MI, RI;

    void init();

    void connectToComputer();
    void disconnectFromComputer();

    void setWriteMode();
    void setReadMode();

    void setBus(char data[]);
    void clearBus();

    void enableProgrammingMode();
    void disableProgrammingMode();

    void pulseClock();
    void pulsePinWithClock(int pin);
    void pulseReset();
};
