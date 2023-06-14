#include <Arduino.h>
#include <logger.h>
#include <sensors.h>
#include <Balancer.h>

void setup() {
    bool error = false;
    error |= Logger::setup();
    Log.infoln("Starting up");
    error |= Sensors::imu.setup();
    if (error) {
        Log.errorln("Setup failed. Rebooting...");
        _reboot_Teensyduino_();
        while (true);
    }
    Log.infoln("Setup complete");
}

void loop() {
    Sensors::imu.loop();
    static uint32_t prevPrint = millis();
    if (millis() > prevPrint + 100) {
        Sensors::imu.logMeasurements();
        prevPrint = millis();
    }
    balancer.update();
}