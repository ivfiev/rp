#include <cstdarg>
#include <cstdio>
#include "pico_explorer.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "font8_data.hpp"

#define SIZE_BUF 4096  // TODO finish wrapping
#define SIZE_MSG 25
#define SIZE_SCREEN 17

using namespace std;

extern PicoGraphics_PenRGB332 graphics;
extern Pen WHITE;

int i;
char buf[SIZE_BUF];
char msg[SIZE_MSG];

void log_msg(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int written = vsnprintf(msg, SIZE_MSG, format, args);

    for (int j = 0; j < written; j++) {
        buf[i] = msg[j];
        i = (i + 1) % SIZE_BUF;
    }

    va_end(args);
}

void print_msgs(uint offset) {
    int j = i;
    int count = offset + SIZE_SCREEN + 1;

    while (0 < count && 0 <= j) {
        if (buf[j] == '\n') {
            count--;
        }
        j--;
    }

    graphics.set_pen(WHITE);
    graphics.text(buf + j + (buf[j+1] == '\n' ? 2 : 1), Point(1, 1), 240);
}