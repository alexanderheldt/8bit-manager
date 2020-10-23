#include <WiFi.h>
#include <WebServer.h>
#include "Signals.h"

const char* ssid = "";
const char* password = "";

Signals s;
WebServer server(80);

void help() {
  server.send( 200, "text/plain",
    "Existing endpoints: \n \
    /program POST program in the format: '<address> <data>' separated by new lines\n \
    /healthcheck");
}

void program() {
  String request = server.arg(0);

  char program[512];
  request.toCharArray(program, 512);

  // Split program on new line
  int n = 0;
  char *lines[512];

  char *newLine = strtok(program, "\n");
  while (newLine != NULL) {
    lines[n++] = newLine;
    newLine = strtok(NULL, "\n");
  }

  // split all lines on " "
  int m = 0;
  char* addressDataPairs[512];

  for (int i = 0; i < n; i++) {
    char *space = strtok(lines[i], " ");
    while (space != NULL) {
      addressDataPairs[m++] = space;
      space = strtok(NULL, " ");
    }
  }

  s.enableProgrammingMode();
  s.pulseReset();

  for (int i = 0; i < m; i += 2) {
    char* address = addressDataPairs[i];
    char* data = addressDataPairs[i+1];

    Serial.print("address: ");
    Serial.println(address);
    s.setBus(address);
    s.pulsePinWithClock(s.MI);

    delay(1 * 1000);

    Serial.print("data: ");
    Serial.println(data);
    s.setBus(data);
    s.pulsePinWithClock(s.RI);

    delay(1 * 1000);
  }

  s.disableProgrammingMode();

  // Clear bus
  s.setBus("00000000");
  server.send(200, "text/plain", "Programming completed");
}

void reset() {
  s.pulseReset();
  server.send(200, "text/plain", "Reset completed");
}

void pulseClock() {
  s.pulseClock();
  server.send(200, "text/plain", "Clock pulsed");
}

void healthcheck() {
  server.send(200, "text/plain", "A-OK");
}

void setup() {
  Serial.begin(57600);

  s.init();

  Serial.print("Connecting to wifi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Server started on IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", help);
  server.on("/program", program);
  server.on("/reset", reset);
  server.on("/pulseClock", pulseClock);
  server.on("/healthcheck", healthcheck);

  server.begin();
}

void loop() {
  server.handleClient();
 }
