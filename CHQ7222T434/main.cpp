#include <RCSwitch.h>
#include <WiFi.h>
#include <WebServer.h>

// Define remote codes
#define FANEND "000000111111"
#define FANOFF "000000111101"
#define FANLOW "000000110111"
#define FANMED "000000101111"
#define FANHIGH "000000011111"
#define FANREVERSE "000000111011"

// Define RCswitch params
#define TXPIN 4
#define PULSE 334
#define PROT 11
#define REPEATS 10

// Wifi details
const char *SSID = "SSID";
const char *PWD = "PASSWORD";

void fanOff();
void fanLow();
void fanMed();
void fanHigh();
void fanReverse();

// Web server running on port 80
WebServer server(80);

RCSwitch mySwitch = RCSwitch();

// Connect to WiFi
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);
  
  WiFi.begin(SSID, PWD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void fanOff() {
  mySwitch.send(FANOFF);
  mySwitch.send(FANEND);
  server.send(200);
}

void fanLow() {
  mySwitch.send(FANLOW);
  mySwitch.send(FANEND);
  server.send(200);
}

void fanMed() {
  mySwitch.send(FANMED);
  mySwitch.send(FANEND);
  server.send(200);
}

void fanHigh() {
  mySwitch.send(FANHIGH);
  mySwitch.send(FANEND);
  server.send(200);
}

void fanReverse() {
  mySwitch.send(FANREVERSE);
  mySwitch.send(FANEND);
  server.send(200);
}

// API endpoints
void setup_routing() {	 	 
  server.on("/off", fanOff);	 	 
  server.on("/low", fanLow);	 	 
  server.on("/med", fanMed);	 	 
  server.on("/high", fanHigh);	 	 
  server.on("/reverse", fanReverse);	 	 
  	 	 
  // start server	 	 
  server.begin();	 	 
}

void setup() {
 Serial.begin(115200);

 // Transmitter GPIO Pin
 mySwitch.enableTransmit(TXPIN);

 // Set pulse length.
 mySwitch.setPulseLength(PULSE);

 // Set protocol
  mySwitch.setProtocol(PROT);

  // Number of repeats
  mySwitch.setRepeatTransmit(REPEATS);

  connectToWiFi();	 	 
  setup_routing(); 	 	 
}

void loop() {
  server.handleClient();	 	 
}