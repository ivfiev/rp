#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>

#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

#include "font6_data.hpp"
#include "font8_data.hpp"

using namespace pimoroni;

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

int main() {
    stdio_init_all();
    graphics.set_font(&font8);

    Pen BG = graphics.create_pen(120, 40, 60);
    Pen WHITE = graphics.create_pen(255, 255, 255);

    uint32_t i = 0;

    while (true) {
        graphics.set_pen(BG);
        graphics.clear();

        graphics.set_pen(WHITE);
        graphics.set_font(&font8);
        if (i & 1) {
            graphics.text("hello", Point(100, 111), 200);
        } else {
            graphics.text("world", Point(100, 111), 200);
        }

        st7789.update(&graphics);
        sleep_ms(500);
        i++;
    }

    return 0;
}
