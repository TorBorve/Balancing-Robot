#pragma once

class Motors {
public:
    Motors(unsigned int leftForwardPin, unsigned int leftBackwardPin, unsigned int rightForwardPin, unsigned int rightBackwardPin);
    Motors(unsigned int leftForwardPin, unsigned int leftBackwardPin, unsigned int rightForwardPin, unsigned int rightBackwardPin, float scaleLeft, float scaleRight, float maxInputPercent);
    void setInputSD(float sum, float diff);
    void setInputLR(float left, float right);
    void setEnable(bool enable);
    void setOutputScales(float scaleLeft, float scaleRight);
    bool getEnable() const;
    void setMaxInputPercent(float maxInputPercent);
private:
    void setInputOneSide(unsigned int forwardPin, unsigned int backwardPin, float input);
    unsigned int _leftForwardPin;
    unsigned int _leftBackwardPin;
    unsigned int _rightForwardPin;
    unsigned int _rightBackwardPin;
    float _scaleLeft;
    float _scaleRight;
    float _maxInputPercent;
    float _inputLeft;
    float _inputRight;
    bool _enable;
};