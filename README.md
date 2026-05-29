# BlinkRateControll

BlinkRateControll is a microcontroller project designed to control the blink rate of an LED.

I designed this with the use of an Arduino Uno R3.

There is an LED and three buttons to control the LED to blink (on/off, blink faster, blink slower)

<img width="4065" height="3317" alt="BlinkRateControl" src="https://github.com/user-attachments/assets/13447eac-5b05-4837-9a5c-3ffe61ec46b9" />

Built using PlatformIO, it provides a simple and extensible framework for experimenting with timing, digital output, and embedded C++ development by bare metal coding.

## Features
- Toggelable LED blink
- Adjustable LED blink rate
- Modular code structure (helpers and main logic separated)
- Easy to extend for additional hardware or features
- PlatformIO-based for easy build and upload

## Project Structure
```
BlinkRateControll/
├── include/         # Header files
│   └── helpers.h
├── lib/             # Project-specific libraries
├── src/             # Source files
│   ├── main.cpp
│   └── helpers.cpp
├── test/            # Test files (empty at the moment)
├── platformio.ini   # PlatformIO configuration
```

## Getting Started

### Prerequisites
- [PlatformIO](https://platformio.org/) installed (VS Code extention recommended)
- Supported microcontroller board Arduino Uno R3

### Building and Uploading
1. Clone this repository:
   ```sh
   git clone https://github.com/Dylanlucas01/BlinkRateControll.git
   ```
2. Open the project in VS Code with PlatformIO extension.
3. Connect your microcontroller board.
4. Build and upload the firmware using PlatformIO's interface or:
   ```sh
   pio run --target upload
   ```

## Usage
- The default behavior is to blink an LED at a set interval.
- You can modify the blink rate or pin assignments in `src/main.cpp` or via helper functions in `src/helpers.cpp` and `include/helpers.h`.
