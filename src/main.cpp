#include <Arduino.h>
#include <logger.h>
#include <sensors.h>

void setup() {
    Logger::setup();
    Sensors::imu.setup();
}

void loop() {
    Sensors::imu.loop();
    static uint32_t prevPrint = millis();
    if (millis() > prevPrint + 50) {
        Sensors::imu.logMeasurements();
        prevPrint = millis();
    }
}