#include <CppUTest/TestHarness.h>
#include "StaticFIRFilter.hpp"
#include <vector>
#include <iostream>
#include <cmath>

TEST_GROUP(TestSFF)
{
};

TEST(TestSFF, TestBasic) {
    StaticFIRFilter<float, 3> filt({1.0f, 1.0f, 1.0f});
    CHECK_EQUAL(filt.num_taps(), 3);
    CHECK_FALSE(filt.apply_filter(1.0f).has_value());
    CHECK_FALSE(filt.apply_filter(0.0f).has_value());
    auto v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());
    CHECK_EQUAL(v.value(), 1.0f);

    //check that it decays to zero
    for (int i=0; i < 100; i++)
    {
        v = filt.apply_filter(0.0f);
        CHECK_TRUE(v.has_value());
    }

    v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());
    CHECK_EQUAL(v.value(), 0.0f);
}

TEST(TestSFF, TestInitZeros)
{
    StaticFIRFilter<float, 3> filt({0.5f, 1.0f, 0.5f});
    filt.init_zeros();
    auto v = filt.apply_filter(1.0f);
    CHECK_TRUE(v.has_value());

    v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());

    v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());

    v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());
}

bool is_equal(float a, float b, float epsilon) {
    return (fabsf(a-b)/b < epsilon);
}

TEST(TestSFF, TestDataCSV)
{
#include "testdata.h"

    std::vector<float> outdata;
    for (auto& v: test_samples) {
        auto ret = testFilter.apply_filter(v);
        if (ret)
            outdata.push_back(ret.value());
    }

    for (int i = 0; i < sizeof(test_output)/sizeof(test_output[0]); i++) {
        //0.01% accuracy to account for float in C++ vs double in python
        CHECK_TRUE(is_equal(test_output[i], outdata.at(i), 0.0001f));
    }

}
