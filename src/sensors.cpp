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
    Log.infoln("Verifying connection to BNO080");
    Log.infoln("Waiting for data available");
    while (myIMU.dataAvailable() == false);

    float theta, thetaDot, psi, psiDot;
    Log.infoln("Waiting for valid data");
    Log.traceln("waiting for valid theta");
    do {
        theta = getTheta();
        delay(IMU_UPDATE_INTERVAL);
    } while (theta < -M_PI/2 || theta > M_PI / 2);
    
    Log.traceln("waiting for valid thetaDot");
    do {
        thetaDot = getThetaDot();
        delay(IMU_UPDATE_INTERVAL);
    } while (abs(thetaDot) < 0.001);

    Log.traceln("waiting for valid psi");
    do {
        psi = getPsi();
        delay(IMU_UPDATE_INTERVAL);
    } while (psi < -M_PI || psi > M_PI);

    Log.traceln("waiting for valid psiDot");
    do {
        psiDot = getPsiDot();
        delay(IMU_UPDATE_INTERVAL);
    } while (abs(psiDot) < 0.001);
    Log.infoln("Connection to BNO080 is ok");
    return false;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions and variables
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool IMU::setup() {
    Wire.begin();

    if (myIMU.begin() == false) {
        std::string error = "BNO080 not detected at default I2C address. Check your jumpers. Freezing...";
        Log.errorln(error.c_str());
        return true;
    }
    Wire.setClock(400000);  // Increase I2C data rate to 400kHz

    myIMU.enableRotationVector(50); //Send data update every 50ms
    myIMU.enableGyro(50);
    // verifyConnection();
    return false;
}

void IMU::loop() {
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
    }
}

void IMU::logMeasurements() {
//     if (myIMU.dataAvailable() == true)
//   {
    // float quatI = myIMU.getQuatI();
    // float quatJ = myIMU.getQuatJ();
    // float quatK = myIMU.getQuatK();
    // float quatReal = myIMU.getQuatReal();
    // float quatRadianAccuracy = myIMU.getQuatRadianAccuracy();

    // Serial.print(quatI, 2);
    // Serial.print(F(","));
    // Serial.print(quatJ, 2);
    // Serial.print(F(","));
    // Serial.print(quatK, 2);
    // Serial.print(F(","));
    // Serial.print(quatReal, 2);
    // Serial.print(F(","));
    // Serial.print(quatRadianAccuracy, 2);
    // Serial.print(F(","));

    // Serial.println();
    char buf[100];
    sprintf(buf, "Theta: %.2f, ThetaDot: %.2f, Psi: %.2f, PsiDot: %.2f\n", getTheta(), getThetaDot(), getPsi(), getPsiDot());
    Log.info(buf);
//   }
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions and variables
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


// BNO080 myIMU;

// bool verifyConnection() {
//     Log.infoln("Verifying connection to BNO080");
//     Log.infoln("Waiting for data available");
//     while (myIMU.dataAvailable() == false);

//     float theta, thetaDot, psi, psiDot;
//     Log.infoln("Waiting for valid data");
//     Log.traceln("waiting for valid theta");
//     do {
//         theta = getTheta();
//         delay(IMU_UPDATE_INTERVAL);
//     } while (theta < -M_PI/2 || theta > M_PI / 2);
    
//     Log.traceln("waiting for valid thetaDot");
//     do {
//         thetaDot = getThetaDot();
//         delay(IMU_UPDATE_INTERVAL);
//     } while (abs(thetaDot) < 0.001);

//     Log.traceln("waiting for valid psi");
//     do {
//         psi = getPsi();
//         delay(IMU_UPDATE_INTERVAL);
//     } while (psi < -M_PI || psi > M_PI);

//     Log.traceln("waiting for valid psiDot");
//     do {
//         psiDot = getPsiDot();
//         delay(IMU_UPDATE_INTERVAL);
//     } while (abs(psiDot) < 0.001);
//     Log.infoln("Connection to BNO080 is ok");
//     return false;
// }


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Public Functions and variables
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////


// bool setup() {
//     Wire.begin();

//     if (myIMU.begin() == false) {
//         std::string error = "BNO080 not detected at default I2C address. Check your jumpers. Freezing...";
//         Log.errorln(error.c_str());
//         return true;
//     }
//     Wire.setClock(400000);  // Increase I2C data rate to 400kHz

//     myIMU.enableRotationVector(50); //Send data update every 50ms
//     myIMU.enableGyro(50);
//     // verifyConnection();
//     return false;
// }

// void loop() {
//     // if (myIMU.dataAvailable() == false) {
//     //     Log.warningln("No data available from IMU");
//     // }
// }

// void logMeasurements() {
//     if (myIMU.dataAvailable() == true)
//   {
//     // float quatI = myIMU.getQuatI();
//     // float quatJ = myIMU.getQuatJ();
//     // float quatK = myIMU.getQuatK();
//     // float quatReal = myIMU.getQuatReal();
//     // float quatRadianAccuracy = myIMU.getQuatRadianAccuracy();

//     // Serial.print(quatI, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatJ, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatK, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatReal, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatRadianAccuracy, 2);
//     // Serial.print(F(","));

//     // Serial.println();
//     char buf[100];
//     sprintf(buf, "Theta: %.2f, ThetaDot: %.2f, Psi: %.2f, PsiDot: %.2f\n", getTheta(), getThetaDot(), getPsi(), getPsiDot());
//     Log.info(buf);
//   }
// }

// float getTheta() {
//     float yaw = myIMU.getYaw();
//     float pitch = myIMU.getPitch();
//     constexpr float offset = M_PI / 2;
//     pitch += offset;
//     pitch *= (yaw > 0 ? -1 : 1);
//     return pitch;
// }

// float getThetaDot() {
//     return myIMU.getGyroY();
// }

// float getPsi() {
//     return myIMU.getYaw();
// }
// float getPsiDot() {
//     return myIMU.getGyroX();
// }



}  // namespace Sensors