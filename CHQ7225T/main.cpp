#include <RCSwitch.h>
#include <WiFi.h>
#include <WebServer.h>

// Define remote codes
#define FANON "00010101110110101001010000"
#define FANOFF "00010101110110100000010000"
#define FANUP "00010101110110101001010000"
#define FANDOWN "00010101110110101000010000"
#define TIMER2H "00010101110110101000011010"
#define TIMER4H "00010101110110101000011011"
#define TIMER8H "00010101110110101000011100"
#define TIMEROFF "00010101110110101000011001"
#define PULSELOW "00010101110110101011010000"
#define PULSEMED "00010101110110101100010000"
#define PULSEHIGH "00010101110110101101010000"
#define PULSEOFF "00010101110110101000000000"
#define REVUP "00010101110110101000100000"
#define REVDOWN "00010101110110101000010000"
#define LIGHT "00010101110110101000010001"

// Define RCswitch params
#define TXPIN 4
#define PULSE 282
#define PROT 11
#define REPEATS 30

// Wifi details
const char *SSID = "SSID";
const char *PWD = "PASSWORD";

void fanOn();
void fanOff();
void fanUp();
void fanDown();
void timer2H();
void timer4H();
void timer8H();
void timerOFF();
void pulseLow();
void pulseMed();
void pulseHigh();
void pulseOff();
void revUp();
void revDown();
void light();

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

void fanOn() {
  mySwitch.send(FANON);
  server.send(200);
}

void fanOff() {
  mySwitch.send(FANOFF);
  server.send(200);
}

void fanUp() {
  mySwitch.send(FANUP);
  server.send(200);
}

void fanDown() {
  mySwitch.send(FANDOWN);
  server.send(200);
}

void timer2H() {
  mySwitch.send(TIMER2H);
  server.send(200);
}

void timer4H() {
  mySwitch.send(TIMER4H);
  server.send(200);
}

void timer8H() {
  mySwitch.send(TIMER8H);
  server.send(200);
}

void timerOFF() {
  mySwitch.send(TIMEROFF);
  server.send(200);
}

void pulseLow() {
  mySwitch.send(PULSELOW);
  server.send(200);
}

void pulseMed() {
  mySwitch.send(PULSEMED);
  server.send(200);
}

void pulseHigh() {
  mySwitch.send(PULSEHIGH);
  server.send(200);
}

void pulseOFF() {
  mySwitch.send(PULSEOFF);
  server.send(200);
}

void revUp() {
  mySwitch.send(REVUP);
  server.send(200);
}

void revDown() {
  mySwitch.send(REVDOWN);
  server.send(200);
}

void light() {
  mySwitch.send(LIGHT);
  server.send(200);
}

// API endpoints
void setup_routing() {	 	 
  server.on("/on", fanOn);	 	 
  server.on("/off", fanOff);	 	 
  server.on("/fanUp", fanUp);	 	 
  server.on("/fanDown", fanDown);	 	 
  server.on("/timer2h", timer2H);
  server.on("/timer4h", timer4H);
  server.on("/timer8h", timer8H);
  server.on("/timerOff", timerOFF);
  server.on("/pulseLow", pulseLow);
  server.on("/pulseMed", pulseMed);
  server.on("/pulseHigh", pulseHigh);
  server.on("/pulseOff", pulseOFF);
  server.on("/revUp", revUp);
  server.on("/revDown", revDown);
  server.on("/light", light);
  	 	 
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