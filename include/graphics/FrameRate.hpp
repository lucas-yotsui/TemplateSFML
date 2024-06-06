#pragma once
#include "SFML/System/Time.hpp"

namespace LY {
class FrameRate {
public:
	// Constexpr constructor for compile time creation of objects 🏎️ 💨
	constexpr FrameRate(unsigned long long fps);
	// All my homies hate them copy constructors 😤
	FrameRate(FrameRate&) = delete;
	// Move constructors are cool though 🫡
	FrameRate(FrameRate&&) = default;

	// Cast to a sf::Time to use in sleep function
	operator sf::Time(void) const;

private:
	const unsigned long long microseconds;
};

constexpr FrameRate::FrameRate(unsigned long long fps) : microseconds(1.f / (double)fps) {}

namespace conversions {
constexpr auto operator""_fps(unsigned long long value) -> FrameRate {
	return FrameRate(value);
}
}
}
