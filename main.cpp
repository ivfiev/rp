#include "pico_explorer.hpp"
#include "functions.h"

using namespace pimoroni;
using namespace std;

int main() {
    stdio_init_all();

    int i = 0;

    while (true) {
        clear();

        log_msg("ASDF %d\n", i);
        print_msgs(0);

        redraw();

        sleep_ms(100);
        i++;
    }

    return 0;
}