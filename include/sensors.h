#pragma once

#define IMU_UPDATE_INTERVAL 20

#ifndef NDEBUG
    #define DBG 1

#else
    #define DBG 0
#endif

#include "SparkFun_BNO080_Arduino_Library.h"
    
namespace Sensors {


class IMU {
public:
    IMU();
    bool setup();
    void loop();
    void logMeasurements();
    float getTheta();
    float getThetaDot();
    float getPsi();
    float getPsiDot();
private:
    bool verifyConnection();
    BNO080 myIMU;
    float theta, thetaDot, psi, psiDot;
};

extern IMU imu;

// bool setup();
// void loop();

// void logMeasurements();

// float getTheta();
// float getThetaDot();
// float getPsi();
// float getPsiDot();

}  // namespace Sensors
