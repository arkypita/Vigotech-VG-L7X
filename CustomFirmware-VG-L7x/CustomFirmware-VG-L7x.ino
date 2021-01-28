#include <Arduino.h>
#include <WiFi.h> 
#include <DNSServer.h>
#include <WebServer.h>
#include <Update.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager min v2 to support ESP32

WebServer httpServer(80);
const char* update_path = "/firmware";
const char* update_username = "admin";
const char* update_password = "admin";

#define RXD2 27 //RX Pin to m328p
#define TXD2 33 //TX Pin to m328p

#define MAX_SRV_CLIENTS 1

bool initializedWifi = false;

WiFiServer server(23);
WiFiClient serverClient;

int RESET_PIN = 0; // = GPIO0 on nodeMCU
WiFiManager wifiManager;

void setup()
{
  wifiManager.setDebugOutput(false);
  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);
  
  Serial.setRxBufferSize(1024);
  Serial.begin(115200);

  delay(1000); //BOOT WAIT

  Serial2.setRxBufferSize(1024); 
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  pinMode(RESET_PIN, INPUT_PULLUP);

  setupWifi();
}

void loop()
{
  if (!initializedWifi)
    setupWifi();
  else if (server.hasClient())
    AcceptConnection();
  else if (serverClient && serverClient.connected())
    ManageWifiConnected();
  else
    ManageUSBConnected();
  
  httpServer.handleClient();
}

void setupWifi() {
  wifiManager.autoConnect("ESP32");
  server.begin();
  server.setNoDelay(true);
  httpServer.begin();
  
  delay(5000); //wait for wifi connected
  initializedWifi = true;
}

void AcceptConnection()
{
  if (serverClient && serverClient.connected()) 
    serverClient.stop();

  serverClient = server.available();
  serverClient.write("ESP32 Connected!\n");
  delay(1000);
  Serial2.write(0x18); //soft-reset grbl after connection
}

void ManageWifiConnected()
{
    size_t rxlen = serverClient.available();
    if (rxlen > 0) {
      uint8_t sbuf[rxlen];
      serverClient.readBytes(sbuf, rxlen);
          Serial2.write(sbuf, rxlen);
    }
  
    size_t txlen = Serial2.available();
    if (txlen > 0) {
      uint8_t sbuf[txlen];
      Serial2.readBytes(sbuf, txlen);
          serverClient.write(sbuf, txlen);
    }
}

void ManageUSBConnected()
{    
    size_t rxlen = Serial.available();
    if (rxlen > 0) {
      uint8_t sbuf[rxlen];
      Serial.readBytes(sbuf, rxlen);
          Serial2.write(sbuf, rxlen);
    }
  
    size_t txlen = Serial2.available();
    if (txlen > 0) {
      uint8_t sbuf[txlen];
      Serial2.readBytes(sbuf, txlen);
          Serial.write(sbuf, txlen);
    }
}
