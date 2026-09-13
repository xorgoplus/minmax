#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

#define DEFAULT_N (1 << 24)

int main(const int argc, char *argv[]) {
    void (*minMax)(float* data, int n) = cpu;
    int n = DEFAULT_N;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--kind") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "simd") == 0) {
                minMax = simd;
            }
            i++;
        } else if (strcmp(argv[i], "--size") == 0 && i + 1 < argc) {
            n = atoi(argv[i + 1]);
            i++;
        }
    }

    float* data = malloc(n * sizeof(float));
    if (!data) return 1;

    for (int i = 0; i < n; i++) {
        data[i] = (float)rand() / RAND_MAX * 500.0f - 100.0f;
    }

    const clock_t start = clock();
    minMax(data, n);
    const clock_t end = clock();

    const double time_used = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%.6f\n", time_used);

    free(data);
    return 0;
}
