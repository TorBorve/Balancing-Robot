// #include <Wire.h>

// #include "SparkFun_BNO080_Arduino_Library.h"  // Click here to get the library: http://librarymanager/All#SparkFun_BNO080
// BNO080 myIMU;

// // Given a accuracy number, print what it means
// void printAccuracyLevel(byte accuracyNumber) {
//     if (accuracyNumber == 0)
//         Serial.print(F("Unreliable"));
//     else if (accuracyNumber == 1)
//         Serial.print(F("Low"));
//     else if (accuracyNumber == 2)
//         Serial.print(F("Medium"));
//     else if (accuracyNumber == 3)
//         Serial.print(F("High"));
// }

// void setup() {
//     Serial.begin(115200);
//     Serial.println();
//     Serial.println("BNO080 Read Example");

//     Wire.begin();

//     myIMU.begin();

//     Wire.setClock(400000);  // Increase I2C data rate to 400kHz

//     // Enable dynamic calibration for accel, gyro, and mag
//     myIMU.calibrateAll();  // Turn on cal for Accel, Gyro, and Mag

//     // Enable Game Rotation Vector output
//     myIMU.enableGameRotationVector(100);  // Send data update every 100ms

//     // Enable Magnetic Field output
//     myIMU.enableMagnetometer(100);  // Send data update every 100ms

//     // Once magnetic field is 2 or 3, run the Save DCD Now command
//     Serial.println(F("Calibrating. Press 's' to save to flash"));
//     Serial.println(F("Output in form x, y, z, in uTesla"));
// }

// void loop() {
//     if (Serial.available()) {
//         byte incoming = Serial.read();

//         if (incoming == 's') {
//             Serial.println(F("Saving calibration to flash"));
//             myIMU.saveCalibration();           // Saves the current dynamic calibration data (DCD) to memory
//             myIMU.requestCalibrationStatus();  // Sends command to get the latest calibration status

//             // Wait for calibration response, timeout if no response
//             int counter = 100;
//             while (1) {
//                 if (--counter == 0) break;
//                 if (myIMU.dataAvailable() == true) {
//                     // The IMU can report many different things. We must wait
//                     // for the ME Calibration Response Status byte to go to zero
//                     if (myIMU.calibrationComplete() == true) {
//                         Serial.println("Calibration data successfully stored");
//                         delay(1000);
//                         break;
//                     }
//                 }

//                 delay(1);
//             }
//             if (counter == 0) {
//                 Serial.println("Calibration data failed to store. Please try again.");
//             }

//             // myIMU.endCalibration(); //Turns off all calibration
//             // In general, calibration should be left on at all times. The BNO080
//             // auto-calibrates and auto-records cal data roughly every 5 minutes
//         }
//     }

//     // Look for reports from the IMU
//     if (myIMU.dataAvailable() == true) {
//         float x = myIMU.getMagX();
//         float y = myIMU.getMagY();
//         float z = myIMU.getMagZ();
//         byte accuracy = myIMU.getMagAccuracy();

//         float quatI = myIMU.getQuatI();
//         float quatJ = myIMU.getQuatJ();
//         float quatK = myIMU.getQuatK();
//         float quatReal = myIMU.getQuatReal();
//         byte sensorAccuracy = myIMU.getQuatAccuracy();

//         Serial.print(x, 2);
//         Serial.print(F(","));
//         Serial.print(y, 2);
//         Serial.print(F(","));
//         Serial.print(z, 2);
//         Serial.print(F(","));
//         printAccuracyLevel(accuracy);
//         Serial.print(F(","));

//         Serial.print("\t");

//         Serial.print(quatI, 2);
//         Serial.print(F(","));
//         Serial.print(quatJ, 2);
//         Serial.print(F(","));
//         Serial.print(quatK, 2);
//         Serial.print(F(","));
//         Serial.print(quatReal, 2);
//         Serial.print(F(","));
//         printAccuracyLevel(sensorAccuracy);
//         Serial.print(F(","));

//         Serial.println();
//     }
// }

#include <Arduino.h>
#include <logger.h>
#include <Motors.h>
#include <sensors.h>
// #include <Balancer.h>
#include <HumanInterface.h>

#define LF 7
#define LB 8
#define RF 9
#define RB 10

Motors motors(LF, LB, RF, RB);

#define CONTROL_LOOP_INTERVAL 5

double controller(double theta, double thetaDot) {
    static double thetaIntegral = 0.0;
    static double uIntegral = 6.0;
    constexpr double KiU = 0.0;
    constexpr double Kp = 6.0;
    constexpr double Ki = 0;
    constexpr double Kd = 0.05;
    constexpr double thetaRef = -0.03;

    if (fabs(theta) > 45.0 * M_PI / 180.0) {
        thetaIntegral = 0.0;
        uIntegral = 0.0;
        return 0.0;
    }

    thetaIntegral += (theta - thetaRef) * (CONTROL_LOOP_INTERVAL / 1000.0);
    double u = Kp * (theta - thetaRef) + Ki * thetaIntegral + Kd * thetaDot + KiU * uIntegral;
    uIntegral += u * (CONTROL_LOOP_INTERVAL / 1000.0);
    return u;
}

void setup() {
    bool error = false;
    // error |= Logger::setup();
    Serial.end();
    Log.infoln("Starting up");
    motors.setEnable(true);
    error |= Sensors::imu.setup();
    if (error) {
        Log.errorln("Setup failed. Rebooting...");
        _reboot_Teensyduino_();
        while (true);
    }
    Log.infoln("Setup complete");
}

void loop() {
    // motors.setInputLR(1, 1);
    // humanInterface.update();
    Sensors::imu.loop();
    // static uint32_t prevPrint = millis();
    // if (millis() > prevPrint + 100) {
    //     Sensors::imu.logMeasurements();
    //     prevPrint = millis();
    // }
    static uint32_t prevControl = millis();
    if (millis() > prevControl + CONTROL_LOOP_INTERVAL) {
        prevControl = millis();
        double theta = Sensors::imu.getTheta();
        double thetaDot = Sensors::imu.getThetaDot();
        double u = controller(theta, thetaDot);
        motors.setInputLR(u, u);
        Log.infoln("Theta: %F, ThetaDot: %F, U: %F", theta, thetaDot, u);
        // Serial.printf("theta: %.4f, thetaDot %.4f\n", theta, thetaDot);
    }
    // balancer.update();
}