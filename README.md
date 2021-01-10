# MCP980X-arduino

[![Build Status](https://badgen.net/github/checks/Roman3349/MCP980X-arduino/master?cache=300)](https://github.com/Roman3349/MCP980X-arduino/actions)
[![Apache License](https://badgen.net/github/license/Roman3349/MCP980X-arduino)](https://github.com/Roman3349/MCP980X-arduino/blob/master/LICENSE)

Arduino library for Microchip MCP9800, MCP9801, MCP9802 and MCP9803 temp sensors.

## Supported chips

|  Name   |                                Datasheet                                |
| ------- | ----------------------------------------------------------------------- |
| MCP9800 | [Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/21909c.pdf) |
| MCP9801 | [Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/21909c.pdf) |
| MCP9802 | [Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/21909c.pdf) |
| MCP9803 | [Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/21909c.pdf) |

### Chip features
 * Operating Voltage Range: 2.7V to 5.5V
 * Operating/Shutdown Current: 200 μA/1 μA
 * Selectable resolution: 9-12 bit
 * Accuracy with 12-bit Resolution:
   * ±0.5°C at +25°C
   * ±1°C from -10°C to +85°C
   * ±2°C from -10°C to +125°C
   * ±3°C from -55°C to +125°C
 * I2C interface
 * Power-saving One-shot Temperature Measurement
 * Available Packages: SOT-23-5, MSOP-8, SOIC-8

## Installation
The best way how to install this library is to [download a latest package](https://github.com/Roman3349/MCP980X-arduino/releases) or use [PlatformIO](http://platformio.org/):
```
pio lib install "roman3349/MCP980X"
```

## License
This library is licensed under Apache License 2.0:

 > Copyright 2016 Roman Ondráček <ondracek.roman@centrum.cz>
 > 
 > Licensed under the Apache License, Version 2.0 (the "License");
 > you may not use this file except in compliance with the License.
 > You may obtain a copy of the License at
 > 
 >     http://www.apache.org/licenses/LICENSE-2.0
 > 
 > Unless required by applicable law or agreed to in writing, software
 > distributed under the License is distributed on an "AS IS" BASIS,
 > WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 > See the License for the specific language governing permissions and
 > limitations under the License.
