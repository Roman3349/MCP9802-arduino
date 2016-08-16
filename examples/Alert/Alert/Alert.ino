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
void alertHandler();

// Instances
MCP980X mcp(0x4B);

bool hasAlert;

/**
 * Init peripherals
 */
void setup() {
	Serial.begin(9600);
	// Wait for Serial
	while (!Serial) {
	}
	Serial.print("Initializing temperature sensor in the alert mode: ");
	mcp.begin();
	if (mcp.available()) {
		// Set 12 bit sensor resolution
		mcp.setResolution(12);
		// Temperatures ouuside 20-30*C trigger an alert
		mcp.setAlertLimits(20, 30);
		// Interrupt based. active high alert
		mcp.setAlertMode(mcp.MCP_INTERRUPT, true);
		// Allow a couple readings outside of the allowed range before triggering an alert
		mcp.setFaultQueue(mcp.MCP_2_FAULTS);
		// Use interrupt 0, interrupt pin connected to arduino pin 2
		attachInterrupt(2, alertHandler, RISING);
		Serial.println("OK");
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
	if (hasAlert) {
		Serial.println("Alert!");
		Serial.print("Temperature is");
		Serial.print(mcp.readTemperature(), 4);
		Serial.print("*C.");
		mcp.resetAlert();
		hasAlert = false;
	}
}

/**
 * Temperature alert handler
 */
void alertHandler() {
	hasAlert = true;
}
