#include <iostream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define BAUD_RATE 115200

#define LED_RGB_R 27
#define LED_RGB_G 26
#define LED_RGB_B 25
#define ONBOARD_LED 2

#define BUZZER 33

#define R_WHEELS_AHEAD 22
#define R_WHEELS_BACK 23
#define R_WHEELS_SPEED 32

#define L_WHEELS_AHEAD 18
#define L_WHEELS_BACK 19
#define L_WHEELS_SPEED 21

#define X_DEDZONE 2270
#define Y_DEADZONE 2300
#define X_DEDZONE_MIN 2240
#define X_DEDZONE_MAX 2300
#define Y_DEADZONE_MIN 2270
#define Y_DEADZONE_MAX 2320
#define AXIS_MIN 0
#define AXIS_MAX 4100
#define MIN_SPEED 0
#define MAX_SPEED 0

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "9765cce2-6fba-4643-9c3d-4665a29545c3"
#define CHARACTERISTIC_X_UUID "02732da3-bf6d-43e1-a0bc-a61e69c299b9"
#define CHARACTERISTIC_Y_UUID "4954805c-f7bd-4a95-a0ec-0e2a11453c36"
#define CHARACTERISTIC_BTN_UUID "c03ea1d4-4c2f-469f-be40-df90304f00c1"

bool deviceConnected = false;
bool oldDeviceConnected = false;

// init pointers
BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristicX = NULL;
BLECharacteristic *pCharacteristicY = NULL;
BLECharacteristic *pCharacteristicBtn = NULL;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void ledRgbSet(bool red, bool green, bool blue) {
  digitalWrite(LED_RGB_R, red);
  digitalWrite(LED_RGB_G, green);
  digitalWrite(LED_RGB_B, blue);
}
void hornActivate(int btnPresst) {
  if (!btnPresst) {
    analogWrite(BUZZER, 64);
    //tone(BUZZER,1000);
  } else {
    analogWrite(BUZZER, 0);
    //noTone();
  }
}

void wheelControl(int inpXaxes, int inpYaxes) {
   int speedRight = 0;
  int speedLeft = 0;

  // Forward (UP)
  if (inpXaxes <= X_DEDZONE_MIN) {
    int speed = map(inpXaxes, X_DEDZONE_MIN, AXIS_MIN, MIN_SPEED, MAX_SPEED);
    speedRight = speed;
    speedLeft = speed;

    // Adjust for turning
    if (inpYaxes <= Y_DEADZONE_MIN) { // Turning Right
      int turnFactor = map(inpYaxes, Y_DEADZONE_MIN, AXIS_MIN, MIN_SPEED, MAX_SPEED);
      speedLeft = speed;       // Left wheel full speed
      speedRight = speed - turnFactor; // Reduce right wheel speed
    } 
    else if (inpYaxes >= Y_DEADZONE_MAX) { // Turning Left
      int turnFactor = map(inpYaxes, Y_DEADZONE_MAX, AXIS_MAX, MIN_SPEED, MAX_SPEED);
      speedRight = speed;       // Right wheel full speed
      speedLeft = speed - turnFactor; // Reduce left wheel speed
    }
  }

  // Backward (DOWN)
  if (inpXaxes >= X_DEDZONE_MAX) {
    int speed = map(inpXaxes, X_DEDZONE_MAX, AXIS_MAX, MIN_SPEED, MAX_SPEED);
    speedRight = -speed;
    speedLeft = -speed;

    // Adjust for turning
    if (inpYaxes < Y_DEADZONE_MIN) { // Turning Right
      int turnFactor = map(inpYaxes, Y_DEADZONE_MIN, AXIS_MIN, MIN_SPEED, MAX_SPEED);
      speedLeft = -speed;       // Left wheel full speed
      speedRight = -(speed - turnFactor); // Reduce right wheel speed
    } 
    else if (inpYaxes > Y_DEADZONE_MAX) { // Turning Left
      int turnFactor = map(inpYaxes, Y_DEADZONE_MAX, AXIS_MAX, MIN_SPEED, MAX_SPEED);
      speedRight = -speed;       // Right wheel full speed
      speedLeft = -(speed - turnFactor); // Reduce left wheel speed
    }
  }

  // Apply speed to wheels
  if (speedRight >= 0) {
    digitalWrite(R_WHEELS_AHEAD, 1);
    digitalWrite(R_WHEELS_BACK, 0);
    analogWrite(R_WHEELS_SPEED, speedRight);
  } 
  else {
    digitalWrite(R_WHEELS_AHEAD, 0);
    digitalWrite(R_WHEELS_BACK, 1);
    analogWrite(R_WHEELS_SPEED, -speedRight);
  }

  if (speedLeft >= 0) {
    digitalWrite(L_WHEELS_AHEAD, 1);
    digitalWrite(L_WHEELS_BACK, 0);
    analogWrite(L_WHEELS_SPEED, speedLeft);
  } 
  else {
    digitalWrite(L_WHEELS_AHEAD, 0);
    digitalWrite(L_WHEELS_BACK, 1);
    analogWrite(L_WHEELS_SPEED, -speedLeft);
  }
  //Turning Left on place
  if (inpXaxes > X_DEDZONE_MIN && inpXaxes < X_DEDZONE_MAX &&  inpYaxes <= Y_DEADZONE_MIN) {
    digitalWrite(R_WHEELS_AHEAD, 1);
    digitalWrite(R_WHEELS_BACK, 0);
    analogWrite(R_WHEELS_SPEED, map(inpYaxes, Y_DEADZONE_MIN, AXIS_MIN, MIN_SPEED, MAX_SPEED));
    digitalWrite(L_WHEELS_AHEAD, 0);
    digitalWrite(L_WHEELS_BACK, 1);
    analogWrite(L_WHEELS_SPEED, map(inpYaxes, Y_DEADZONE_MIN, AXIS_MIN, MIN_SPEED, MAX_SPEED));
  }
  // Turning Right on plce
  if (inpXaxes > X_DEDZONE_MIN && inpXaxes < X_DEDZONE_MAX && inpYaxes >= Y_DEADZONE_MAX) {
    digitalWrite(R_WHEELS_AHEAD, 0);
    digitalWrite(R_WHEELS_BACK, 1);
    analogWrite(R_WHEELS_SPEED, map(inpYaxes, Y_DEADZONE_MAX, AXIS_MAX, MIN_SPEED, MAX_SPEED));
    digitalWrite(L_WHEELS_AHEAD, 1);
    digitalWrite(L_WHEELS_BACK, 0);
    analogWrite(L_WHEELS_SPEED, map(inpYaxes, Y_DEADZONE_MAX, AXIS_MAX, MIN_SPEED0, MAX_SPEED));
  }
  // Deadzone
  if (inpXaxes > X_DEDZONE_MIN && inpXaxes < X_DEDZONE_MAX && inpYaxes > Y_DEADZONE_MIN && inpYaxes < Y_DEADZONE_MAX) {
    digitalWrite(R_WHEELS_AHEAD, 0);
    digitalWrite(R_WHEELS_BACK, 0);
    analogWrite(R_WHEELS_SPEED, MIN_SPEED);
    digitalWrite(L_WHEELS_AHEAD, 0);
    digitalWrite(L_WHEELS_BACK, 0);
    analogWrite(L_WHEELS_SPEED, MIN_SPEED);
  }
}
void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("Starting BLE work!");

  BLEDevice::init("CFSebastianCar");
  // create server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // create service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // create characteristics
  pCharacteristicX =pService->createCharacteristic(
                    CHARACTERISTIC_X_UUID,
                    BLECharacteristic::PROPERTY_READ |
                    BLECharacteristic::PROPERTY_WRITE
                    );
  pCharacteristicY =pService->createCharacteristic(
                    CHARACTERISTIC_Y_UUID,
                    BLECharacteristic::PROPERTY_READ |
                    BLECharacteristic::PROPERTY_WRITE
                    );
  pCharacteristicBtn =pService->createCharacteristic(
                    CHARACTERISTIC_BTN_UUID,
                    BLECharacteristic::PROPERTY_READ |
                    BLECharacteristic::PROPERTY_WRITE
                    );

  //pCharacteristic->setValue("Hello World says Neil");
  // Start service
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

  

  pinMode(LED_RGB_R, OUTPUT);
  pinMode(LED_RGB_G, OUTPUT);
  pinMode(LED_RGB_B, OUTPUT);
  digitalWrite(LED_RGB_R, 0);
  digitalWrite(LED_RGB_G, 0);
  digitalWrite(LED_RGB_B, 1);

  pinMode(BUZZER, OUTPUT);

  pinMode(R_WHEELS_AHEAD, OUTPUT);
  pinMode(R_WHEELS_BACK, OUTPUT);
  pinMode(R_WHEELS_SPEED, OUTPUT);
  pinMode(L_WHEELS_AHEAD, OUTPUT);
  pinMode(L_WHEELS_BACK, OUTPUT);
  pinMode(L_WHEELS_SPEED, OUTPUT);

  ledRgbSet(0,1,0);
}

void loop() {
  // put your main code here, to run repeatedly:
   // notify changed value
  int inpXaxes = X_DEDZONE;
  int inpYaxes = Y_DEADZONE;
  int inpBtn = true;
  if (deviceConnected) {
    ledRgbSet(0,0,1);
    String xAxes = pCharacteristicX->getValue();
    inpXaxes = xAxes.toInt();
    Serial.print("X: ");
    Serial.print(inpXaxes);
    
    String yAxes = pCharacteristicY->getValue();
    inpYaxes = yAxes.toInt();
    Serial.print(" | Y: ");
    Serial.print(inpYaxes);
    
    String btn = pCharacteristicBtn->getValue();
    inpBtn = btn.toInt();
    Serial.print(" | Switch: ");
    Serial.print(inpBtn);
    
    Serial.println(" | ceva merge 1 ");

    hornActivate(inpBtn);
    wheelControl(inpXaxes,inpYaxes);

  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
    ledRgbSet(0,1,0);
    delay(500); // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
      // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
  }
 
}