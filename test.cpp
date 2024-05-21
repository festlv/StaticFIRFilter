#include <CppUTest/TestHarness.h>
#include "StaticFIRFilter.hpp"
#include <vector>
#include <iostream>

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
    printf("%f\n", v.value());

    v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());
    printf("%f\n", v.value());

    v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());
    printf("%f\n", v.value());

    v = filt.apply_filter(0.0f);
    CHECK_TRUE(v.has_value());
    printf("%f\n", v.value());


}
