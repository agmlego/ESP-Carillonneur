#include <Arduino.h>
#include <WiFi.h>
// #include <WiFiUdp.h>
#include <AppleMIDI.h>
#include <ESPmDNS.h>

#include "bells.h"
#include "ssid.h"

int8_t isConnected = 0;

const struct {
  byte note;
  uint8_t pin;  
} bell_config[NUM_BELLS] = {
  // E7
  { 100, 16 },
  // C7
  { 96, 17 },
  // B6
  { 95, 18 },
  // A#6
  { 94, 19 },
  // A6
  { 93, 21 },
  // G#6
  { 92, 22 },
  // C6
  { 84, 33 },
  // C#6
  { 85, 32 },
  // D6
  { 86, 27 },
  // B5
  { 83, 26 },
  // G#5
  { 80, 25 },
  // F#6
  { 90, 23 }, // Suspect this is actually F#5/78
};

struct {
  unsigned long stop_time;
} bell_state[NUM_BELLS];

const size_t NO_BELL = -1;

APPLEMIDI_CREATE_DEFAULTSESSION_INSTANCE(); 

size_t find_bell(byte midi_note) {
  // TODO: Binary search?
  for (size_t i = 0; i < NUM_BELLS; i++) {
    if (bell_config[i].note == midi_note) {
      return i;
    }
  }
  return NO_BELL;
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

void setup()
{
  delay(5000);
  Serial.begin(115200);
  Serial.println("Setting up bells!");
  for (uint8_t bell = 0; bell < NUM_BELLS; ++bell)
  {
    pinMode(bells[bell], OUTPUT);
    bell_state[bell].stop_time = 0;
    Serial.print(bell_notes[bell]);
    Serial.print(" ");
  }
  Serial.println(" Done!");

  auto status = WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Waiting for WiFi connection");
    delay(1000);
  }

  printWifiData();

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

    auto bellidx = find_bell(note);
    if (bellidx != NO_BELL) {
      digitalWrite(bell_config[bellidx].pin, HIGH);
      bell_state[bellidx].stop_time = millis() + STRIKE_DURATION_MS;
    }
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

  auto now = millis();
  for (size_t i = 0; i < NUM_BELLS; i++) {
    auto stop_time = bell_state[i].stop_time;
    if (stop_time != 0 && stop_time < now) {
      digitalWrite(bell_config[i].pin, LOW);
      bell_state[i].stop_time = 0;
    }
  }
}