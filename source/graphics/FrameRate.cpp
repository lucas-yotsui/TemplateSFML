#include "graphics/FrameRate.hpp"

namespace LY {
FrameRate::operator sf::Time(void) const { return sf::microseconds(microseconds); }
}
