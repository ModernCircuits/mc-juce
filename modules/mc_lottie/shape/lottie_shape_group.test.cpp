#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeGroup::parse", "[lottie]")
{
    auto const* src = R"(
        {
          "ty": "gr",
          "nm": "Ellipse Group",
          "it": [
            {
              "ty": "el",
              "nm": "Ellipse",
              "p": {
                "a": 0,
                "k": [204, 169]
              },
              "s": {
                "a": 0,
                "k": [153, 153]
              }
            },
            {
              "ty": "fl",
              "nm": "Fill",
              "o": {
                "a": 0,
                "k": 100
              },
              "c": {
                "a": 0,
                "k": [0.71, 0.192, 0.278]
              },
              "r": 1
            },
            {
              "ty": "tr",
              "a": {
                "a": 0,
                "k": [204, 169]
              },
              "p": {
                "a": 1,
                "k": [
                  {
                    "t": 0,
                    "s": [235, 106],
                    "h": 0,
                    "o": {
                      "x": [0.333],
                      "y": [0]
                    },
                    "i": {
                      "x": [1],
                      "y": [1]
                    }
                  },
                  {
                    "t": 60,
                    "s": [265, 441],
                    "h": 0,
                    "o": {
                      "x": [0],
                      "y": [0]
                    },
                    "i": {
                      "x": [0.667],
                      "y": [1]
                    }
                  },
                  {
                    "t": 120,
                    "s": [235, 106]
                  }
                ]
              },
              "s": {
                "a": 1,
                "k": [
                  {
                    "t": 55,
                    "s": [100, 100],
                    "h": 0,
                    "o": {
                      "x": [0],
                      "y": [0]
                    },
                    "i": {
                      "x": [1],
                      "y": [1]
                    }
                  },
                  {
                    "t": 60,
                    "s": [136, 59],
                    "h": 0,
                    "o": {
                      "x": [0],
                      "y": [0]
                    },
                    "i": {
                      "x": [1],
                      "y": [1]
                    }
                  },
                  {
                    "t": 65,
                    "s": [100, 100]
                  }
                ]
              },
              "r": {
                "a": 0,
                "k": 0
              },
              "o": {
                "a": 0,
                "k": 100
              }
            }
          ]
        }
    )";

    auto reg         = entt::registry {};
    auto const obj   = juce::JSON::parse(src);
    auto const shape = mc::LottieShape2::parse(reg, obj);
    REQUIRE(shape.type() == mc::LottieShapeType::group);
    REQUIRE(shape.name() == "Ellipse Group");

    auto const group = mc::tryGetComponent<mc::LottieShapeGroup2>(reg, shape.id);
    REQUIRE(group->shapes.size() == 3);
}
