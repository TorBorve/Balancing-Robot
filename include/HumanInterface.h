#pragma once

#include <stdint.h>

// Button classs, encapsulate the functionality of a latched button
// Found at https://forum.arduino.cc/t/buttons-an-object-oriented-approach/279724/7
class Button {
   protected:
    uint8_t _pin;             // hardware pin number
    bool _wasPressed;      // button latch
    uint16_t _startDebounce;  // start of debounce time

   public:
    uint16_t debounceMs;  // period before button latches

    Button(uint8_t pin);
    void poll(uint32_t now);                          // call periodically to refresh the button state
    bool wasPressed(void) { return _wasPressed; }  // return the latch state
    void reset(void);                                 // reset the latch
};


// LED class, encapsulate the functionality of an LED
class LED {
   public:
    enum Mode { OFF, ON, BLINK };
    LED(uint8_t pin, Mode mode, uint32_t blink_interval = 1000);
    void update();
    void setMode(Mode mode);
    Mode getMode() const;
    void setBlinkInterval(uint32_t blink_interval);
    uint32_t getBlinkInterval() const;

   private:
    uint8_t _pin;
    Mode _mode;
    uint32_t _blink_interval;
    uint32_t _last_blink_time;
};


// Human interface class. Used to encapusalte all the  buttons and LEDs connected to the teensy. 
class HumanInterface {
   public:
    HumanInterface();
    void update();

   private:
    LED _red_led;
    LED _yellow_led;
    LED _green_led;
    LED _builtin_led;
    Button _on_off_button;
    uint32_t _last_update_time;
};

extern HumanInterface humanInterface;