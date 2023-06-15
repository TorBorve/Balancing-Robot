#pragma once

#include <stdint.h>

#define RED_LED_PIN 32
#define YELLOW_LED_PIN 31
#define GREEN_LED_PIN 30

#define FAST_BLINK_INTERVAL 100
#define MEDIUM_BLINK_INTERVAL 500
#define SLOW_BLINK_INTERVAL 1000

#define HUMAN_INTERFACE_UPDATE_INTERVAL 50


class LED {
public:
    enum Mode {OFF, ON, BLINK};
    LED(uint8_t pin, Mode mode, uint32_t blink_interval = SLOW_BLINK_INTERVAL);
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


class HumanInterface {
   public:
    HumanInterface();
    bool setup();
    void update();

   private:
    LED _red_led;
    LED _yellow_led;
    LED _green_led;
    LED _builtin_led;
    uint32_t _last_update_time;
};