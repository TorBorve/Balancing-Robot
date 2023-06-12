#include "sensors.h"

#include <string>
#include <cmath>
#include <Wire.h>



#include "logger.h"

namespace Sensors {

IMU imu{};

IMU::IMU() {
}


bool IMU::verifyConnection() {
    uint32_t startTime = millis();
    Log.infoln("Verifying connection to BNO080");

    Log.infoln("Waiting for valid data");
    bool success = false;
    while(success == false) {
        success = true;
        if (loop()) {
            float theta = getTheta();
            float thetaDot = getThetaDot();
            float psi = getPsi();
            float psiDot = getPsiDot();
            success &= (theta > -M_PI/2 && theta < M_PI / 2);
            success &= (std::fabs(thetaDot) > 0.001);
            success &= (psi > -M_PI && psi < M_PI);
            success &= (std::fabs(psiDot) > 0.001);
        
        } else {
            success = false;
        }
        if (millis() > startTime + 5000) {
            Log.errorln("Timed out waiting for valid data");
            return true;
        }
    }
    return false;
}

bool IMU::setup() {
    Wire.begin();

    if (myIMU.begin() == false) {
        std::string error = "BNO080 not detected at default I2C address. Check your jumpers. Freezing...";
        Log.errorln(error.c_str());
        return true;
    }
    Wire.setClock(400000);  // Increase I2C data rate to 400kHz

    myIMU.enableRotationVector(IMU_UPDATE_INTERVAL); //Send data update every 50ms
    myIMU.enableGyro(IMU_UPDATE_INTERVAL);
    return verifyConnection();
}

bool IMU::loop() {
    if (myIMU.dataAvailable() == true) {
        float yaw = myIMU.getYaw();
        float pitch = myIMU.getPitch();
        constexpr float offset = M_PI / 2;
        pitch += offset;
        pitch *= (yaw > 0 ? -1 : 1);

        theta = pitch;
        thetaDot = myIMU.getGyroY();
        psi = yaw;
        psiDot = myIMU.getGyroX();
        return true;
    }
    return false;
}

void IMU::logMeasurements() {
    char buf[100];
    sprintf(buf, "Theta: %.2f, ThetaDot: %.2f, Psi: %.2f, PsiDot: %.2f\n", getTheta(), getThetaDot(), getPsi(), getPsiDot());
    Log.info(buf);
}

float IMU::getTheta() {
    return theta;
}

float IMU::getThetaDot() {
    return thetaDot;
}

float IMU::getPsi() {
    return psi;
}

float IMU::getPsiDot() {
    return psiDot;
}



}  // namespace Sensors