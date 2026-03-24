#include "vector.h"
#include <stdio.h>

DeclareVector(u32) int main() {
    Vectoru32 list = vectoru32_init(0);

    for (int i = 0; i < 50; i++) {
        vectoru32_push(&list, 0xCAFEBABE);
        vectoru32_push(&list, 0xDEADBEEF);
    }

    for (int i = 0; i < 50; i++) {
        log("%X %X\n", list.data[2 * i], list.data[(2 * i) + 1]);
    }
}
