#include "HumanInterface.h"

#include <Arduino.h>

#define RED_LED_PIN 32
#define YELLOW_LED_PIN 31
#define GREEN_LED_PIN 30

#define FAST_BLINK_INTERVAL 100
#define MEDIUM_BLINK_INTERVAL 500
#define SLOW_BLINK_INTERVAL 1000

#define ON_OFF_BUTTON_PIN 32

#define HUMAN_INTERFACE_UPDATE_INTERVAL 50

// constructor
Button::Button(uint8_t pin) : _pin{pin}, _wasPressed{false}, _startDebounce{0}, debounceMs{500} { pinMode(_pin, INPUT_PULLUP); }

// refresh the button state
void Button::poll(uint32_t now) {
    // pullup resistors cause the
    //  button to be HIGH when open
    //  so we invert the hardware state
    uint8_t state = !digitalRead(_pin);

    // when the button state is false, reset the debounce time
    if (!state) {
        _startDebounce = 0;
    } else {
        // start debounce time
        if (!_startDebounce) {
            _startDebounce = now;
        } else {
            // latch the button if it is still pressed when the debounce time expires
            if (now - _startDebounce > debounceMs) {
                _wasPressed = true;
            }
        }
    }
}

// reset the button
void Button::reset(void) {
    _wasPressed = false;
    _startDebounce = 0;
}

LED::LED(uint8_t pin, Mode mode, uint32_t blink_interval) : _pin(pin), _mode(mode), _blink_interval(blink_interval), _last_blink_time(0) {
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

LED::Mode LED::getMode() const { return _mode; }

void LED::setBlinkInterval(uint32_t blink_interval) {
    _blink_interval = blink_interval;
    update();
}

uint32_t LED::getBlinkInterval() const { return _blink_interval; }

HumanInterface::HumanInterface()
    : _red_led(RED_LED_PIN, LED::Mode::OFF),
      _yellow_led(YELLOW_LED_PIN, LED::Mode::OFF),
      _green_led(GREEN_LED_PIN, LED::Mode::OFF),
      _builtin_led(LED_BUILTIN, LED::Mode::BLINK, FAST_BLINK_INTERVAL),
      _last_update_time(0),
      _on_off_button(ON_OFF_BUTTON_PIN) {
    update();
}

void HumanInterface::update() {
    if (millis() > _last_update_time + HUMAN_INTERFACE_UPDATE_INTERVAL) {
        _last_update_time = millis();
        _red_led.update();
        _yellow_led.update();
        _green_led.update();
        _builtin_led.update();
    }
}