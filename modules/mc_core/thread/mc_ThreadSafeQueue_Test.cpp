#include "mc_core/mc_core.hpp"

#include "catch2/catch_template_test_macros.hpp"

#include <thread>

TEMPLATE_TEST_CASE("core/thread: ThreadSafeQueue", "[core][thread]", int, float, double, std::string, juce::String)
{
    SECTION("single thread")
    {
        auto queue = mc::ThreadSafeQueue<TestType> {};
        CHECK(queue.size() == 0);
        CHECK_FALSE(queue.pop().has_value());

        queue.push(TestType {});
        CHECK(queue.size() == 1);

        auto val = queue.pop();
        CHECK(queue.size() == 0);
        CHECK(val.has_value());
        CHECK(val.value() == TestType {});

        queue.push(TestType {});
        queue.push(TestType {});
        CHECK(queue.size() == 2);
    }

    SECTION("two thread")
    {
        auto iterations = 10'000;
        auto queue      = mc::ThreadSafeQueue<TestType> {};
        auto thread     = std::thread([&queue, iterations] {
            for (auto i = 0; i < iterations; ++i) { queue.push(TestType {}); }
        });

        auto counter = 0;
        while (counter != iterations)
        {
            auto val = queue.pop();
            if (val.has_value())
            {
                counter += 1;
                CHECK(val.value() == TestType {});
            }
        }

        thread.join();
    }
}