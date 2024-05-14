#include <cstdio>
#include <pico/cyw43_arch.h>
#include <pico_graphics.hpp>
#include "pico_explorer.hpp"
#include "functions.h"

using namespace pimoroni;
using namespace std;

extern PicoGraphics_PenRGB332 graphics;

int main() {
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    dht_init();

    int i = 0;
    char celsius[20];
    char humidity[20];

    dht_reading dr;

    while (true) {
        clear();

        sleep_ms(2000);

        set_led(1);
        dht_read(&dr);
        set_led(0);

        sprintf(celsius, "%.fC", dr.temp_celsius);
        sprintf(humidity, "%.f%%", dr.humidity);

        graphics.set_font(&hershey::futural);
        graphics.text(celsius, Point(55, 85), 240);
        graphics.text(humidity, Point(55, 155), 240);

//        log_msg("%.f Celsius\n%.f Humidity\n\n", dr.temp_celsius, dr.humidity);
//        print_msgs(0);

        redraw();
        sleep_ms(1000);
        i++;
    }

    return 0;
}