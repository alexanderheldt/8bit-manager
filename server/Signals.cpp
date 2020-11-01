#include "Arduino.h"
#include "Signals.h"

// clock signals and programming mode are active low
const int CLK_AL = 13;
const int ENABLE_MANUAL_CLK_AL = 12;
const int ENABLE_PROGRAMMING_MODE_AL = 32;

const int RESET = 14;

const int D0 = 21;
const int D1 = 19;
const int D2 = 23;
const int D3 = 18;
const int D4 = 5;
const int D5 = 17;
const int D6 = 16;
const int D7 = 4;

const int dataPins[] = { D7, D6, D5, D4, D3, D2, D1, D0 };

const int Signals::MI = 27;
const int Signals::RI = 26;

void setDataPinsTo(int mode) {
  for (int pin = 0; pin < 8; pin += 1) {
    pinMode(dataPins[pin], mode);
  }
}

void Signals::init() {
  pinMode(MI, OUTPUT);
  pinMode(RI, OUTPUT);
  pinMode(RESET, OUTPUT);

  setDataPinsTo(OUTPUT);

  // Clock signals and programming mode are active low
  digitalWrite(CLK_AL, HIGH);
  pinMode(CLK_AL, OUTPUT);

  digitalWrite(ENABLE_MANUAL_CLK_AL, HIGH);
  pinMode(ENABLE_MANUAL_CLK_AL, OUTPUT);

  digitalWrite(ENABLE_PROGRAMMING_MODE_AL, HIGH);
  pinMode(ENABLE_PROGRAMMING_MODE_AL, OUTPUT);
}

void Signals::setReadMode() {
  setDataPinsTo(INPUT);
};

void Signals::setWriteMode() {
  setDataPinsTo(OUTPUT);
};

void Signals::setBus(char data[]) {
  for (int pin = 0; pin < 8; pin += 1) {
    int level = data[pin] == '1' ? HIGH : LOW;
    digitalWrite(dataPins[pin], level);
  }
};

void Signals::clearBus() {
  for (int pin = 0; pin < 8; pin += 1) {
    digitalWrite(dataPins[pin], LOW);
  }
}

void Signals::enableProgrammingMode() {
  digitalWrite(ENABLE_MANUAL_CLK_AL, LOW);
  digitalWrite(ENABLE_PROGRAMMING_MODE_AL, LOW);
}

void Signals::disableProgrammingMode() {
  digitalWrite(ENABLE_MANUAL_CLK_AL, HIGH);
  digitalWrite(ENABLE_PROGRAMMING_MODE_AL, HIGH);
}

void Signals::pulseClock() {
  digitalWrite(CLK_AL, HIGH);
  delay(10);
  digitalWrite(CLK_AL, LOW);
  delay(10);
  digitalWrite(CLK_AL, HIGH);
}

void Signals::pulsePinWithClock(int pin) {
  digitalWrite(pin, LOW);
  delay(10);
  digitalWrite(pin, HIGH);
  delay(10);

  pulseClock();
  delay(10);

  digitalWrite(pin, LOW);
  delay(10);
}

void Signals::pulseReset() {
  digitalWrite(RESET, LOW);
  delay(10);
  digitalWrite(RESET, HIGH);
  delay(10);
  digitalWrite(RESET, LOW);
}

