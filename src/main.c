#include "color.h"
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void rgb_handler(ColorRGB rgb) {
    ColorRGB rgb2 = linear_to_srgb(rgb);
    int r = clamp((int)(rgb2.r * 255), 0, 255);
    int g = clamp((int)(rgb2.g * 255), 0, 255);
    int b = clamp((int)(rgb2.b * 255), 0, 255);
    printf("\033[38;2;%d;%d;%dm", clamp(r - 25, 0, 255), clamp(g - 25, 0, 255),
           clamp(b - 25, 0, 255));
    printf("\033[48;2;%d;%d;%dm>.<!!\n", r, g, b);
}

void clean_fd(int* fd) {
    if (*fd >= 1) { close(*fd); }
}

u64 true_random() {
    cleanup(clean_fd) int fd = open("/dev/random", O_RDONLY);
    u64 thing = 0;
    (void)read(fd, &thing, 8);
    return thing;
}

int main() {
    struct timespec ts;

    ColorOKLCH oklch_1 = {(true_random() % 1000) / 1000.0,
                          (true_random() % 1000) / 10000.0,
                          (true_random() % 1000) / 1000.0};

    ColorOKLCH oklch_2 = {(true_random() % 1000) / 1000.0,
                          (true_random() % 1000) / 10000.0,
                          (true_random() % 1000) / 1000.0};

    printf("random gradient gen\n");
    printf("%f %f\n", oklch_1.l, oklch_2.l);
    printf("%f %f\n", oklch_1.c, oklch_2.c);
    printf("%f %f\n", oklch_1.h, oklch_2.h);

    ColorHandler handler = {0};
    handler.color_rgb = rgb_handler;
    handler.supported_spaces = RGB;

    color_install_handler(handler);

    for (int i = 0; i < 100; i++) {
        ColorOKLCH oklch =
            color_oklch_lerp(oklch_1, oklch_2, i / (100.0 - 1.0));
        Color color = {0};
        color.color_rgb = color_oklch_to_rgb(oklch);
        color.type = RGB;
        color_run_handler(0, color);
        ts.tv_sec = 0;
        ts.tv_nsec = 5 * 1000000;
        nanosleep(&ts, NULL);
    }

    printf("\033[0m");

    return 0;
}
