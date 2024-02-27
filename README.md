# Kindle Remote Control
A project that allows for wireless remote control of a Kindle e-reader running Koreader.

## Acknowledgement
Big thanks to user [bneo99](https://github.com/bneo99) for creating a base to create this project!

## Setup

## Kindle

### Jailbreak

### WiFi
The Kindle won't allow you to connect to a network that has no Internet access by default.
In the topmost level of USB storage, create the file named `WIFI_NO_NET_PROBE` (all capitals, no extension, no contents).
This has to be done when Koreader is NOT launched.
Once you've connected the Kindle to the network once, you do not need to mess with the Kindle's default WiFi settings.
You may turn on Airplane mode if you are afraid of losing your jailbreak.

## ESP32
Any ESP32-based dev board that supports WiFi AP can be utilized for this project.
[LILYGO's T-Lion board](https://www.lilygo.cc/products/t-lion) works great for this project, as it comes with a 5-way joystick and 18650 li-ion charging circuit which is ideal for remote operations.

### Flashing KindleWiFiRemote.ino
If using the Arduino IDE,
1. In your Arduino IDE, go to File > Preferences
2. Enter the following into the “Additional Board Manager URLs” field:

   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
4. Open the Boards Manager: Go to Tools > Board > Boards Manager…
5. Search for ESP32 and press install button for the “ESP32 by Espressif Systems“
6. Select your Board in Tools > Board menu
   - For the case of the T-Lion, use ESP32 Wrover Kit (all versions)
7. Upload the code after selecting the COM port

### Configuration

1. **Wi-Fi AP Configuration:**
   - SSID: `KindleRemote`
   - Password: `password`

2. **ESP32 Pin Configuration:**
   - Forward Button: Pin 36
   - Toggle Button: Pin 39
   - Down Button: Pin 33
   - Backward Button: Pin 34
   - Up Button: Pin 32

3. **Kindle Static IP Address:**
   - Kindle IP: `192.168.4.2`

### Usage

1. Connect the Kindle to the Wi-Fi network named `KindleRemote` using the provided password.
2. Open the Serial Monitor to view ESP32 status messages.
3. Press the corresponding buttons on your ESP32 to control the Kindle remotely:

   - Forward Button (`buttonPinForward`): Page forward.
   - Toggle Button (`buttonPinToggle`): Toggle night mode.
   - Down Button (`buttonPinDown`): Decrease brightness.
   - Backward Button (`buttonPinBackward`): Page backward.
   - Up Button (`buttonPinUp`): Increase brightness.

## Note

- The script uses a debounce mechanism to ensure accurate button presses.

- Adjust the Kindle's IP address in the script if needed (`const char *host = "192.168.4.2";`).

- The ESP32 runs at a lower frequency (`80MHz`) to reduce battery drain.

- The Kindle is assumed to be running a web server on port `8080`. Modify the `sendRequest` function if your Kindle uses a different port.

## Dependencies

- [WiFi.h](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFi.h)
- esp_wifi.h

## Disclaimer

This script is provided as-is, and you should use it responsibly. Ensure that you have the necessary permissions to control your Kindle remotely. The script assumes a certain setup and may require adjustments based on your specific environment.

---

Feel free to customize this README based on your preferences and add any additional information that might be relevant for users.
