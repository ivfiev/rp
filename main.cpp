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

    int i = 0;

    wifi_scan();

//    while (true) {
//        clear();
//
//        log_msg("ASDF %d\n", i);
//        print_msgs(0);
//
//        redraw();
//
//        set_led(i & 1);
//
//        sleep_ms(1000);
//        i++;
//    }

    return 0;
}