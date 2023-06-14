#include "PIDControlSystem.h"

#include "logger.h"

namespace ControlSystems {

PIDControlSystem::PIDControlSystem(double KpSum, double KiSum, double KdSum, double KpDiff, double KiDiff, double KdDiff, double setpointSum, double setpointDiff) :
    _pidSum(&_inputSum, &_outputSum, &_setpointSum, KpSum, KiSum, KdSum, DIRECT), _pidDiff(&_inputDiff, &_outputDiff, &_setpointDiff, KpDiff, KiDiff, KdDiff, DIRECT)
{
    _setpointSum = setpointSum;
    _setpointDiff = setpointDiff;
    _pidSum.SetMode(AUTOMATIC);
    _pidDiff.SetMode(AUTOMATIC);

}

void PIDControlSystem::setSampleTime(double sampleTime) {
    _pidSum.SetSampleTime(sampleTime);
    _pidDiff.SetSampleTime(sampleTime);
}

void PIDControlSystem::setOutputLimits(double minSum, double maxSum, double minDiff, double maxDiff) {
    _pidSum.SetOutputLimits(minSum, maxSum);
    _pidDiff.SetOutputLimits(minDiff, maxDiff);
}

void PIDControlSystem::setTunings(double KpSum, double KiSum, double KdSum, double KpDiff, double KiDiff, double KdDiff){
    _pidSum.SetTunings(KpSum, KiSum, KdSum);
    _pidDiff.SetTunings(KpDiff, KiDiff, KdDiff);
}

void PIDControlSystem::setSetpoints(double setpointSum, double setpointDiff) {
    _setpointSum = setpointSum;
    _setpointDiff = setpointDiff;
}

PIDControlSystem::Inputs PIDControlSystem::update(double inputSum, double inputDiff) {
    _inputSum = inputSum;
    _inputDiff = inputDiff;
    _pidSum.Compute();
    _pidDiff.Compute();

    return Inputs{_outputSum, _outputDiff};
}

}  // namespace ControlSystems