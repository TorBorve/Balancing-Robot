#include "Balancer.h"

#include <Arduino.h>

#include "logger.h"
#include "sensors.h"

Balancer::Balancer()
    : _angle_control(10.0, 4, 0.0, 0.0, 0.0, 0.0, -0.00, 0.0),
      _control_mode{ControlMode::BALANCE},
      _motors{MOTOR_LEFT_FORWARD_PIN, MOTOR_LEFT_BACKWARD_PIN, MOTOR_RIGHT_FORWARD_PIN, MOTOR_RIGHT_BACKWARD_PIN} {
    _angle_control.setSampleTime(MAIN_LOOP_INTERVAL);
    _angle_control.setOutputLimits(-2.0, 2.0, -2.0, 2.0);

    _motors.setMaxInputPercent(1.0);
    _motors.setEnable(true);
}

bool Balancer::setup() { return false; }

void Balancer::update() {
    if (millis() > _last_update_time + MAIN_LOOP_INTERVAL) {
        _last_update_time = millis();
        switch (_control_mode) {
            case ControlMode::STOP:
                _motors.setEnable(false);
                break;
            case ControlMode::BALANCE:
                _motors.setEnable(true);
                double theta = Sensors::imu.getTheta();
                if (fabs(theta) > MAX_ANGLE_STOP) {
                    _control_mode = ControlMode::STOP;
                    break;
                }
                ControlSystems::PIDControlSystem::Inputs inputs = _angle_control.update(theta, 0.0);
                // inputs.diff = 0.12;
                // inputs.sum = 2.0;
                // inputs.diff = 0.0;
                // Log.infoln(F("Sum: %F, Diff: %F"), (float)inputs.sum, (float)inputs.diff);
                _motors.setInputSD(inputs.sum, inputs.diff);
                break;
        }
    }
}

Balancer balancer{};