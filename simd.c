#include <stdio.h>
#include "header.h"
#include <immintrin.h>
#include <float.h>

void simd(float* data, const int n) {
    printf("SIMD\n");

    float min_val, max_val;

    findMinMaxSimd(data, n, &min_val, &max_val);

    const float range = max_val - min_val;

    if (range == 0.0f) {
        makeZeroSimd(data, n);
        return;
    }

    const float inv_range = 1.0f / range;

    normalizeSimd(data, n, min_val, inv_range);
}

void normalizeSimd(float* data, const int n, float min_val, float inv_range) {
    if (data == NULL || n <= 0) return;
    const __m256 v_min = _mm256_set1_ps(min_val);
    const __m256 v_inv_range = _mm256_set1_ps(inv_range);

    int i = 0;
    for (; i <= n - 8; i += 8) {
        const __m256 v_data = _mm256_loadu_ps(&data[i]);
        const __m256 v_sub = _mm256_sub_ps(v_data, v_min);
        const __m256 v_res = _mm256_mul_ps(v_sub, v_inv_range);

        _mm256_storeu_ps(&data[i], v_res);
    }
    for (; i < n; i++) {
        data[i] = (data[i] - min_val) * inv_range;
    }
}

void makeZeroSimd(float* data, const int n) {
    if (data == NULL || n <= 0) return;
    const __m256 v_zero = _mm256_setzero_ps();
    int i = 0;
    for (; i <= n - 8; i += 8) {
        _mm256_storeu_ps(&data[i], v_zero);
    }
    for (; i < n; i++) {
        data[i] = 0.0f;
    }
}

void findMinMaxSimd(const float* data, const int n, float* out_min, float* out_max) {
    if (data == NULL || n <= 0) return;

    __m256 v_min = _mm256_set1_ps(FLT_MAX);
    __m256 v_max = _mm256_set1_ps(FLT_MIN);

    int i = 0;
    for (; i <= n - 8; i += 8) {
        const __m256 v_data = _mm256_loadu_ps(&data[i]);

        v_min = _mm256_min_ps(v_min, v_data);
        v_max = _mm256_max_ps(v_max, v_data);
    }

    float res_min[8], res_max[8];
    _mm256_storeu_ps(res_min, v_min);
    _mm256_storeu_ps(res_max, v_max);

    float current_min = res_min[0];
    float current_max = res_max[0];
    for (int j = 1; j < 8; j++) {
        if (res_min[j] < current_min) current_min = res_min[j];
        if (res_max[j] > current_max) current_max = res_max[j];
    }

    for (; i < n; i++) {
        if (data[i] < current_min) current_min = data[i];
        if (data[i] > current_max) current_max = data[i];
    }

    *out_min = current_min;
    *out_max = current_max;
}
