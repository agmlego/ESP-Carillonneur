#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <AppleMIDI.h>

#include "bells.h"
#include "ssid.h"

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE(); 

void setup()
{
  Serial.begin(115200);
  Serial.println("Setting up bells!");
  for (uint8_t bell = 0; bell < NUM_BELLS; ++bell)
  {
    pinMode(bells[bell], OUTPUT);
    Serial.print(bell_notes[bell]);
    Serial.print(" ");
  }
  Serial.println(" Done!");

  auto status = WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    printf("Waiting for WiFi connection\n");
    delay(1000);
  }

  MIDI.begin(); // listens on channel 1
}


void printWifiData() 
{
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}


void printCurrentNet() 
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print the MAC address of the router you're attached to:
  Serial.print("BSSID: ");
  Serial.println(WiFi.BSSIDstr());
  // print the received signal strength:
  Serial.print("signal strength (RSSI):");
  Serial.println(WiFi.RSSI());
  // // print the encryption type:
  // byte encryption = WiFi.encryptionType();
  // Serial.print("Encryption Type:");
  // Serial.println(encryption, HEX);
  // Serial.println();
}

void loop()
{
  MIDI.read();
  // printf("WiFi status: %i\n", WiFi.status());
  // printWifiData();
  // printCurrentNet();
  // delay(10000);
}