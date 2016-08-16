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
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MCP980X.h>

// LOCAL PROTOTYPES
void setup();
void loop();

// Instances
MCP980X mcp(0x4B);
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16x2 LCD

/**+
 * Init peripherals
 */
void setup() {
	Serial.begin(9600);
	// Wait for Serial
	while (!Serial) {
	}
	mcp.begin();
	if (mcp.available()) {
		// Set 12 bit sensor resolution
		mcp.setResolution(12);
		Serial.println("OK.");
	} else {
		Serial.println("failed. Check connections.");
		while (true) {
		}
	}
	lcd.init();
	lcd.backlight();
	lcd.setCursor(2, 0);
	lcd.print("Thermometer");
	lcd.setCursor(4, 1);
	lcd.print("MCP980X");
	delay(500);
}

/**
 * Main loop
 */
void loop() {
	float temp = mcp.readTemperature();
	lcd.setCursor(2, 0);
	lcd.print("Temperature:");
	lcd.setCursor(0, 1);
	lcd.print(temp, 2);
	lcd.print("*C");
	lcd.setCursor(7, 1);
	lcd.print(mcp.toFahrenheit(temp), 2);
	lcd.print("*F");
	delay(500);
}
