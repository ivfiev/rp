#include <boards/pico_w.h>
#include <pico/cyw43_arch.h>
#include <cstdio>
#include "hardware/vreg.h"
#include "pico/stdlib.h"

static int scan_result(void *env, const cyw43_ev_scan_result_t *result) {
    if (result) {
        printf("ssid: %-32s rssi: %4d chan: %3d mac: %02x:%02x:%02x:%02x:%02x:%02x sec: %u\n",
               result->ssid, result->rssi, result->channel,
               result->bssid[0], result->bssid[1], result->bssid[2], result->bssid[3], result->bssid[4], result->bssid[5],
               result->auth_mode);
    }
    return 0;
}

int wifi_scan() {
    cyw43_arch_enable_sta_mode();
    absolute_time_t scan_time = nil_time;
    bool scan_in_progress = false;

    while(true) {
        if (absolute_time_diff_us(get_absolute_time(), scan_time) < 0) {
            if (!scan_in_progress) {
                cyw43_wifi_scan_options_t scan_options = {0};
                int err = cyw43_wifi_scan(&cyw43_state, &scan_options, nullptr, scan_result);
                if (err == 0) {
                    printf("\nPerforming wifi scan\n");
                    scan_in_progress = true;
                } else {
                    printf("Failed to start scan: %d\n", err);
                    scan_time = make_timeout_time_ms(10000);
                }
            } else if (!cyw43_wifi_scan_active(&cyw43_state)) {
                scan_time = make_timeout_time_ms(10000);
                scan_in_progress = false;
            }
        }
#if PICO_CYW43_ARCH_POLL
        cyw43_arch_poll();
        cyw43_arch_wait_for_work_until(scan_time);
#else
        sleep_ms(1000);
#endif
    }

    cyw43_arch_deinit();
    return 0;
}

void set_led(int value) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, value);
}