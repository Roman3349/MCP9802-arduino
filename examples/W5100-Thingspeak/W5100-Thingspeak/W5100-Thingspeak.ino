/**
 * Copyright 2016 Roman Ondráček
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MCP980X.h>

// LOCAL PROTOTYPES
void setup();
void loop();
void updateThingSpeak(String tsData);
void startEthernet();

// Instances
MCP980X mcp(0x4B);
EthernetClient client;

// Local Network Settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFA, 0xCE};
// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "1234567890ABCDEF";
const int updateThingSpeakInterval = 16 * 1000;
// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;
int failedCounter = 0;

/**
 * Init peripherals
 */
void setup() {
  Serial.begin(9600);
  // Wait for Serial
  while (!Serial) {
  }
  mcp.begin();
  while (!mcp.available()) {
  }
  mcp.setResolution(12);
  startEthernet();
}

/**
 * Main loop
 */
void loop() {
  float temp = mcp.readTemperature();
  String tempString = String(temp, DEC);
  if (client.available())  {
    char c = client.read();
    Serial.print(c);
  }
  if (!client.connected() && lastConnected)  {
    Serial.println("...disconnected");
    Serial.println();
    client.stop();
  }
  if (!client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval)) {
    updateThingSpeak("field1=" + tempString);
  }
  if (failedCounter > 3) {
    startEthernet();
  }
  lastConnected = client.connected();
}

void updateThingSpeak(String tsData) {
  if (client.connect(thingSpeakAddress, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    lastConnectionTime = millis();
    if (client.connected()) {
      Serial.println("Connecting to ThingSpeak...");
      failedCounter = 0;
    } else {
      failedCounter++;
      Serial.println("Connection to ThingSpeak failed (" + String(failedCounter, DEC) + ")");
    }
  } else {
    failedCounter++;
    Serial.println("Connection to ThingSpeak failed (" + String(failedCounter, DEC) + ")");
    lastConnectionTime = millis();
  }
}

void startEthernet() {
  client.stop();
  Serial.println("Connecting Arduino to network...");
  Serial.println();
  delay(1000);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP Failed, reset Arduino to try again");
  } else {
    Serial.println("Arduino connected to network using DHCP");
  }
  delay(1000);
}
