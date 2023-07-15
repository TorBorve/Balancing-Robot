#include "Motors.h"

#include <Arduino.h>

Motors::Motors(unsigned int leftForwardPin, unsigned int leftBackwardPin, unsigned int rightForwardPin, unsigned int rightBackwardPin,
               float scaleLeft, float scaleRight, float maxInputPercent)
    : _leftForwardPin(leftForwardPin),
      _leftBackwardPin(leftBackwardPin),
      _rightForwardPin(rightForwardPin),
      _rightBackwardPin(rightBackwardPin),
      _scaleLeft(scaleLeft),
      _scaleRight(scaleRight),
      _maxInputPercent(maxInputPercent),
      _inputLeft(0),
      _inputRight(0),
      _enable(false) {
    pinMode(_leftForwardPin, OUTPUT);
    pinMode(_leftBackwardPin, OUTPUT);
    pinMode(_rightForwardPin, OUTPUT);
    pinMode(_rightBackwardPin, OUTPUT);

    analogWrite(_leftForwardPin, 0);
    analogWrite(_leftBackwardPin, 0);
    analogWrite(_rightForwardPin, 0);
    analogWrite(_rightBackwardPin, 0);
}

Motors::Motors(unsigned int leftForwardPin, unsigned int leftBackwardPin, unsigned int rightForwardPin, unsigned int rightBackwardPin)
    : Motors{leftForwardPin, leftBackwardPin, rightForwardPin, rightBackwardPin, 1.0, 1.0, 1.0} {}

void Motors::setInputSD(float sum, float diff) {
    float left = (sum - diff) / 2;
    float right = (sum + diff) / 2;
    setInputLR(left, right);
}
void Motors::setInputLR(float left, float right) {
    _inputLeft = left;
    _inputRight = right;
    if (_enable) {
        setInputOneSide(_leftForwardPin, _leftBackwardPin, left);
        setInputOneSide(_rightForwardPin, _rightBackwardPin, right);
    }
}

void Motors::setInputOneSide(unsigned int forwardPin, unsigned int backwardPin, float input) {
    input *= _scaleLeft;
    float maxInput = _maxInputPercent * 255;
    constexpr float offset = 0.09;
    input = min(max(255 * input, -maxInput), maxInput);
    if (input > 0) {
        analogWrite(forwardPin, input + offset);
        analogWrite(backwardPin, 0);
    } else {
        analogWrite(forwardPin, 0);
        analogWrite(backwardPin, -input + offset);
    }
}

void Motors::setEnable(bool enable) {
    if (enable) {
        setInputLR(_inputLeft, _inputRight);
    } else {
        setInputLR(0, 0);
    }
    this->_enable = enable;
}

bool Motors::getEnable() const { return _enable; }

void Motors::setOutputScales(float scaleLeft, float scaleRight) {
    scaleLeft = scaleLeft;
    scaleRight = scaleRight;
}

void Motors::setMaxInputPercent(float maxInputPercent) {
    _maxInputPercent = maxInputPercent;
}