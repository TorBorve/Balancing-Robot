#pragma once

#include <PID_v1.h>

namespace ControlSystems {
class PIDControlSystem {
public:
    PIDControlSystem(double KpSum, double KiSum, double KdSum, double KpDiff, double KiDiff, double KdDiff, double setpointSum, double setpointDiff);
    void setSampleTime(double sampleTime);
    void setOutputLimits(double minSum, double maxSum, double minDiff, double maxDiff);
    void setTunings(double KpSum, double KiSum, double KdSum, double KpDiff, double KiDiff, double KdDiff);
    void setSetpoints(double setpointSum, double setpointDiff);
    void update(double inputSum, double inputDiff);
private:
    PID _pidSum;
    double _inputSum;
    double _outputSum;
    double _setpointSum;

    PID _pidDiff;
    double _inputDiff;
    double _outputDiff;
    double _setpointDiff;
};
}  // namespace ControlSystems