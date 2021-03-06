#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/time: samplesToMicroseconds", "")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    CHECK(test(mc::samplesToMicroseconds(44'100, 44'100.0), 1'000'000));
    CHECK(test(mc::samplesToMicroseconds(48'000, 48'000.0), 1'000'000));
    CHECK(test(mc::samplesToMicroseconds(88'200, 88'200.0), 1'000'000));
    CHECK(test(mc::samplesToMicroseconds(96'000, 96'000.0), 1'000'000));
    CHECK(test(mc::samplesToMicroseconds(22'050, 44'100.0), 500'000));
    CHECK(test(mc::samplesToMicroseconds(11'025, 44'100.0), 250'000));
}

TEST_CASE("core/time: samplesToMilliseconds", "")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    CHECK(test(mc::samplesToMilliseconds(44'100, 44'100.0), 1'000));
    CHECK(test(mc::samplesToMilliseconds(48'000, 48'000.0), 1'000));
    CHECK(test(mc::samplesToMilliseconds(88'200, 88'200.0), 1'000));
    CHECK(test(mc::samplesToMilliseconds(96'000, 96'000.0), 1'000));
    CHECK(test(mc::samplesToMilliseconds(22'050, 44'100.0), 500));
    CHECK(test(mc::samplesToMilliseconds(11'025, 44'100.0), 250));
}

TEST_CASE("core/time: samplesToSeconds", "")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    CHECK(test(mc::samplesToSeconds(44'100, 44'100.0), 1));
    CHECK(test(mc::samplesToSeconds(48'000, 48'000.0), 1));
    CHECK(test(mc::samplesToSeconds(88'200, 88'200.0), 1));
    CHECK(test(mc::samplesToSeconds(96'000, 96'000.0), 1));
    CHECK(test(mc::samplesToSeconds(22'050, 44'100.0), 0.5));
    CHECK(test(mc::samplesToSeconds(11'025, 44'100.0), 0.25));
}

TEST_CASE("core/time: toSampleCount(Microseconds)", "")
{
    CHECK(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 44'100.0) == Catch::Approx(44'100));
    CHECK(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 48'000.0) == Catch::Approx(48'000));
    CHECK(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 88'200.0) == Catch::Approx(88'200));
    CHECK(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 96'000.0) == Catch::Approx(96'000));
    CHECK(mc::toSampleCount(mc::Microseconds<double> { 500'000 }, 44'100.0) == Catch::Approx(22'050));
    CHECK(mc::toSampleCount(mc::Microseconds<double> { 250'000 }, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("core/time: toSampleCount(Milliseconds)", "")
{
    CHECK(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 44'100.0) == Catch::Approx(44'100));
    CHECK(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 48'000.0) == Catch::Approx(48'000));
    CHECK(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 88'200.0) == Catch::Approx(88'200));
    CHECK(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 96'000.0) == Catch::Approx(96'000));
    CHECK(mc::toSampleCount(mc::Milliseconds<double> { 500 }, 44'100.0) == Catch::Approx(22'050));
    CHECK(mc::toSampleCount(mc::Milliseconds<double> { 250 }, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("core/time: toSampleCount(Seconds)", "")
{
    CHECK(mc::toSampleCount(mc::Seconds<double> { 1 }, 44'100.0) == Catch::Approx(44'100));
    CHECK(mc::toSampleCount(mc::Seconds<double> { 1 }, 48'000.0) == Catch::Approx(48'000));
    CHECK(mc::toSampleCount(mc::Seconds<double> { 1 }, 88'200.0) == Catch::Approx(88'200));
    CHECK(mc::toSampleCount(mc::Seconds<double> { 1 }, 96'000.0) == Catch::Approx(96'000));
    CHECK(mc::toSampleCount(mc::Seconds<double> { 0.5 }, 44'100.0) == Catch::Approx(22'050));
    CHECK(mc::toSampleCount(mc::Seconds<double> { 0.25 }, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("core/time: barsToSamples", "")
{
    CHECK(mc::barsToSamples(1.0, 240.0, 44'100.0) == Catch::Approx(44'100.0));
    CHECK(mc::barsToSamples(1.0, 120.0, 44'100.0) == Catch::Approx(88'200.0));
    CHECK(mc::barsToSamples(1.0, 120.0, 88'200.0) == Catch::Approx(176'400.0));

    CHECK(mc::barsToSamples(2.0, 120.0, 44'100.0) == Catch::Approx(176'400.0));
    CHECK(mc::barsToSamples(1.0 / 16.0, 240.0, 44'100.0) == Catch::Approx(2756.25));
    CHECK(mc::barsToSamples(1.0 / 8.0, 240.0, 44'100.0) == Catch::Approx(5512.5));
}

TEST_CASE("core/time: barsToSeconds", "")
{
    CHECK(mc::barsToSeconds(120.0, 2.0, 1.0) == mc::Seconds<double> { 4.0 });
    CHECK(mc::barsToSeconds(120.0, 1.0, 1.0) == mc::Seconds<double> { 2.0 });
    CHECK(mc::barsToSeconds(120.0, 1.0, 4.0) == mc::Seconds<double> { 0.5 });
}

TEST_CASE("core/time: bpmToHertz", "")
{
    CHECK(mc::bpmToHertz(60.0) == 1.0);
    CHECK(mc::bpmToHertz(120.0) == 2.0);
}

TEST_CASE("core/time: TriggerClock", "")
{
    auto clock = mc::TriggerClock {};
    clock.setSampleRate(44'100.0);
    clock.setTickLength(mc::Seconds<double> { 1.0 });
    CHECK(clock.advance(32));
    CHECK_FALSE(clock.advance(32));
    CHECK(clock.advance(44'100));
    CHECK_FALSE(clock.advance(32));

    clock.reset();
    CHECK(clock.advance(32));
    CHECK_FALSE(clock.advance(32));
    CHECK(clock.advance(44'100));
    CHECK_FALSE(clock.advance(32));
}
