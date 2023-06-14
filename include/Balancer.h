#pragma once

#include <stdint.h>

#include "Motors.h"
#include "PIDControlSystem.h"

#define MOTOR_LEFT_FORWARD_PIN 2
#define MOTOR_LEFT_BACKWARD_PIN 3
#define MOTOR_RIGHT_FORWARD_PIN 4
#define MOTOR_RIGHT_BACKWARD_PIN 5

#define MAIN_LOOP_INTERVAL 10  // ms

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