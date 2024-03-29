#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace {
struct TestProcessor final : juce::AudioProcessor {
    explicit TestProcessor(juce::AudioProcessorValueTreeState::ParameterLayout parameters)
        : vts { *this, nullptr, "Test", std::move(parameters) }
    {
    }
    ~TestProcessor() override = default;

    auto getName() const -> const juce::String override { return "Test"; }

    auto prepareToPlay(double /*sampleRate*/, int /*samplesPerBlock*/) -> void override { }
    auto processBlock(juce::AudioBuffer<float>& /*buffer*/, juce::MidiBuffer& /*midiMessages*/) -> void override { }
    using juce::AudioProcessor::processBlock;
    auto releaseResources() -> void override { }

    auto isBusesLayoutSupported(BusesLayout const& /*layouts*/) const -> bool override { return true; }

    auto createEditor() -> juce::AudioProcessorEditor* override { return nullptr; }
    auto hasEditor() const -> bool override { return false; }

    auto acceptsMidi() const -> bool override { return false; }
    auto producesMidi() const -> bool override { return false; }
    auto isMidiEffect() const -> bool override { return false; }
    auto getTailLengthSeconds() const -> double override { return 0.0; }

    auto getNumPrograms() -> int override { return 0; }
    auto getCurrentProgram() -> int override { return 0; }
    void setCurrentProgram(int /*index*/) override { }
    auto getProgramName(int /*index*/) -> const juce::String override { return ""; }
    void changeProgramName(int /*index*/, juce::String const& /*newName*/) override { }

    auto getStateInformation(juce::MemoryBlock& /*destData*/) -> void override { }
    auto setStateInformation(void const* /*data*/, int /*size*/) -> void override { }

    juce::AudioProcessorValueTreeState vts;
};

auto makeTestProcessor()
{
    return TestProcessor { {
        mc::makeFloatParameter("test_float", "Float", juce::NormalisableRange { 0.0F, 1.0F, 0.01F }, 1.0F),
        mc::makeIntParameter("test_int", "Int", 0, 10, 0),
        mc::makeChoiceParameter("test_choice", "Choice", juce::StringArray { "1", "2", "3" }, 0),
        mc::makeBoolParameter("test_bool", "Bool", false),
    } };
}
} // namespace

TEST_CASE("audio_processors/parameter: getFloatParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getFloatParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getFloatParameter(test.vts, "test_float") != nullptr);
    REQUIRE(mc::getFloatParameter(test.vts, "test_int") == nullptr);
    REQUIRE(mc::getFloatParameter(test.vts, "test_choice") == nullptr);
    REQUIRE(mc::getFloatParameter(test.vts, "test_bool") == nullptr);
}

TEST_CASE("audio_processors/parameter: getChoiceParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getChoiceParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getChoiceParameter(test.vts, "test_choice") != nullptr);
    REQUIRE(mc::getChoiceParameter(test.vts, "test_float") == nullptr);
    REQUIRE(mc::getChoiceParameter(test.vts, "test_int") == nullptr);
    REQUIRE(mc::getChoiceParameter(test.vts, "test_bool") == nullptr);
}

TEST_CASE("audio_processors/parameter: getIntParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getIntParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getIntParameter(test.vts, "test_int") != nullptr);
    REQUIRE(mc::getIntParameter(test.vts, "test_choice") == nullptr);
    REQUIRE(mc::getIntParameter(test.vts, "test_float") == nullptr);
    REQUIRE(mc::getIntParameter(test.vts, "test_bool") == nullptr);
}

TEST_CASE("audio_processors/parameter: getBoolParameter", "[audio_processors]")
{
    auto empty = TestProcessor { {} };
    REQUIRE(mc::getBoolParameter(empty.vts, "Unkown") == nullptr);

    auto test = makeTestProcessor();
    REQUIRE(mc::getBoolParameter(test.vts, "test_bool") != nullptr);
    REQUIRE(mc::getBoolParameter(test.vts, "test_int") == nullptr);
    REQUIRE(mc::getBoolParameter(test.vts, "test_choice") == nullptr);
    REQUIRE(mc::getBoolParameter(test.vts, "test_float") == nullptr);
}

TEST_CASE("audio_processors/text_value_converter: ActiveTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::ActiveTextConverter const converter {};
        REQUIRE(converter("active") == Catch::Approx(1.0F));
        REQUIRE(converter("bypassed") == Catch::Approx(0.0F));
    }

    SECTION("float -> String")
    {
        mc::ActiveTextConverter const converter {};
        REQUIRE(converter(1.0F) == "active");
        REQUIRE(converter(0.0F) == "bypassed");
    }
}

TEST_CASE("audio_processors/text_value_converter: FrequencyTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter("10.00 Hz") == Catch::Approx(10.0F));
        REQUIRE(converter("10.00 kHz") == Catch::Approx(10000.0F));
    }

    SECTION("float -> String")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter(10.0F) == "10.00 Hz");
        REQUIRE(converter(10000.0F) == "10.00 kHz");
    }
}

TEST_CASE("audio_processors/text_value_converter: GainTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("0.0 db") == Catch::Approx(1.0F));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("1.0 db") == Catch::Approx(1.12202F));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("6.0 db") == Catch::Approx(1.99526F));
    }
}

TEST_CASE("audio_processors/text_value_converter: InvertPhaseTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter("Normal") == Catch::Approx(0.0F));
        REQUIRE(converter("Inverted") == Catch::Approx(1.0F));
    }

    SECTION("float -> String")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter(0.0F) == "Normal");
        REQUIRE(converter(1.0F) == "Inverted");
    }
}

TEST_CASE("audio_processors/text_value_converter: MillisecondsTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::MillisecondsTextConverter const converter {};
        REQUIRE(converter("100.0 ms") == Catch::Approx(100.0F));
        REQUIRE(converter("0.0 ms") == Catch::Approx(0.0F));
        REQUIRE(converter("14.3 ms") == Catch::Approx(14.3F));
    }

    SECTION("float -> String")
    {
        mc::MillisecondsTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.0 ms");
        REQUIRE(converter(1.0F) == "1.0 ms");
        REQUIRE(converter(14.3F) == "14.3 ms");
    }
}

TEST_CASE("audio_processors/text_value_converter: PercentTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::PercentTextConverter const converter {};
        REQUIRE(converter("100.0 %") == Catch::Approx(1.0F));
        REQUIRE(converter("0.0 %") == Catch::Approx(0.0F));
        REQUIRE(converter("14.3 %") == Catch::Approx(0.143F));
    }

    SECTION("float -> String")
    {
        mc::PercentTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.0 %");
        REQUIRE(converter(1.0F) == "100.0 %");
        REQUIRE(converter(0.143F) == "14.3 %");
    }
}

TEST_CASE("audio_processors/text_value_converter: QualityTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::QualityTextConverter const converter {};
        REQUIRE(converter("1.2") == Catch::Approx(1.2F));
        REQUIRE(converter("0.0") == Catch::Approx(0.0F));
    }

    SECTION("float -> String")
    {
        mc::QualityTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1.0");
        REQUIRE(converter(0.24F) == "0.2");
        REQUIRE(converter(9.99F) == "10.0");
    }
}

TEST_CASE("audio_processors/text_value_converter: RatioOrGateTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::RatioOrGateTextConverter const converter {};
        REQUIRE(converter("100:1") == Catch::Approx(100.0F));
        REQUIRE(converter("1:1") == Catch::Approx(1.0F));
        REQUIRE(converter("14:1") == Catch::Approx(14.F));
        REQUIRE(converter("9.9:1") == Catch::Approx(9.9F));
    }

    SECTION("float -> String")
    {
        mc::RatioOrGateTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1.0:1");
        REQUIRE(converter(11.0F) == "11:1");
        REQUIRE(converter(9.F) == "9.0:1");
        REQUIRE(converter(21.F) == "Gate");
    }
}

TEST_CASE("audio_processors/text_value_converter: RatioOrLimiterTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::RatioOrLimiterTextConverter const converter {};
        REQUIRE(converter("1:100") == Catch::Approx(100.0F));
        REQUIRE(converter("1:1.0") == Catch::Approx(1.0F));
        REQUIRE(converter("1:14") == Catch::Approx(14.F));
        REQUIRE(converter("1:9.9") == Catch::Approx(9.9F));
    }

    SECTION("float -> String")
    {
        mc::RatioOrLimiterTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1:1.0");
        REQUIRE(converter(11.0F) == "1:11");
        REQUIRE(converter(9.F) == "1:9.0");
        REQUIRE(converter(30.1F) == "Limiter");
    }
}

TEST_CASE("audio_processors/text_value_converter: SecondsTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::SecondsTextConverter const converter {};
        REQUIRE(converter("100.0 s") == Catch::Approx(100.0F));
        REQUIRE(converter("0.00 s") == Catch::Approx(0.0F));
        REQUIRE(converter("14.30 s") == Catch::Approx(14.3F));
    }

    SECTION("float -> String")
    {
        mc::SecondsTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.00 s");
        REQUIRE(converter(1.0F) == "1.00 s");
        REQUIRE(converter(14.3F) == "14.30 s");
    }
}

TEST_CASE("audio_processors/parameter: TrueFalseTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::TrueFalseTextConverter const converter {};
        REQUIRE(converter("true") > 0.5F);
        REQUIRE(converter("false") < 0.5F);
    }

    SECTION("float -> String")
    {
        mc::TrueFalseTextConverter const converter {};
        REQUIRE(converter(1.0F) == "true");
        REQUIRE(converter(0.0F) == "false");
    }
}
