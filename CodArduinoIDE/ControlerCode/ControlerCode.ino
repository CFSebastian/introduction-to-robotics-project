#include <FastLED.h>
#include "BLEDevice.h"

#define BAUD_RATE 115200
#define A5 0
#define A4 4
#define A3 3
#define NUM_LEDS 1
#define LED_PIN 20  
#define LED_BRIGHTNESS 5

//BLE
#define CLIENT_MTU_VALUE 517
#define SCAN_INTERVAL 1349
#define SCAN_WINDOW 449
#define SCAN_DURATION 5



CRGB leds[NUM_LEDS];
int xVal;
int yVal;
int bttState;

// UUIDs for the BLE service and characteristics
static BLEUUID serviceUUID("9765cce2-6fba-4643-9c3d-4665a29545c3");
static BLEUUID xAxesUUID("02732da3-bf6d-43e1-a0bc-a61e69c299b9");
static BLEUUID yAxesUUID("4954805c-f7bd-4a95-a0ec-0e2a11453c36");
static BLEUUID btnUUID("c03ea1d4-4c2f-469f-be40-df90304f00c1");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
bool deviceConnected = false;
bool oldDeviceConnected = false;

static BLEAdvertisedDevice *myDevice;
static BLERemoteCharacteristic *pRemoteCharX;
static BLERemoteCharacteristic *pRemoteCharY;
static BLERemoteCharacteristic *pRemoteCharBtn;

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient *pclient) override {
    deviceConnected = true;
  }

  void onDisconnect(BLEClient *pclient) override {
    connected = false;
    deviceConnected = false;
    Serial.println("Disconnected from server");
  }
};

// Function to check and validate characteristics
bool connectCharacteristic(BLERemoteCharacteristic *l_BLERemoteChar) {
  if (l_BLERemoteChar == nullptr) {
    Serial.println("Failed to find characteristic");
    return false;
  }
  Serial.println("Found characteristic: " + String(l_BLERemoteChar->getUUID().toString().c_str()));
  return true;
}

// Function to connect to the BLE server
bool connectToServer() {
  Serial.print("Connecting to device: ");
  Serial.println(myDevice->getAddress().toString().c_str());

  BLEClient *pClient = BLEDevice::createClient();
  Serial.println("Client created");

  pClient->setClientCallbacks(new MyClientCallback());
  pClient->connect(myDevice);
  Serial.println("Connected to server");
  pClient->setMTU(CLIENT_MTU_VALUE);

  BLERemoteService *pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.println("Failed to find service UUID");
    pClient->disconnect();
    return false;
  }
  Serial.println("Service found");

  // Get the characteristics
  pRemoteCharX = pRemoteService->getCharacteristic(xAxesUUID);
  pRemoteCharY = pRemoteService->getCharacteristic(yAxesUUID);
  pRemoteCharBtn = pRemoteService->getCharacteristic(btnUUID);

  if (!connectCharacteristic(pRemoteCharX) ||
      !connectCharacteristic(pRemoteCharY) ||
      !connectCharacteristic(pRemoteCharBtn)) {
    pClient->disconnect();
    Serial.println("Failed to find one or more characteristics");
    return false;
  }

  connected = true;
  return true;
}

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) override {
    Serial.print("Found BLE device: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;
    }
  }
};

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("Starting BLE Client application...");

  BLEDevice::init("");

  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(SCAN_INTERVAL);
  pBLEScan->setWindow(SCAN_WINDOW);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(SCAN_DURATION, false);

  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
}

void loop() {
  xVal = analogRead(A4);
  yVal = analogRead(A3);
  bttState = digitalRead(A5);

  if (doConnect) {
    if (connectToServer()) {
      Serial.println("Connected to BLE server");
    } else {
      Serial.println("Failed to connect to BLE server");
    }
    doConnect = false;
  }

  if (connected) {//Transmit to the server the joystick data
    pRemoteCharX->writeValue(String(xVal), String(xVal).length());
    Serial.print("X: ");
    Serial.print(xVal);

    pRemoteCharY->writeValue(String(yVal), String(yVal).length());
    Serial.print(" | Y: ");
    Serial.print(yVal);

    pRemoteCharBtn->writeValue(String(bttState), String(bttState).length());
    Serial.print(" | Button: ");
    Serial.println(bttState);
  } else if (doScan) {
    leds[0] = CRGB::Green;
    BLEDevice::getScan()->start(0);
  }
  // set the RGB led when connected to the car
  if (deviceConnected) {
    leds[0] = CRGB::Blue;
  } 
  else {
    leds[0] = CRGB::Green;
  }

  FastLED.show();

  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }
}
