#include <mcj_dsp/mcj_dsp.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("dsp/units: samplesToMicroseconds", "[dsp]")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    REQUIRE(test(mc::samplesToMicroseconds(44'100, 44'100.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(48'000, 48'000.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(88'200, 88'200.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(96'000, 96'000.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(22'050, 44'100.0), 500'000));
    REQUIRE(test(mc::samplesToMicroseconds(11'025, 44'100.0), 250'000));
}

TEST_CASE("dsp/units: samplesToMilliseconds", "[dsp]")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    REQUIRE(test(mc::samplesToMilliseconds(44'100, 44'100.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(48'000, 48'000.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(88'200, 88'200.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(96'000, 96'000.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(22'050, 44'100.0), 500));
    REQUIRE(test(mc::samplesToMilliseconds(11'025, 44'100.0), 250));
}

TEST_CASE("dsp/units: samplesToSeconds", "[dsp]")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    REQUIRE(test(mc::samplesToSeconds(44'100, 44'100.0), 1));
    REQUIRE(test(mc::samplesToSeconds(48'000, 48'000.0), 1));
    REQUIRE(test(mc::samplesToSeconds(88'200, 88'200.0), 1));
    REQUIRE(test(mc::samplesToSeconds(96'000, 96'000.0), 1));
    REQUIRE(test(mc::samplesToSeconds(22'050, 44'100.0), 0.5));
    REQUIRE(test(mc::samplesToSeconds(11'025, 44'100.0), 0.25));
}

TEST_CASE("dsp/units: toSampleCount(Microseconds)", "[dsp]")
{
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 44'100.0) == Catch::Approx(44'100));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 48'000.0) == Catch::Approx(48'000));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 88'200.0) == Catch::Approx(88'200));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 96'000.0) == Catch::Approx(96'000));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 500'000 }, 44'100.0) == Catch::Approx(22'050));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 250'000 }, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("dsp/units: toSampleCount(Milliseconds)", "[dsp]")
{
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 44'100.0) == Catch::Approx(44'100));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 48'000.0) == Catch::Approx(48'000));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 88'200.0) == Catch::Approx(88'200));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 96'000.0) == Catch::Approx(96'000));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 500 }, 44'100.0) == Catch::Approx(22'050));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 250 }, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("dsp/units: toSampleCount(Seconds)", "[dsp]")
{
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 44'100.0) == Catch::Approx(44'100));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 48'000.0) == Catch::Approx(48'000));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 88'200.0) == Catch::Approx(88'200));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 96'000.0) == Catch::Approx(96'000));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 0.5 }, 44'100.0) == Catch::Approx(22'050));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 0.25 }, 44'100.0) == Catch::Approx(11'025));
}
