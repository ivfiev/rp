#include <cstdio>
#include <pico/cyw43_arch.h>
#include <pico_graphics.hpp>
#include "pico_explorer.hpp"
#include "states.hpp"
#include "button.hpp"

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

    auto a = Button(PicoExplorer::A);
    auto b = Button(PicoExplorer::B);

    auto dht = DhtState();
    auto log = LogState();
    State *curr = &dht;

    while (true) {
        clear();
        sleep_ms(1000);

        curr->Tick();

        if (a.read()) {
            curr = &dht;
        } else if (b.read()) {
            curr = &log;
        }

        redraw();
        sleep_ms(1000);
    }

    return 0;
}