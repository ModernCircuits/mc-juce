#pragma once

namespace mc {

template <typename T>
struct RingBuffer {
    using value_type = T;
    using size_type  = std::uint32_t;

    RingBuffer();
    explicit RingBuffer(size_type size);

    [[nodiscard]] auto empty() const noexcept -> bool;
    [[nodiscard]] auto size() const noexcept -> size_type;

    auto clear() -> void;
    auto resize(size_type size) -> void;

    auto push(T value) -> void;
    [[nodiscard]] auto operator[](size_type index) const noexcept -> float;

private:
    UniquePtr<T[]> _buffer { nullptr }; // NOLINT(modernize-avoid-c-arrays)
    size_type _size { 0 };
    size_type _writePosition { 0 };
};

template <typename T>
RingBuffer<T>::RingBuffer() : RingBuffer { 1 }
{
}

template <typename T>
RingBuffer<T>::RingBuffer(size_type size)
{
    resize(size);
}

template <typename T>
auto RingBuffer<T>::operator[](size_type index) const noexcept -> float
{
    auto const i = _writePosition + index;
    if (i < _size) { return _buffer[i]; }
    return _buffer[i - _size];
}

template <typename T>
auto RingBuffer<T>::clear() -> void
{
    ranges::fill(_buffer.get(), std::next(_buffer.get(), _size), T {});
}

template <typename T>
auto RingBuffer<T>::resize(size_type size) -> void
{
    _size   = size;
    _buffer = makeUnique<T[]>(size); // NOLINT(modernize-avoid-c-arrays)
    clear();
}

template <typename T>
auto RingBuffer<T>::size() const noexcept -> size_type
{
    return _size;
}

template <typename T>
auto RingBuffer<T>::empty() const noexcept -> bool
{
    return size() == 0;
}

template <typename T>
auto RingBuffer<T>::push(T value) -> void
{
    _buffer[_writePosition++] = value;
    if (_writePosition == _size) { _writePosition = 0; }
}
} // namespace mc
