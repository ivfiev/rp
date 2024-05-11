#include <cstdio>
#include <pico/cyw43_arch.h>
#include "pico_explorer.hpp"
#include "functions.h"

using namespace pimoroni;
using namespace std;

int main() {
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    dht_init();

    int i = 0;

    dht_reading dr;

    while (true) {
        clear();

        sleep_ms(5000);
        dht_read(&dr);
        //printf("%f.0 %f.0\n", dr.temp_celsius, dr.humidity);

        log_msg("%.f Celsius\n%.f Humidity\n\n", dr.temp_celsius, dr.humidity);
        print_msgs(0);

        redraw();

        //set_led(i & 1);

        sleep_ms(1000);
        i++;
    }

    return 0;
}