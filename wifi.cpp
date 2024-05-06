#include <boards/pico_w.h>
#include <pico/cyw43_arch.h>

void set_led(int value) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, value);
}