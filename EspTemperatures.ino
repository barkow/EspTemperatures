#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "secrets.h"

MDNSResponder mdns;
// Replace with your network credentials

ESP8266WebServer server(80);

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void){
  //Mit Wifi verbinden
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  MDNS.begin("espTemperatures");

  sensors.begin();

  // this page is loaded when accessing the root of esp8266´s IP
  server.on("/", [](){
    //String webPage = mywebsite;
    //server.send(200, "text/html", webPage);
    sensors.requestTemperatures();
    server.send(200, "text/html", "Devices: " + String(sensors.getDeviceCount()) + " Temp: " + String(sensors.getTempCByIndex(0)));
  });
  
  server.begin();
}
void loop(void){
  server.handleClient();
}
