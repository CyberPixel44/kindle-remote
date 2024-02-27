#include <WiFi.h> // Include the Wi-Fi library
#include "esp_wifi.h"

const char *ssid = "KindleRemote"; // The name of the Wi-Fi network that will be created
const char *password = "password"; // The password required to connect to it

// kindle IP address
byte ip[] = {192, 168, 4, 2};
const char *host = "192.168.4.2";

#define buttonPinForward 36
#define buttonPinToggle 39
#define buttonPinDown 33
#define buttonPinBackward 34
#define buttonPinUp 32

bool lastButtonStateForward = HIGH;  // initial state is not pressed
bool lastButtonStateToggle = HIGH;   // initial state is not pressed
bool lastButtonStateDown = HIGH;     // initial state is not pressed
bool lastButtonStateBackward = HIGH; // initial state is not pressed
bool lastButtonStateUp = HIGH;       // initial state is not pressed

WiFiClient client;

void setup()
{

  setCpuFrequencyMhz(80); // decreases battery drain over 2x! (30mA) vs (63mA original)

  pinMode(buttonPinForward, INPUT_PULLUP);  // forward button pin
  pinMode(buttonPinToggle, INPUT_PULLUP);   // toggle button pin
  pinMode(buttonPinDown, INPUT_PULLUP);     // down button pin
  pinMode(buttonPinBackward, INPUT_PULLUP); // backward button pin
  pinMode(buttonPinUp, INPUT_PULLUP);       // up button pin

  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password); // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP()); // Send the IP address of the ESP8266 to the computer

  delay(1000);
}

void loop()
{
  // debounce button code for perfect button listening :)
  // read button Forward
  bool buttonStateForward = digitalRead(buttonPinForward);
  if (buttonStateForward != lastButtonStateForward && buttonStateForward == LOW)
  {
    PageForward();
  }
  lastButtonStateForward = buttonStateForward;

  // read button Toggle
  bool buttonStateToggle = digitalRead(buttonPinToggle);
  if (buttonStateToggle != lastButtonStateToggle && buttonStateToggle == LOW)
  {
    ToggleNightMode();
  }
  lastButtonStateToggle = buttonStateToggle;

  // read button Down
  bool buttonStateDown = digitalRead(buttonPinDown);
  if (buttonStateDown != lastButtonStateDown && buttonStateDown == LOW)
  {
    DecreaseBrightness();
  }
  lastButtonStateDown = buttonStateDown;

  // read button Backward
  bool buttonStateBackward = digitalRead(buttonPinBackward);
  if (buttonStateBackward != lastButtonStateBackward && buttonStateBackward == LOW)
  {
    PageBackward();
  }
  lastButtonStateBackward = buttonStateBackward;

  // read button Up
  bool buttonStateUp = digitalRead(buttonPinUp);
  if (buttonStateUp != lastButtonStateUp && buttonStateUp == LOW)
  {
    IncreaseBrightness();
  }
  lastButtonStateUp = buttonStateUp;

  delay(50); // debounce delay
}

void sendRequest(const char *action)
{
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(ip, 8080)) // port 8080 configured within the kindle
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]"); // send the HTTP request to kindle
    client.print(String("GET /?action=") + action + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n");
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(500);
}

void PageForward()
{
  Serial.println("Front Clicked!");
  sendRequest("nextpage");
}

void ToggleNightMode()
{
  Serial.println("Toggle Clicked!");
  sendRequest("togglenightmode");
}

void DecreaseBrightness()
{
  Serial.println("Down Clicked!");
  sendRequest("decreasebrightness");
}

void PageBackward()
{
  Serial.println("Back Clicked!");
  sendRequest("prevpage");
}

void IncreaseBrightness()
{
  Serial.println("Up Clicked!");
  sendRequest("increasebrightness");
}