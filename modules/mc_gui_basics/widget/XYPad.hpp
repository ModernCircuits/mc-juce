#ifndef MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP
#define MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP

namespace mc {
struct XYPad : juce::Component {
    enum ColourIds {
        backgroundColor  = 0x1330101,
        outlineColor     = 0x1330102,
        thumbNormalColor = 0x1330103,
        thumbOverColor   = 0x1330104,
        thumbDownColor   = 0x1330105,
    };

    struct Listener {
        virtual ~Listener() = default;

        virtual auto xypadChanged(XYPad* pad, juce::Point<float> position) -> void = 0;
        virtual auto xypadDragStarted(XYPad* pad) -> void                          = 0;
        virtual auto xypadDragEnded(XYPad* pad) -> void                            = 0;
    };

    struct LookAndFeelMethods {
        virtual ~LookAndFeelMethods() = default;

        virtual auto drawXYPad(juce::Graphics& g, juce::Rectangle<float> thumbBounds, XYPad& pad) -> void = 0;
        virtual auto getXYPadThumbDiameter(XYPad& pad) -> int                                             = 0;
    };

    explicit XYPad(juce::String const& name = {});
    ~XYPad() override = default;

    MC_NODISCARD auto getValueX() const noexcept -> float;
    MC_NODISCARD auto getValueY() const noexcept -> float;
    auto setValueX(float x) -> void;
    auto setValueY(float y) -> void;

    MC_NODISCARD auto getNormalizedX() const noexcept -> float;
    MC_NODISCARD auto getNormalizedY() const noexcept -> float;
    auto setNormalizedX(float x) -> void;
    auto setNormalizedY(float y) -> void;

    MC_NODISCARD auto getXRange() const noexcept -> juce::NormalisableRange<float>;
    MC_NODISCARD auto getYRange() const noexcept -> juce::NormalisableRange<float>;
    auto setXRange(juce::NormalisableRange<float> const& newRange) -> void;
    auto setYRange(juce::NormalisableRange<float> const& newRange) -> void;

    MC_NODISCARD auto getDirectionX() const noexcept -> bool;
    MC_NODISCARD auto getDirectionY() const noexcept -> bool;
    auto setDirectionX(bool startShouldBeOnLeft) -> void;
    auto setDirectionY(bool startShouldBeOnTop) -> void;

    MC_NODISCARD auto isOverThumb() const noexcept -> bool;
    MC_NODISCARD auto isDragging() const noexcept -> bool;

    auto addListener(Listener* listener) -> void { listeners_.add(listener); }
    auto removeListener(Listener* listener) -> void { listeners_.remove(listener); }

private:
    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    auto mouseMove(juce::MouseEvent const& event) -> void override;
    auto mouseDown(juce::MouseEvent const& event) -> void override;
    auto mouseUp(juce::MouseEvent const& event) -> void override;
    auto mouseDrag(juce::MouseEvent const& event) -> void override;

    MC_NODISCARD auto getValueFromPixel(int pixel, bool isXAxis) const -> float;
    MC_NODISCARD auto getPixelFromNormalizedValue(float value, bool x) const -> int;
    MC_NODISCARD auto thumbHitTest(juce::MouseEvent const& event) const -> bool;

    auto updatePosition() -> void;

    auto startDragging() -> void;
    auto stopDragging() -> void;

    juce::Point<float> normalizedValues_ {};
    juce::NormalisableRange<float> xRange_ {};
    juce::NormalisableRange<float> yRange_ {};
    bool startShouldBeOnLeft_ { true };
    bool startShouldBeOnTop_ { true };

    juce::Rectangle<int> thumb_ { 0, 0, 8, 8 };
    juce::Colour thumbColor_ { juce::Colours::grey };
    juce::Rectangle<int> bounds_ {};
    bool isDragging_ { false };
    bool isOverThumb_ { false };

    juce::ListenerList<Listener> listeners_ {};

    JUCE_LEAK_DETECTOR(XYPad) // NOLINT
};

} // namespace mc

#endif // MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP
