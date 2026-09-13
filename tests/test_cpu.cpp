#include <gtest/gtest.h>
#include <cmath>
#include <vector>

extern "C" {
    #include "header.h"
}

constexpr float EPSILON = 1e-5f;

TEST(CpuNormalizationTest, InvalidInputs) {
    EXPECT_NO_THROW(cpu(nullptr, 5));

    float data[] = {1.0f, 2.0f, 3.0f};
    cpu(data, 0);
    EXPECT_FLOAT_EQ(data[0], 1.0f);

    cpu(data, -5);
    EXPECT_FLOAT_EQ(data[0], 1.0f);
}

TEST(CpuNormalizationTest, StandardPositiveValues) {
    std::vector<float> data = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f};
    std::vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};

    cpu(data.data(), static_cast<int>(data.size()));

    for (size_t i = 0; i < data.size(); ++i) {
        EXPECT_NEAR(data[i], expected[i], EPSILON);
    }
}

TEST(CpuNormalizationTest, AllElementsEqual) {
    std::vector<float> data = {5.5f, 5.5f, 5.5f};

    cpu(data.data(), static_cast<int>(data.size()));

    for (float val : data) {
        EXPECT_FLOAT_EQ(val, 0.0f);
    }
}

TEST(CpuNormalizationTest, SingleElement) {
    float data[] = {42.0f};

    cpu(data, 1);

    EXPECT_FLOAT_EQ(data[0], 0.0f);
}

TEST(CpuNormalizationTest, NegativeAndZeroValues) {
    std::vector<float> data = {-10.0f, -5.0f, 0.0f, 5.0f, 10.0f};
    std::vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};

    cpu(data.data(), static_cast<int>(data.size()));

    for (size_t i = 0; i < data.size(); ++i) {
        EXPECT_NEAR(data[i], expected[i], EPSILON);
    }
}

TEST(CpuNormalizationTest, StrictlyNegativeValues) {
    std::vector<float> data = {-100.0f, -50.0f, -20.0f};
    std::vector<float> expected = {0.0f, 0.625f, 1.0f};

    cpu(data.data(), static_cast<int>(data.size()));

    for (size_t i = 0; i < data.size(); ++i) {
        EXPECT_NEAR(data[i], expected[i], EPSILON);
    }
}