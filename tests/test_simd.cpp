#include <gtest/gtest.h>
#include <vector>
#include <cmath>

extern "C" {
    #include "header.h"
}

constexpr float EPSILON = 1e-5f;

TEST(SimdNormalizationTest, InvalidInputs) {
    EXPECT_NO_THROW(simd(nullptr, 16));

    float data[] = {1.0f, 2.0f, 3.0f};
    simd(data, 0);
    EXPECT_FLOAT_EQ(data[0], 1.0f);

    simd(data, -8);
    EXPECT_FLOAT_EQ(data[0], 1.0f);
}

TEST(SimdNormalizationTest, MultipleOfEightSize) {
    std::vector data = {
        1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 17.0f
    };
    std::vector<float> expected(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        expected[i] = (data[i] - 1.0f) / 16.0f;
    }

    simd(data.data(), static_cast<int>(data.size()));

    for (size_t i = 0; i < data.size(); ++i) {
        EXPECT_NEAR(data[i], expected[i], EPSILON);
    }
}

TEST(SimdNormalizationTest, NonMultipleOfEightSize) {
    std::vector data = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f, 100.0f, 110.0f};

    simd(data.data(), static_cast<int>(data.size()));

    EXPECT_NEAR(data[0], 0.0f, EPSILON);
    EXPECT_NEAR(data[5], 0.5f, EPSILON);
    EXPECT_NEAR(data[10], 1.0f, EPSILON);
}

TEST(SimdNormalizationTest, SmallArrayLessThanEight) {
    std::vector data = {2.0f, 4.0f, 6.0f, 8.0f, 10.0f};

    simd(data.data(), static_cast<int>(data.size()));

    EXPECT_NEAR(data[0], 0.0f, EPSILON);
    EXPECT_NEAR(data[2], 0.5f, EPSILON);
    EXPECT_NEAR(data[4], 1.0f, EPSILON);
}

TEST(SimdNormalizationTest, AllElementsEqual) {
    std::vector data(10, 7.5f);

    simd(data.data(), static_cast<int>(data.size()));

    for (float val : data) {
        EXPECT_FLOAT_EQ(val, 0.0f);
    }
}


TEST(SimdNormalizationTest, NegativeValues) {
    std::vector data = {
        -16.0f, -14.0f, -12.0f, -10.0f, -8.0f, -6.0f, -4.0f, -2.0f, 0.0f
    };

    simd(data.data(), static_cast<int>(data.size()));

    EXPECT_NEAR(data[0], 0.0f, EPSILON);
    EXPECT_NEAR(data[4], 0.5f, EPSILON);
    EXPECT_NEAR(data[8], 1.0f, EPSILON);
}