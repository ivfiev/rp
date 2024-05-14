typedef struct {
    float humidity;
    float temp_celsius;
} dht_reading;

void log_msg(const char *format, ...);
void print_msgs(uint offset);

void clear();
void redraw();

void set_led(int);

void wifi_scan();

void dht_init();
void dht_read(dht_reading *);

class DhtState;
class LogState;