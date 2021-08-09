#pragma once
#include <SFML/System/Vector2.hpp>
namespace Shitful
{
	template<typename T>
	// 将向量lhs的模长与rhs进行比较
	bool operator>(const sf::Vector2<T>& lhs, float rhs)
	{
		return lhs.x * lhs.x + lhs.y * lhs.y > rhs * rhs;
	}

	template<typename T>
	// 将向量lhs的模长与rhs进行比较
	bool operator<(const sf::Vector2<T>& lhs, float rhs)
	{
		return lhs.x * lhs.x + lhs.y * lhs.y < rhs* rhs;
	}
}