#include <Arduino.h>
#include <sensors.h>

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing...");
    Sensors::setup();
}

void loop() {
    // Serial.println("Hello World!");
    Sensors::loop();
    double theta = Sensors::getTheta();
    double thetaDot = Sensors::getThetaDot();
    Serial.printf("theta: %f, thetaDot: %f\n", theta, thetaDot);
    delay(50);
}
