#define NO_COLOR_IMPLEMENTATION
#include "game_input.h"
#include "terminal.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

bool is_running = true;

void sighandler(int signum) {
    (void)signum;
    is_running = false;
}

u64 get_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000 + (u64)ts.tv_nsec / 1000000;
}

int main() {
    u16 w, h;
    u64 counter = 0;

    terminal_init();

    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);

    terminal_get_size(&w, &h);

    u64 now = get_time_ms();
    u64 last = now;

    while (is_running) {
        terminal_get_size(&w, &h);
        do_input();

        counter += 1;

        terminal_write('@', (ColorRGB) {.r = 0.5, .g = 0.5, .b = 0.5},
                       (ColorRGB) {0}, counter % w, (counter / w) % h);

        terminal_present();
    }

    return 0;
}
