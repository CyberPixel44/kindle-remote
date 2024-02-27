# Kindle Remote Control
A project that allows for wireless remote control of a Kindle e-reader running Koreader.

## Acknowledgement
Big thanks to user [bneo99](https://github.com/bneo99) for creating a base to create this project!

# Setup

## Kindle

### Jailbreak
For most up to date jailbreak info, monitor the mobilread forums

\[UPDATED JUL 23]

[Forum Help](https://www.mobileread.com/forums/showthread.php?t=356872)
Download [relevant files](https://github.com/notmarek/LanguageBreak/releases/latest).
Instructions from [notmarek](https://github.com/notmarek/LanguageBreak):

Warnings

    ⚠️ This method will DELETE all content on your device. Backup important files.
    ⚠️ This method works up to firmware version 5.16.2.1.1. It is strongly suggested you upgrade to this firmware before starting.
    ⚠️ Do not update your firmware beyond 5.16.2.1.1 after jailbreaking with LanguageBreak, as future versions of the firmware patch it.
    ⚠️ Your device must have no password lock. Remove it before starting.

Before you start, make sure:

    Airplane Mode is ON
    The device (esp. the root folder) should have no .bin or update.bin.tmp.partial files before you start. This may be a pending OTA update. Delete them.

Jailbreaking your Kindle

    Type ;enter_demo into the Kindle search bar, press enter, then reboot the device.
    Once the device boots, dismiss the wifi selection dialog, type whatever you'd like into the text fields, then continue.
    Select Skip, then Standard, then Done
    The device will take a few minutes to go into demo mode. When it's done, use this gesture to access the main screen.
    Type ;demo into the Kindle search bar, then press enter to access the Demo Mode Configuration screen.
    Select the Sideload Content option.
    Connect your Kindle to a PC, then copy the contents of the LanguageBreak folder to the Kindle's root directory (if prompted, overrwrite the existing files).
    Eject, then unplug your Kindle, then return to the Demo Configuration Screen (using the method in step 5, if required).
    Select Resell Device, then confirm.
    As soon as the "Press the Power Button" screen appears, plug your Kindle back into your computer. (This is time sensitive, be quick.)
    Copy the contents of the LanguageBreak folder to the Kindle's root directory, again. (if prompted, overrwrite the existing files).
    After all files have been written, eject your Kindle, then press and hold the power button until the unit reboots.
    At this point, a language selection screen appears. Select 简体中文 (Chinese), which should appear above an entry called Pseudot and below Japanese.
    Your Kindle should reboot, and some log messages should appear in the top right-hand corner.

Applying the Hotfix

    After the device has rebooted, type ;uzb into the Kindle search bar to enable USB access within demo mode, then press enter.
    Connect the device to a PC and copy whichever Update_hotfix_languagebreak-{languge/locale}.bin file matches your language to the Kindle's root directory.
    Eject your Kindle, then ;dsts into the Kindle search bar to access the settings page. Locate the Update your Kindle option and press it, then confirm.

    Using your phone to translate the menus is helpful if you don't happen to be able to read Chinese.

This will reboot the device out of Demo mode. Your device may go into Managed mode after completing these steps. Managed devices have some settings greyed out, and ask the user to contact their system administrator. See below for steps on how to restore functionality (and the correct language) to your device.
Restoring the Correct Language and Exiting Managed Mode
If your kindle is not registered to an Amazon account:

    Type ;demo into the Kindle search bar.
    You will get a prompt with two buttons. Press the right-most button.
    The device will reboot. If all is well, your Kindle should have a folder named mkk in the root directory.

If your kindle is registered to an Amazon account:

    Enter ;enter_demo into the Kindle search bar, then reboot your device.
    The device will be back in full "Demo Mode". Use the same gesture to access the main screen.
    Enter ;demo into the Kindle search bar.
    Select Resell device, then confirm.
    The device will reboot. If all is well, your Kindle should have a folder named mkk in the root directory.


### WiFi
The Kindle won't allow you to connect to a network that has no Internet access by default.
In the topmost level of USB storage, create the file named `WIFI_NO_NET_PROBE` (all capitals, no extension, no contents).
This has to be done when Koreader is NOT launched.
Once you've connected the Kindle to the network once, you do not need to mess with the Kindle's default WiFi settings.
You may turn on Airplane mode if you are afraid of losing your jailbreak.

### Koreader
Before installing Koreader, you must install KUAL:
- Download `MR Package Installer` from [mobilread](https://www.mobileread.com/forums/showthread.php?t=225030).
- Extract. Copy all files to Kindle.
- Download `KUAL (coplate).` from [mobilread](https://www.mobileread.com/forums/showthread.php?t=225030).
- Extract it and put `Update_KUALBooklet_ff4134d_install.bin` in the `mrpackages` folder on the kindle and enter `;log mrpi` into the search bar (where you search for books).
- Read [this section at the end of this page to](https://github.com/koreader/koreader/wiki/Installation-on-Kindle-devices#err-there-are-three-kindle-packages-to-choose-from-which-do-i-pick) figure out which Kindle release you want to download.
- Download the latest Kindle package from this page.
- Unzip the whole archive into the Kindle's USB root directory

After installing Koreader, extract the contents of the `plugins` directory provided in this repository into the `koreader` folder of the Kindle found in the root of the Kindle. (`koreader/plugins/httpremote.koplugin/...`)

Once setup, you can find the plugin menu in the toolbar of Koreader. I suggest enabling autostart to start the listening server on the Kindle whenever turned on.
Turn on WiFi from Koreader ONLY! If you turn on WiFi in the main OS, you may run the risk of updating your Kindle and losing your jailbreak.
Your Koreader should automatically connect to the KindleRemote access point, as you configured it previously.


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

### Dependencies

- [WiFi.h](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFi.h)
- esp_wifi.h

### Configuration

1. **Wi-Fi AP Configuration:**
   - SSID: `KindleRemote`
   - Password: `password`

2. **ESP32 Pin Configuration:**
   These pins are default for the T-Lion
   - Forward Button: Pin 36
   - Toggle Button: Pin 39
   - Down Button: Pin 33
   - Backward Button: Pin 34
   - Up Button: Pin 32

3. **Kindle Static IP Address:**
   - The Kindle will normally get assigned the same default IP whenever connected to the ESP32's AP
   - To determine this (only has to be done once), open `Network Settings` in Koreader and click on `Network Info` to view the Kindle's local IP address
   - Replace the field with this local address: `Kindle IP: <local_IP>`
  
### 3D Printed Enclosure
To protect the ESP32 T-Lion from LILYGO, I designed 3D printable models that enclose the remote.
The STL files can be found in this repository as `Remote Bottom.stl` and `Remote Top.stl`

To print, simply slice them in slicing software such as [Aultimaker Cura](https://ultimaker.com/software/ultimaker-cura/) and print!
Mounting the base is tricky:
- WARNING: The remote DOES NOT SLIDE IN! You will damage some traces and resistors!!!
1) Insert one of the edges directly into the groove from above such that the remote sits at an angle with one edge completely inside the groove and the other sticking out.
2) Gently press down on the edge that is sticking out and pull back on the casing with your other hand to force the grooves around and on top of the other side.
3) Adjust the forwards and backwards position to seat the board properly.


# Usage

1. Connect the Kindle to the Wi-Fi network named `KindleRemote` using the provided password.
2. Open the Serial Monitor to view ESP32 status messages.
3. Press the corresponding buttons on your ESP32 to control the Kindle remotely:

   - Forward Button (`buttonPinForward`): Page forward.
   - Toggle Button (`buttonPinToggle`): Toggle night mode.
   - Down Button (`buttonPinDown`): Decrease brightness.
   - Backward Button (`buttonPinBackward`): Page backward.
   - Up Button (`buttonPinUp`): Increase brightness.


## Disclaimer

This script is provided as-is, and you should use it responsibly. Ensure that you have the necessary permissions to control your Kindle remotely. The script assumes a certain setup and may require adjustments based on your specific environment.
