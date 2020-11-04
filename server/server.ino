#include <WiFi.h>
#include <WebServer.h>
#include "Signals.h"

const char* ssid = "yoalex";
const char* password = "latkatt1";

Signals s;
WebServer server(80);

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

  s.connectToComputer();
  s.enableProgrammingMode();
  s.pulseReset();

  for (int i = 0; i < m; i += 2) {
    char* address = addressDataPairs[i];
    char* data = addressDataPairs[i+1];

    Serial.print("address: ");
    Serial.println(address);
    s.setBus(address);
    s.pulsePinWithClock(s.MI);

    delay(100);
    s.clearBus();

    Serial.print("data: \t");
    Serial.println(data);
    s.setBus(data);
    s.pulsePinWithClock(s.RI);

    delay(100);
    s.clearBus();
  }

  s.pulseReset();
  s.disableProgrammingMode();
  s.disconnectFromComputer();

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

void enableProgrammingMode() {
  s.enableProgrammingMode();
  server.send(200, "text/plain", "Programming mode enabled");
}

void disableProgrammingMode() {
  s.disableProgrammingMode();
  server.send(200, "text/plain", "Programming mode disabled");
}

void enableMI() {
  digitalWrite(s.MI, HIGH);
  server.send(200, "text/plain", "MI enabled");
}

void disableMI() {
  digitalWrite(s.MI, LOW);
  server.send(200, "text/plain", "MI disabled");
}

void enableRI() {
  digitalWrite(s.RI, HIGH);
  server.send(200, "text/plain", "RI enabled");
}

void disableRI() {
  digitalWrite(s.RI, LOW);
  server.send(200, "text/plain", "RI disabled");
}

void connect() {
  s.connectToComputer();
  server.send(200, "text/plain", "Connected");
}

void disconnect() {
  s.disconnectFromComputer();
  server.send(200, "text/plain", "Disconnected");
}

void setBus() {
  String request = server.pathArg(0);

  char pattern[16];
  request.toCharArray(pattern, 16);

  Serial.print("Pattern: ");
  Serial.println(pattern);

  s.setWriteMode();
  delay(10);
  s.setBus(pattern);

  server.send(200, "text/plain", "Bus set");
}

void clearBus() {
  s.clearBus();
  server.send(200, "text/plain", "Bus cleared");
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

  server.on("/program", program);
  server.on("/reset", reset);

  server.on("/pulseClock", pulseClock);
  server.on("/connect", connect);
  server.on("/disconnect", disconnect);

  server.on("/set-bus/{}", setBus);
  server.on("/clear-bus", clearBus);

  server.on("/enable-programming", enableProgrammingMode);
  server.on("/disable-programming", disableProgrammingMode);

  server.on("/enable-mi", enableMI);
  server.on("/disable-mi", disableMI);
  server.on("/enable-ri", enableRI);
  server.on("/disable-ri", disableRI);

  server.on("/healthcheck", healthcheck);

  server.begin();
}

void loop() {
  server.handleClient();
 }
