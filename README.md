# Car and Controller Using ESP32

## Introduction

My project is a wirelessly controlled car operated via a custom-built controller. The system enables the operator to move the car forward, backward, steer, and honk.  

### What Does the Project Do?  
The car and controller communicate wirelessly, allowing essential functions such as directional movement, steering, and honking.  

### What Was the Initial Idea?  
The project was inspired by the goal of learning how to control a motorized object wirelessly, laying a foundation for future projects   
like an electric bike or skateboard. To keep it achievable within time constraints, the design was kept simple and focused.  

### Why Is It Useful?  
This project serves as a practical example of wireless control systems, offering learning opportunities for students and hobbyists.   
It bridges theory and real-world application while fostering skills in robotics and transportation technologies.  
For us, it has been a stepping stone toward more advanced projects and a valuable hands-on experience.

## General Description

![plot](./Media/Copie%20pentru%20SchemaBlock.drawio.png)

## Hardware Design

### Physical Components

#### Controller:
- **ESP32-C3 SuperMini**: The microcontroller board for the controller, chosen for its small profile. It reads the input and sends it wirelessly to the car.
- **Joystick module**: Generates input data based on the operator's actions.
- **WS2812 LED**: Indicates the state of the controller board.
- **1x 330-ohm resistor**: Used for current limiting.
- **Small Breadboard**: Facilitates the easy wiring of the components.

#### Car:
- **ESP32 Devkit V1**: The microcontroller board for the car. It receives input from the controller and instructs the actuators on what to do.
- **RGB LED**: Indicates the state of the car board.
- **Breadboard**: Facilitates the easy wiring of the components.
- **4x Small DC Motors**: The primary actuators that move the car.
- **L293D**: The H-bridge driver that helps the car board control the motors and protects it from high currents.
- **Passive Buzzer**: Represents the horn.
- **2x 4-Battery Pack**: Power source for the car.
- **3x 330-ohm resistors**: Used for current limiting.


### Electronic Schematics

#### Car:
![plot](./Media/DiagramaMasina.PNG)

#### Controller:
![plot](./Media/SchemaTelecomanda.PNG)

## Software Design

### Development Environment

**IDE**: Arduino IDE

#### ESP32-C3 SuperMini Environment:
TO DO

#### ESP32 Devkit V1 Environment:
TO DO

## Results Obtained

TO DO

## Conclusions

TO DO

## Bibliography/Resources

### Hardware

**ESP32-C3 SuperMini**:  
- [ESP32-C3 SuperMini Datasheet](https://dl.artronshop.co.th/ESP32-C3%20SuperMini%20datasheet.pdf)  
- [ESP32-C3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)  

**ESP32 Devkit V1**:  
- [ESP32 Pinout Reference](https://lastminuteengineers.com/esp32-pinout-reference/)  
- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)  

**WS2812 LED**:  
- [WS2812 Datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812.pdf)  
- [ESP32 WS2812 Tutorial](https://lastminuteengineers.com/esp32-wled-tutorial/)  

**L293D H-Bridge Driver**:  
- [L293D Motor Driver Tutorial](https://lastminuteengineers.com/l293d-dc-motor-arduino-tutorial/)  
- [L293 Datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf)  

**Passive Buzzer**:  
- [Passive Active Buzzer](https://deepbluembedded.com/arduino-active-passive-buzzer/)  

### Software

**IDE**:  
- [Arduino IDE](https://www.arduino.cc/en/software)
**Bluetooth Low Energy(BLE)**:  
- [BLE materials+code](https://dronebotworkshop.com/esp32-bluetooth/)
- [BLE materials+code](https://github.com/mo-thunderz)
- [BLE libraries](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE)



