# **Balancing Robot**
Software for balancing a two wheeled robot

<!-- ## :book: **Table of Contents**
- [:notebook_with_decorative_cover: **Description**](#description)
  * [**ROS interface**](#ROS_interface)
- [:hammer_and_wrench: **Install**](#install)
- [:rocket: **Usage**](#usage)
  * [**Parameters**](#parameters)
  * [**Run**](#run)
- [:link: **References**](#references) -->

<!-- <small><i><a href='http://ecotrust-canada.github.io/markdown-toc/'>Table of contents generated with markdown-toc</a></i></small> -->


## :notebook_with_decorative_cover: **Description** <a name="description"></a>

This repository contains software and hardware descriptions for making a self balancing robot. An IMU is used to measure the angle of the robot. A simple PID control loop is then used to stabilize the robot. The input given by the PID is then conveverted into a pwm voltage signal for some DC motors using a simple motor drive. The chassis of the robot is modelled in fusion 360 and was then 3D printed.

### **Hardware**

List of Hardware needed should be here.

## :hammer_and_wrench: **Install** <a name="install"></a>

To flash the code you will need Teensyduino and Platformio.

1. **Platformio**
  Platformio can be added as an extension in vscode. Search for *platformio.platformio-ide*

2. **TeensyDuino**
    This is needed to flash code to our Teensy microcontroller. Install it by running the followring commands

    ```terminal
    wget https://downloads.arduino.cc/arduino-1.8.15-linux64.tar.xz
    wget https://www.pjrc.com/teensy/td_154/TeensyduinoInstall.linux64
    wget https://www.pjrc.com/teensy/00-teensy.rules
    sudo cp 00-teensy.rules /etc/udev/rules.d/
    tar -xf arduino-1.8.15-linux64.tar.xz
    chmod 755 TeensyduinoInstall.linux64
    ./TeensyduinoInstall.linux64 --dir=arduino-1.8.15
    cd arduino-1.8.15/hardware/teensy/avr/cores/teensy4
    make
    ```

    Keep in mind that there might be newer version available and so on. Please refere to the official [Teensy page](https://www.pjrc.com/teensy/td_download.html) for more information.

 
## :rocket: **Usage** <a name="usage"></a>
 
### **Run** <a name="run"></a>

How to run the code and so on should be writen here...

### **Tuning** <a name="tuning"></a>

There are several parameters that could be tuned to improve the performance. More info should be writen here. 