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
#include <MCP980X.h>

// LOCAL PROTOTYPES
void setup();
void loop();

// Instances
MCP980X mcp(0x4B);

/**
 * Init peripherals
 */
void setup() {
  Serial.begin(9600);
  // Wait for Serial
  while (!Serial) {
  }
  Serial.print("Initializing temperature sensor (integer): ");
  mcp.begin();
  if (mcp.available()) {
    Serial.println("OK.");
  } else {
    Serial.println("failed. Check connections.");
    while (true) {
    }
  }
}

/**
 * Main loop
 */
void loop() {
  // Temperature is multiplied by 16
  float temp = mcp.readTemperatureInt();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("*C\t");
  Serial.print(mcp.toFahrenheit(temp));
  Serial.println("*F");
  delay(500);
}
