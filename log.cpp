#include <cstdarg>
#include <cstdio>
#include "pico_explorer.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "font8_data.hpp"

#define SIZE_BUF 1024
#define SIZE_MSG 32
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
        buf[i % SIZE_BUF] = msg[j];
        i++;
    }

    va_end(args);
}

void print_msgs(uint offset) {
    int j = i;
    int lines = offset + SIZE_SCREEN + 1;
    int lower_bound = i > SIZE_BUF ? i - SIZE_BUF : 0;

    while (0 < lines && lower_bound < j) {
        if (buf[j % SIZE_BUF] == '\n') {
            lines--;
        }
        j--;
    }

    if (j && !lines) {
        j = buf[(j + 1) % SIZE_BUF] == '\n' ? j + 2 : j;
    }

    graphics.set_pen(WHITE);
    int y_offset = 1;

    while (j < i) {
        int m = 0;
        for (; buf[j % SIZE_BUF] != '\n'; j++) {
            msg[m++] = buf[j % SIZE_BUF];
        }
        auto view = string_view(msg, m);
        graphics.text(view, Point(1, y_offset), 300);
        y_offset += 15;
        j++;
    }
}