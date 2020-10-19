#include <WiFi.h>
#include <WebServer.h>

#define CLK 4

const char* ssid = "";
const char* password = "";

bool CLK_ON = LOW;

WebServer server(80);

void help() {
  server.send( 200, "text/plain",
    "Existing endpoints: \n \
    /program POST program in the format: '<address> <data>' separated by new lines\n \
    /healthcheck");
}

void program() {
  String data = server.arg(0);

  char program[256];
  data.toCharArray(program, 256);

  int n = 0;
  char *lines[256];

  char *token = strtok(program, "\n");
  while (token != NULL) {
    lines[n++] = token;
    token = strtok(NULL, "\n");
  }

  for (int i = 0; i < n; i++) {
    Serial.println(lines[i]);
  }

  server.send(200, "text/plain", "Programming completed");
}

void healthcheck() {
  CLK_ON = !CLK_ON;
  digitalWrite(CLK, CLK_ON);

  server.send(200, "text/plain", "A-OK");
}

void setup() {
  Serial.begin(57600);

  pinMode(CLK, OUTPUT);

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
  server.on("/healthcheck", healthcheck);

  server.begin();
}

void loop() {
  server.handleClient();
 }
