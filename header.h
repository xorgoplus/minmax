//
// Created by bmyhi on 13.09.2026.
//

#ifndef UNTITLED_CPU_H
#define UNTITLED_CPU_H




void cpu(float* data, int n);
void simd(float* data, int n);

void findMinMaxSimd(const float* data, int n, float* out_min, float* out_max);
void makeZeroSimd(float* data, int n);
void normalizeSimd(float* data, int n, float min_val, float inv_range);


#endif //UNTITLED_CPU_H