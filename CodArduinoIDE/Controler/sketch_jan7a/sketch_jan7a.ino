#include <FastLED.h>
#include "BLEDevice.h"
//#include "BLEScan.h"

#define BAUD_RATE 9600
#define A5 0
#define A4 4
#define A3 3
#define NUM_LEDS 1
#define LED_PIN 20

CRGB leds[NUM_LEDS];
int xVal;
int yVal;
int bttState;

// The remote service we wish to connect to.
//static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
// The characteristic of the remote service we are interested in.
//static BLEUUID charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");

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
  void onConnect(BLEClient *pclient) {
    deviceConnected = true;
  }

  void onDisconnect(BLEClient *pclient) {
    connected = false;
    deviceConnected = false;
    Serial.println("onDisconnect");
  }
};
// Function to chech Characteristic
bool connectCharacteristic(BLERemoteService* pRemoteService, BLERemoteCharacteristic* l_BLERemoteChar) {
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  if (l_BLERemoteChar == nullptr) {
    Serial.print("Failed to find one of the characteristics");
    Serial.print(l_BLERemoteChar->getUUID().toString().c_str());
    return false;
  }
  Serial.println(" - Found characteristic: " + String(l_BLERemoteChar->getUUID().toString().c_str()));

  return true;
}
bool connectToServer() {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());

  BLEClient *pClient = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");
  pClient->setMTU(517);  //set client to request maximum MTU from server (default is 23 otherwise)

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService *pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  connected = true;
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  pRemoteCharX = pRemoteService->getCharacteristic(xAxesUUID);
  pRemoteCharY = pRemoteService->getCharacteristic(yAxesUUID);
  pRemoteCharBtn = pRemoteService->getCharacteristic(btnUUID);

  if(connectCharacteristic(pRemoteService,pRemoteCharX) == false) {
    connected =false;
  }
  else if(connectCharacteristic(pRemoteService,pRemoteCharY) == false){
    connected =false;
  }
  else if(connectCharacteristic(pRemoteService,pRemoteCharBtn) == false) {
    connected =false;
  }
  if(connected == false) {
    pClient->disconnect();
    Serial.print("Failed to find one or more characteristic UUID");
    return false;
  }
  //connected = true;
  return true;
}

/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    }  // Found our server
  }  // onResult
};  // MyAdvertisedDeviceCallbacks

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

  pinMode(A5,INPUT_PULLUP);
  pinMode(A4,INPUT);
  pinMode(A3,INPUT);

  FastLED.addLeds<WS2812,LED_PIN>(leds,NUM_LEDS);
  FastLED.setBrightness(5);//0-255
  
}  // End of setup.

// This is the Arduino main loop function.
void loop() {
  
  xVal = analogRead(A4);
  yVal = analogRead(A3);
  bttState = digitalRead(A5);
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothing more we will do.");
    }
    doConnect = false;
  }


  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    /*String newValue = "Time since boot: " + String(millis() / 1000);
    Serial.println("Setting new characteristic value to \"" + newValue + "\"");*/

    // Set the characteristic's value to be the array of bytes that is actually a string.
    pRemoteCharX->writeValue(String(xVal), String(xVal).length());
    Serial.print("X: ");
    Serial.print(xVal);
    
    pRemoteCharY->writeValue(String(yVal), String(yVal).length());
    Serial.print(" | Y: ");
    Serial.print(yVal);

    pRemoteCharBtn->writeValue(String(bttState), String(bttState).length());
    Serial.print(" | Switch: ");
    Serial.print(bttState);
    Serial.println(" | ceva merge 1 ");
  } else if (doScan) {
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }
  if (deviceConnected) {
    leds[0] = CRGB::Blue;  // LED albastru dacă suntem conectați
  } 
  if (!deviceConnected && oldDeviceConnected) {
    leds[0] = CRGB::Green;//red?
  }
  FastLED.show();
  Serial.println("D-a ajuns: ");
  //delay(1000);  // Delay a second between loops.
  if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}  // End of loop
