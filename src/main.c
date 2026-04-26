#include "color.h"
#include <stdio.h>
#include <stdlib.h>

void color_printer(ColorXYZ xyz) {
    ColorRGB rgb = color_xyz_to_rgb(xyz);
    rgb = color_tonemap_lottes(rgb);
    rgb = linear_to_srgb(rgb);

    int r = clamp((int)(rgb.r * 255), 0, 256);
    int g = clamp((int)(rgb.g * 255), 0, 256);
    int b = clamp((int)(rgb.b * 255), 0, 256);

    printf("\033[48;2;%d;%d;%dm#%2x%2x%2x", r, g, b, r, g, b);
    printf("\033[0m\n");
}

int main() {
    ColorHandler handler = {.color_xyz = color_printer,
                            .supported_spaces = XYZ};

    color_install_handler(handler);

    double gain = 1;
    ColorXYZ a = color_cherenkov_to_xyz(1.33);

    a.x *= gain;
    a.y *= gain;
    a.z *= gain;
    Color color = {.color_xyz = a, .type = XYZ};
    color_run_handler(0, color);
}
