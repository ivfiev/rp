#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;
using namespace std;

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);
Pen BG = graphics.create_pen(120, 40, 60);
Pen WHITE = graphics.create_pen(255, 255, 255);

void clear() {
    graphics.set_pen(BG);
    graphics.clear();
    graphics.set_pen(WHITE);
}

void redraw() {
    st7789.update(&graphics);
}