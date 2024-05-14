#include <pico_graphics.hpp>
#include "functions.h"

using namespace pimoroni;

extern PicoGraphics_PenRGB332 graphics;

class State {
public:
    virtual void Tick(void);
};

class LogState : public State {
public:
    void Tick() override {
        print_msgs(0);
    }

    // scrolling
};

class DhtState : public State {
public:
    void Tick() override {
        dht_reading dr;
        char celsius[20];
        char humidity[20];

        set_led(1);
        dht_read(&dr);
        set_led(0);

        sprintf(celsius, "%.fC", dr.temp_celsius);
        sprintf(humidity, "%.f%%", dr.humidity);

        graphics.set_font(&hershey::futural);
        graphics.text(celsius, Point(55, 85), 240);
        graphics.text(humidity, Point(55, 155), 240);
    }
};