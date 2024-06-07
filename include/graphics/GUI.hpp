#pragma once

#include "FrameRate.hpp"
#include "SFML/Graphics.hpp"
#include <concepts>
#include <type_traits>

namespace LY {
template <typename... T>
concept AtLeastOne = requires(T... elems) { sizeof...(elems) > 0; };

template <typename... T>
concept IsDrawable = requires(T... elems) { (std::derived_from<decltype(elems), sf::Drawable> && ...); };

template <typename... T>
concept IsIterableOfDrawable = requires(T... elems) { (std::derived_from<typename decltype(elems)::value_type, sf::Drawable> && ...); };

template <typename... T>
concept IsIterableOfIterableOfDrawable = requires(T... elems) { (std::derived_from<typename decltype(elems)::value_type::value_type, sf::Drawable> && ...); };

using Point = std::pair<double, double>;

using namespace LY::conversions;
class GUI {
private:
	static inline constexpr auto FPS = 60_fps;

public:
	GUI(void);

	auto run(void) -> void;

	template <typename... ElemType>
		requires AtLeastOne<ElemType...> && (IsDrawable<ElemType...> || IsIterableOfDrawable<ElemType...> || IsIterableOfIterableOfDrawable<ElemType...>)
	auto update(const ElemType&... element) -> void;


private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;

	template <typename ElemType>
		requires IsDrawable<ElemType> || IsIterableOfDrawable<ElemType> || IsIterableOfIterableOfDrawable<ElemType>
	auto drawElement(const ElemType& element) -> void;

};

template <typename ElemType>
	requires IsDrawable<ElemType> || IsIterableOfDrawable<ElemType> || IsIterableOfIterableOfDrawable<ElemType>
auto GUI::drawElement(const ElemType& element) -> void {
	if constexpr (IsIterableOfIterableOfDrawable<ElemType>)
		for (const auto& container : element)
			for (const auto& entity : container)
				window.draw(entity);

	else if constexpr (IsIterableOfDrawable<ElemType>)
		for (const auto& entity : element)
			window.draw(entity);

	else
		window.draw(element);
}

template <typename... ElemType>
	requires AtLeastOne<ElemType...> && (IsDrawable<ElemType...> || IsIterableOfDrawable<ElemType...> || IsIterableOfIterableOfDrawable<ElemType...>)
auto GUI::update(const ElemType&... element) -> void {
	clock.restart();

	switch (window.pollEvent(event), event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
	}

	window.clear();
	(drawElement(element), ...);
	window.display();

	using namespace LY::conversions;
	sf::sleep(FPS - clock.getElapsedTime());
}
}
