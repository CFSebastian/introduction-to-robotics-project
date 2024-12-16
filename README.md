# Car and Controller Using ESP32
## Introduction
  
## General Description
  ![plot](./Media/SchemaBlock.drawio%20(1).png)
## Hardware Design
  ### Componente fizice utilizate
  Controller:  
    - ESP32-C3 SuperMini - is the board for the controller, chosen for its small profile,   it reads the input and sends them wireless to the car 
    - Joystick module - generates the input data based on the operators actions
    - WS2812 - indicates the state of the board on the controller
    - 1x 330 ohm resistance
    - Small Breadboard - facilitates the easy wireing of the components
  Car:  
  - ESP32 Devkit V1 - is the board for the car, it receives the input from the controller   and instructs the actuators on what to do
  - RGB LED - indicates the state of the board on the car
  - Breadboard - facilitates the easy wiring of the components
  - 4x Small DC Motor - the primary actuators that move the car
  - L293D - the H bridge drive that helps the board on the car control the motors and protects it from high current
  - Passive Buzzer - represents the horn 
  - 2x 4 Battery Pack - power source for the car
  - 4x 330 ohm resistance
  Common:  
  - wires - facilitate the connectivity between the components

  ### Electronic schematics
   ![plot](./Media/DiagramaMasina.PNG)
   ![plot](./Media/SchemaTelecomanda.PNG)
## Software Design
  ### Development environment
  IDE: PlatformIO
  #### ESP32-C3 SuperMini environment:
    TO DO
  #### ESP32 Devkit V1 environment:
    TO DO
## Results Obtained
  
## Conclusions
  
## Bibliography/Resources
  ### Hardware
  ESP32-C3 SuperMini:  
  https://dl.artronshop.co.th/ESP32-C3%20SuperMini%20datasheet.pdf  
  https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf  
  ESP32 Devkit V1:  
  https://lastminuteengineers.com/esp32-pinout-reference/  
  https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf  
  WS2812:  
  https://cdn-shop.adafruit.com/datasheets/WS2812.pdf  
  https://lastminuteengineers.com/esp32-wled-tutorial/  
  L293D:  
  https://lastminuteengineers.com/l293d-dc-motor-arduino-tutorial/  
  https://www.ti.com/lit/ds/symlink/l293.pdf  
  Passive Buzzer:
  https://deepbluembedded.com/active-buzzer-vs-passive-buzzer/
    
  ### Software 
  IDE:  
  https://platformio.org/
