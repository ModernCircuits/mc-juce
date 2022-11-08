#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/model: LottieModel(not_found.json)", "[lottie]")
{
    auto const cwd = juce::File::getCurrentWorkingDirectory();
    REQUIRE_THROWS(mc::LottieModel { cwd.getChildFile("test_data/lottie/not_found.json") });
}

TEST_CASE("lottie/model: LottieModel(bouncy_ball.json)", "[lottie]")
{
    auto const cwd   = juce::File::getCurrentWorkingDirectory();
    auto const model = mc::LottieModel { cwd.getChildFile("test_data/lottie/bouncy_ball.json") };

    REQUIRE(model.name() == "Bouncy Ball");
    REQUIRE(model.version() == "5.5.2");
    REQUIRE(model.inPoint() == 0.0);
    REQUIRE(model.outPoint() == 120.0);
    REQUIRE(model.width() == 512.0);
    REQUIRE(model.height() == 512.0);
    REQUIRE(model.framerate() == 60.0);

    auto const& layers = model.layers();
    REQUIRE(layers.size() == 1);

    auto const& layer = layers[0];
    REQUIRE(layer.name() == "Layer");
    REQUIRE(layer.inOutPoints()->in == 0.0);
    REQUIRE(layer.inOutPoints()->out == 120.0);

    auto const transform = layer.transform();
    REQUIRE(transform.has_value());
    REQUIRE(transform->anchor.x == 0.0);
    REQUIRE(transform->anchor.y == 0.0);
    REQUIRE(transform->position.x == 0.0);
    REQUIRE(transform->position.y == 0.0);
    REQUIRE(transform->scale.x == 100.0);
    REQUIRE(transform->scale.y == 100.0);

    auto const shapeLayer = mc::tryGetComponent<mc::LottieLayerShape>(layer.registry, layer.id);
    REQUIRE(shapeLayer.has_value());

    REQUIRE(shapeLayer->shapes.size() == 1);
    REQUIRE(shapeLayer->shapes[0].type() == mc::LottieShapeType::group);

    auto const& shape = shapeLayer->shapes[0];
    auto const group  = mc::tryGetComponent<mc::LottieShapeGroup>(shape.registry, shape.id);
    REQUIRE(group.has_value());
}

TEST_CASE("lottie/model: LottieModel(knob.json)", "[lottie]")
{
    auto const cwd   = juce::File::getCurrentWorkingDirectory();
    auto const model = mc::LottieModel { cwd.getChildFile("test_data/lottie/knob.json") };

    REQUIRE(model.name() == "Frame 2");
    REQUIRE(model.version() == "5.9.6");
    REQUIRE(model.inPoint() == 0.0);
    REQUIRE(model.outPoint() == 120.0);
    REQUIRE(model.framerate() == 60.0);
    REQUIRE(model.width() == 150.0);
    REQUIRE(model.height() == 150.0);

    auto const& layers = model.layers();
    REQUIRE(layers.size() == 10);
}