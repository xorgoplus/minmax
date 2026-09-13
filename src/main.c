#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/header.h"

#define DEFAULT_N (1 << 24)

int main(const int argc, char *argv[]) {
    void (*minMax)(float* data, int n) = cpu;

    if (argc >= 3) {
        if (strcmp(argv[1], "--kind") == 0) {
            if (strcmp(argv[2], "simd") == 0) {
                minMax = simd;
            }
        }
    }

    const int n = DEFAULT_N;

    float* data = malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        data[i] = (float)rand() / RAND_MAX * 500.0f - 100.0f;
    }

    const clock_t start = clock();

    minMax(data, n);

    const clock_t end = clock();

    const double cpu_time_used =(double)(end - start) / CLOCKS_PER_SEC;
    printf("Done:  %.4f second.\n", cpu_time_used);

    free(data);
    return 0;
}
