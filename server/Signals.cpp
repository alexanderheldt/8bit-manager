#include "Arduino.h"
#include "Signals.h"

// clock signals are active low
const int CLK_AL = 4;
const int ENABLE_MANUAL_CLK_AL = 15;

const int RESET = 2;

const int D0 = 22;
const int D1 = 21;
const int D2 = 19;
const int D3 = 23;
const int D4 = 18;
const int D5 = 5;
const int D6 = 17;
const int D7 = 16;

const int dataPins[] = { D7, D6, D5, D4, D3, D2, D1, D0 };

const int Signals::MI = 13;
const int Signals::RI = 12;
const int Signals::II = 14;
const int Signals::AI = 27;
const int Signals::BI = 26;
const int Signals::OI = 25;
const int Signals::FI = 33;

void setDataPinsTo(int mode) {
  for (int pin = 0; pin < 8; pin += 1) {
    pinMode(dataPins[pin], mode);
  }
}

void Signals::init() {
  pinMode(MI, OUTPUT);
  pinMode(RI, OUTPUT);
  pinMode(II, OUTPUT);
  pinMode(AI, OUTPUT);
  pinMode(BI, OUTPUT);
  pinMode(OI, OUTPUT);
  pinMode(FI, OUTPUT);

  pinMode(RESET, OUTPUT);

  setDataPinsTo(OUTPUT);

  // Clock signals are active low
  digitalWrite(CLK_AL, HIGH);
  pinMode(CLK_AL, OUTPUT);

  digitalWrite(ENABLE_MANUAL_CLK_AL, HIGH);
  pinMode(ENABLE_MANUAL_CLK_AL, OUTPUT);
}

void Signals::setReadMode() {
  setDataPinsTo(INPUT);
};

void Signals::setWriteMode() {
  setDataPinsTo(OUTPUT);
};

void Signals::setBus(char data[]) {
  for (int pin = 0; pin <= 8; pin += 1) {
    int level = data[pin] == '1' ? HIGH : LOW;
    digitalWrite(dataPins[pin], level);
  }
};

void Signals::clearBus() {
  for (int pin = 0; pin <= 8; pin += 1) {
    digitalWrite(dataPins[pin], LOW);
  }
}

void Signals::enableManualClock() {
  digitalWrite(ENABLE_MANUAL_CLK_AL, LOW);
}

void Signals::disableManualClock() {
  digitalWrite(ENABLE_MANUAL_CLK_AL, HIGH);
}

void Signals::pulseClock() {
  digitalWrite(CLK_AL, HIGH);
  delay(1);
  digitalWrite(CLK_AL, LOW);
  delay(1);
  digitalWrite(CLK_AL, HIGH);
}

void Signals::pulsePinWithClock(int pin) {
  digitalWrite(pin, LOW);
  delay(1);
  digitalWrite(pin, HIGH);
  delay(1);

  pulseClock();
  delay(1);

  digitalWrite(pin, LOW);
}

void Signals::pulseReset() {
  digitalWrite(RESET, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(RESET, LOW);
}

