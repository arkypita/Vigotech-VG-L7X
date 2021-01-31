#include <Arduino.h>
#include <WiFi.h> 
#include <DNSServer.h>
#include <WebServer.h>
#include <Update.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager min v2 to support ESP32
#include "esp_wps.h"
#include "soc/uart_reg.h"
#include "soc/uart_struct.h"


WebServer httpServer(80);
const char* update_path = "/firmware";
const char* update_username = "admin";
const char* update_password = "admin";

#define RXD2              27 //RX Pin to m328p
#define TXD2              33 //TX Pin to m328p
#define MAX_SRV_CLIENTS    1
#define LONG_PRESS_TIME   5000
#define SHORT_PRESS_TIME  500
#define ESP_WPS_MODE      WPS_TYPE_PBC

unsigned long buttonpressed = 0;
unsigned long buttonreleased = 0;

bool buttoncurrentState = false;
bool buttonlastState = true;

bool initializedWifi = false;
int wpspin = 32;
int button2 = 0;
int beeper = 21;

WiFiServer server(23);
WiFiClient serverClient;

int RESET_PIN = 0; // = GPIO0 on nodeMCU
WiFiManager wifiManager;

static esp_wps_config_t config;

void setup()
{
  //wifiManager.setDebugOutput(false);
  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);
  pinMode(wpspin, INPUT_PULLUP);
  pinMode(button2, INPUT);
  
  Serial.begin(115200);
  Serial.setRxBufferSize(1024);

  uart_dev_t * dev = (volatile uart_dev_t *)(DR_REG_UART_BASE) ;
  dev->conf1.rxfifo_full_thrhd = 1 ;  // set the number of char received on Serial to 1 before generating an interrupt (original value is 112 and is set by esp32-hal-uart.c)
                                      // this increase the number of interrupts but it allows to forward the char to Serial2 faster
  dev->conf1.rx_tout_thrhd = 1;

  ledcSetup(0, 2000, 8);
  ledcAttachPin(beeper, 0);
  ledcWriteTone(0, 2000);

  delay(500); //BOOT WAIT
  ledcWriteTone(0, 0);
 
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial2.setRxBufferSize(1024);
  
  pinMode(RESET_PIN, INPUT_PULLUP);
  
  WiFi.begin();
  int i = 0;
  while (WiFi.status() != WL_CONNECTED && i < 10) {
    delay(500);
    Serial.print(".");
    i++;
  }
 
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
}

void loop()
{
  switch (buttoncheck(wpspin)) {
    case 0: // no press do nothing
      break;
    case 1: // short press
      startWPS();
      setupWifi();
      break;
    case 2: // long press
      server.stop();
      httpServer.stop();
      WiFi.disconnect();
      delay(50);
      Serial.println("Starting WiFi Manager");
      wifiManager.startConfigPortal("ESP32");
      setupWifi();
      break;
  }

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
  server.begin();
  server.setNoDelay(true);
  httpServer.begin();
  
  delay(500); //wait for wifi connected
  initializedWifi = true;
}

void AcceptConnection()
{
  if (serverClient && serverClient.connected()) 
    serverClient.stop();

  serverClient = server.available();
  serverClient.write("ESP32 Connected!\n");
  delay(500);
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

long buttoncheck( int buttonno){
  buttoncurrentState = digitalRead(buttonno); //read the button
  
  if (buttonlastState == HIGH && buttoncurrentState == LOW){ //button pressed
    buttonpressed = millis();
  }
  else if (buttonlastState == LOW && buttoncurrentState == HIGH){ //button released
    buttonreleased = millis();
  }

  if (buttonpressed == 0){ //do nothing if nothing changed
    return 0;
  }
  
  long pressDuration = buttonreleased - buttonpressed;
  buttonlastState = buttoncurrentState; //save the last state
  
  if (pressDuration >= SHORT_PRESS_TIME && pressDuration < LONG_PRESS_TIME){
    buttonpressed = 0;
    buttonreleased = 0;
    return 1; //shortpress 
  }
  else if (pressDuration > LONG_PRESS_TIME){ 
    buttonpressed = 0;
    buttonreleased = 0;
    return 2;
  }
}

void startWPS(){
  WiFi.onEvent(WiFiEvent);
  WiFi.mode(WIFI_MODE_STA);

  Serial.println("Starting WPS");

  wpsInitConfig();
  esp_wifi_wps_enable(&config);
  esp_wifi_wps_start(0);
}

void wpsInitConfig(){
  config.crypto_funcs = &g_wifi_default_wps_crypto_funcs;
  config.wps_type = ESP_WPS_MODE;
}

void WiFiEvent(WiFiEvent_t event, system_event_info_t info){
  switch(event){
    case SYSTEM_EVENT_STA_START:
      Serial.println("Station Mode Started");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("Connected to :" + String(WiFi.SSID()));
      Serial.print("Got IP: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Disconnected from station, attempting reconnection");
      WiFi.reconnect();
      break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
      Serial.println("WPS Successful, stopping WPS and connecting to: " + String(WiFi.SSID()));
      esp_wifi_wps_disable();
      delay(10);
      WiFi.begin();
      break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
      Serial.println("WPS Failed, retrying");
      esp_wifi_wps_disable();
      esp_wifi_wps_enable(&config);
      esp_wifi_wps_start(0);
      break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
      Serial.println("WPS Timeout, retrying");
      esp_wifi_wps_disable();
      esp_wifi_wps_enable(&config);
      esp_wifi_wps_start(0);
      break;
    default:
      break;
  }
}

  
