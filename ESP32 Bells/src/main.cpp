#include <Arduino.h>
#include <WiFi.h>
// #include <WiFiUdp.h>
#include <AppleMIDI.h>
#include <ESPmDNS.h>

#include "bells.h"
#include "ssid.h"

unsigned long t0 = millis();
int8_t isConnected = 0;

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE(); 

void setup()
{
  delay(5000);
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
    Serial.println("Waiting for WiFi connection");
    delay(1000);
  }

  Serial.println("Beginning MIDI...");
  MIDI.begin(); // listens on channel 1

  AppleMIDI.setHandleConnected([](const APPLEMIDI_NAMESPACE::ssrc_t & ssrc, const char* name) {
    isConnected++;
    Serial.print("Connected to session ");
    Serial.print(ssrc);
    Serial.println(name);
  });
  AppleMIDI.setHandleDisconnected([](const APPLEMIDI_NAMESPACE::ssrc_t & ssrc) {
    isConnected--;
    Serial.print("Disconnected ");
    Serial.println(ssrc);
  });
  
  MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
    Serial.print("NoteOn ");
    Serial.print(note);
    Serial.print(" ");
    Serial.println(velocity);
  });
  MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
    Serial.print("NoteOff ");
    Serial.print(note);
    Serial.print(" ");
    Serial.println(velocity);
  });

  Serial.println("Beginning mDNS...");
  MDNS.begin("Ye Merrie Minstrels");

  Serial.println("Creating record...");
  MDNS.addService("apple-midi", "udp", AppleMIDI.getPort());

  Serial.println("Starting loop...");
}

void loop()
{
  MIDI.read();
  // printf("WiFi status: %i\n", WiFi.status());
  // printWifiData();
  // printCurrentNet();
  // delay(10000);
}