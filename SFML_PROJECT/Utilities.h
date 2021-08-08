#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Button.h"

namespace Shitful
{
	constexpr float sqrt2 = 1.4142135623731f;
	std::string toString(sf::Keyboard::Key key);
	float toRadian(float degree);
	float toDegree(float radian);
	void centerOrigin(sf::Sprite& sprite);
	void centerOrigin(Animation& animation);
	void centerOrigin(sf::Text& text);

	float length(sf::Vector2f vector);
	sf::Vector2f unitVector(sf::Vector2f vector);
	int randomInt(int exclusiveMax);

	template<typename T>
	T bound(T x, T lower, T upper)	// if lower<=x<=upper return x ,else return lower or upper
	{
		if (x < lower)
			return lower;
		if (x > upper)
			return upper;
		return x;
	}
}
