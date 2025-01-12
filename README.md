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

### Bill Of Materials

#### Controller:
| Name |  Image | Number | Links |
| ----------- | ----------- |----------- | ----------- |
| ESP32-C3 SuperMini | <img src="./Media/makergo-esp32c3-supermini.jpg" alt="drawing" width="200"/> | 1 | [Shop](https://shorturl.at/NS3Yj)<br />[Board Datasheet](https://dl.artronshop.co.th/ESP32-C3%20SuperMini%20datasheet.pdf)<br /> [Chip Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)   |
| Joystick module | <img src="./Media/dual-axis-joystick-module-with-button-1-255x191.jpg" alt="drawing" width="200"/> | 1 | Links |
| WS2812 LED | <img src="./Media/SKU-44120.png" alt="drawing" width="200"/> | 1 | [Datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812.pdf)  |
| 330-ohm resistor | <img src="./Media/resistor.jpg" alt="drawing" width="200"/> | 1 | Links |
| Small Breadboard | <img src="./Media/SmallBreadboard.jpg" alt="drawing" width="200"/> | 1 | Links |

#### Car:
| Name | Image | Number | Links |
| ----------- | ----------- |----------- | ----------- |
| ESP32 Devkit V1 | <img src="./Media/esp32-dev-kit-v1.jpg" alt="drawing" width="200"/> | 1 | [Chip Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)<br >[Pinout Reference](https://lastminuteengineers.com/esp32-pinout-reference/)    |
| RGB LED | <img src="./Media/rgb-light-emitting-diode.jpg" alt="drawing" width="200"/> | 1 | Links |
| Breadboard | <img src="./Media/Breadboard.jpg" alt="drawing" width="200"/> | 2 | Links |
| Small DC Motors | <img src="./Media/MOTOR.jpg" alt="drawing" width="200"/> | 4 | Links |
| L293D | <img src="./Media/L293D.jpg" alt="drawing" width="200"/> | 1 | [Datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf) |
| Passive Buzzer | <img src="./Media/buzzer.jpg" alt="drawing" width="200"/> | 1 | Links |
| 330-ohm resistor | <img src="./Media/resistor.jpg" alt="drawing" width="200"/> | 3 | Links |
| 4-Battery holder | <img src="./Media/batteryHolder.jpg" alt="drawing" width="200"/> | 1 | Links |
| 9v battery clip | <img src="./Media/9vClip.jpg" alt="drawing" width="200"/> | 1 | Links |

### Electronic Schematics

#### Car:
![plot](./Media/Car.PNG)

#### Controller:
![plot](./Media/Controller.PNG)

## Software Design
At this point in the project( milestone 3), the car and controler can comunicate via Bluetooth Low Energy, the car is moving, all be it not great thaks to the power consuption and primary because the model of the chassis does not allow all  the wheels make contact with the ground, the horn and leds work fine and indicates when it is conected and not.  
Over all the project does the basics that it suposed to do and all it remains is minor fixes.   
### Development Environment

**IDE**: Arduino IDE

### Librariest:
**Bluetooth Low Energy(BLE)**-ESP32 BLE for Arduino  
**LEDstrips (SWS2812 LED)**-FastLED

### Video:
[![Demonstration Video](http://img.youtube.com/vi/ZfmHpDFt6Ck/0.jpg)](https://www.youtube.com/watch?v=ZfmHpDFt6Ck "Demonstration Video")  

### Calibrations
I calibrated the joystick with the serial monitor, observing where the dead zone is for the x and y axes, and their max and min values.  
I noted them on a paper and the created defines for the joystick taking into acount some tolerances.
[![Joystick calibration](http://img.youtube.com/vi/ZaIzt3UZlsc/0.jpg)](https://www.youtube.com/watch?v=ZaIzt3UZlsc "Joystick calibration")

## Conclusions

TO DO

## Bibliography/Resources

### Hardware

**3D Modeling**:  
- [Onshape](https://www.onshape.com/en/)

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
- [BLE materials+examples](https://dronebotworkshop.com/esp32-bluetooth/)
- [BLE materials+examples](https://github.com/mo-thunderz)
- [BLE libraries](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE)

**FastLED**:
- [materials+examples](https://racheldebarros.com/arduino-projects/how-to-use-fastled-with-arduino-to-program-led-strips/)
- [examples](https://github.com/FastLED/FastLED?utm_source=platformio&utm_medium=piohome)


