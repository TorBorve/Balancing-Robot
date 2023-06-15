#include "HumanInterface.h"

#include <Arduino.h>

LED::LED(uint8_t pin, Mode mode, uint32_t blink_interval) :
    _pin(pin), _mode(mode), _blink_interval(blink_interval), _last_blink_time(0) {
    pinMode(_pin, OUTPUT);
    update();
}
void LED::update() {
    if (_mode == Mode::BLINK) {
        if (millis() > _last_blink_time + _blink_interval) {
            _last_blink_time = millis();
            digitalWrite(_pin, !digitalRead(_pin));
        }
    } else {
        digitalWrite(_pin, (_mode == Mode::ON));
    }
}
void LED::setMode(Mode mode) {
    _mode = mode;
    update();
}

LED::Mode LED::getMode() const { return _mode;}

void LED::setBlinkInterval(uint32_t blink_interval) {
    _blink_interval = blink_interval;
    update();
}

uint32_t LED::getBlinkInterval() const { return _blink_interval;}