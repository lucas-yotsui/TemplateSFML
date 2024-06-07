#include "graphics/GUI.hpp"
#include "SFML/Graphics/CircleShape.hpp"

namespace LY {
GUI::GUI(void) : window(sf::VideoMode::getDesktopMode(), "KNN algorithm") {}

auto GUI::run(void) -> void {
	std::vector<sf::CircleShape> circles1 = { sf::CircleShape(10), sf::CircleShape(10), sf::CircleShape(10), sf::CircleShape(10) };
	for (unsigned short i = 0; i < circles1.size(); i++) {
		circles1[i].setPosition(i * 100, i * 100);
	};

	std::vector<sf::CircleShape> circles2 = { sf::CircleShape(10), sf::CircleShape(10), sf::CircleShape(10), sf::CircleShape(10) };
	for (unsigned short i = 0; i < circles2.size(); i++) {
		circles2[i].setPosition(i * 100, (i * 100) + 400);
	};

	auto circle1 = sf::CircleShape(10);
	circle1.setPosition(400 + 100, 100);
	auto circle2 = sf::CircleShape(10);
	circle2.setPosition(400 + 200, 200);
	auto circle3 = sf::CircleShape(10);
	circle3.setPosition(400 + 300, 300);
	auto circle4 = sf::CircleShape(10);
	circle4.setPosition(400 + 400, 400);

	while (window.isOpen()) {
		update(circles1, circle1, circle2);
	}
}

auto GUI::convertToSFMLCoord(const Point& cartesian) const -> const Point {
	return { cartesian.first + MARGIN, (window.getSize().y - cartesian.second) - MARGIN };
}

}
