#include "Balancer.h"

#include <Arduino.h>
#include "sensors.h"
#include "logger.h"

Balancer::Balancer() :
    _angle_control(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
    _control_mode{ControlMode::BALANCE},
    _motors{MOTOR_LEFT_FORWARD_PIN, MOTOR_LEFT_BACKWARD_PIN, MOTOR_RIGHT_FORWARD_PIN, MOTOR_RIGHT_BACKWARD_PIN}
{
    _angle_control.setSampleTime(MAIN_LOOP_INTERVAL);
    _angle_control.setOutputLimits(-2.0, 2.0, -2.0, 2.0);

    _motors.setMaxInputPercent(0.5);
    _motors.setEnable(true);
}

bool Balancer::setup() {
    return false;
}

void Balancer::update() {
    Log.setLevel(LOG_LEVEL_SILENT);
    if (millis() > _last_update_time + MAIN_LOOP_INTERVAL) {
        _last_update_time = millis();
        switch (_control_mode) {
            case ControlMode::STOP:
                _motors.setEnable(false);
                break;
            case ControlMode::BALANCE:
                _motors.setEnable(true);
                ControlSystems::PIDControlSystem::Inputs inputs = _angle_control.update(Sensors::imu.getTheta(), 1.0);
                // inputs.diff = 0.12;
                Log.infoln(F("Sum: %F, Diff: %F"), (float)inputs.sum, (float)inputs.diff);
                _motors.setInputSD(inputs.sum, inputs.diff);
                break;
        }
    }
    Log.setLevel(LOG_LEVEL_INFO);
}

Balancer balancer{};