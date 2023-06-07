#pragma once

#include <string>
#include <Wire.h>

#include "SparkFun_BNO080_Arduino_Library.h"

namespace Sensors {

BNO080 myIMU;

void setup() {
    Wire.begin();

    if (myIMU.begin() == false) {
        std::string error = "BNO080 not detected at default I2C address. Check your jumpers. Freezing...";
        while (true) {
            Serial.println(error.c_str());
            delay(5000);
        }
    }
    Wire.setClock(400000);  // Increase I2C data rate to 400kHz

    myIMU.enableRotationVector(50); //Send data update every 50ms
    myIMU.enableGyro(50);
}

void loop() {
    if (myIMU.dataAvailable() == false) {
        Serial.println("No data available");
    }
}

float getTheta() {
    if (myIMU.dataAvailable() == false) {
        Serial.println("No data available");
    }
    float yaw = myIMU.getYaw();
    float pitch = myIMU.getPitch();
    constexpr float offset = M_PI / 2;
    pitch += offset;
    pitch *= (yaw > 0 ? -1 : 1);
    return pitch;
}

float getThetaDot() {
    return myIMU.getGyroY();
}

}  // namespace Sensors
