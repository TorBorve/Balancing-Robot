#pragma once

#include <stdint.h>

#include "Motors.h"
#include "PIDControlSystem.h"

#define MOTOR_LEFT_FORWARD_PIN 7
#define MOTOR_LEFT_BACKWARD_PIN 8
#define MOTOR_RIGHT_FORWARD_PIN 9
#define MOTOR_RIGHT_BACKWARD_PIN 10

#define MAIN_LOOP_INTERVAL 10  // ms

#define MAX_ANGLE_STOP (60.0 * M_PI / 180.0)  // radians

enum ControlMode { STOP, BALANCE };

class Balancer {
   public:
    Balancer();
    bool setup();
    void update();

   private:
    ControlSystems::PIDControlSystem _angle_control;
    ControlMode _control_mode;
    Motors _motors;
    uint32_t _last_update_time;
};

extern Balancer balancer;