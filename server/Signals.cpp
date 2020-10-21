#include "Arduino.h"
#include "Signals.h"

const int CLK = 4; // TODO is this active low?
const int ENABLE_MANUAL_CLK  = 0; // TODO is this active low?
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

  pinMode(CLK, OUTPUT);
  pinMode(ENABLE_MANUAL_CLK, OUTPUT);
  pinMode(RESET, OUTPUT);

  setDataPinsTo(OUTPUT);
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
  digitalWrite(ENABLE_MANUAL_CLK, HIGH);
}

void Signals::disableManualClock() {
  digitalWrite(ENABLE_MANUAL_CLK, LOW);
}

void Signals::pulseClock() {
  digitalWrite(CLK, LOW);
  delay(1);
  digitalWrite(CLK, HIGH);
  delay(1);
  digitalWrite(CLK, LOW);
}

void Signals::pulsePin(int pin) {
  digitalWrite(pin, LOW);
  delay(1);
  digitalWrite(pin, HIGH);
  delay(1);

  // Pulse clock while the pin is high
  digitalWrite(CLK, LOW);
  delay(1);
  digitalWrite(CLK, HIGH);
  delay(1);
  digitalWrite(CLK, LOW);
  delay(1);

  digitalWrite(pin, LOW);
}

