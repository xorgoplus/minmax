#include <stdio.h>
#include "header.h"
#include <float.h>

void cpu(float* data, const int n) {
    printf("CPU\n");
    if (data == NULL || n <= 0) return;

    float min_val = FLT_MAX;
    float max_val = FLT_MIN;

    for (int i = 0; i < n; i++) {
        if (data[i] < min_val) min_val = data[i];
        if (data[i] > max_val) max_val = data[i];
    }

    const float range = max_val - min_val;

    if (range == 0.0f) {
        for (int i = 0; i < n; i++) {
            data[i] = 0.0f;
        }
        return;
    }

    const float inv_range = 1.0f / range;

    for (int i = 0; i < n; i++) {
        data[i] = (data[i] - min_val) * inv_range;
    }
}
