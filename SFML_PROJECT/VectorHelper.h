#pragma once
#include <SFML/System/Vector2.hpp>
namespace Shitful
{
	template<typename T>
	// ������lhs��ģ����rhs���бȽ�
	bool operator>(const sf::Vector2<T>& lhs, float rhs)
	{
		return lhs.x * lhs.x + lhs.y * lhs.y > rhs * rhs;
	}

	template<typename T>
	// ������lhs��ģ����rhs���бȽ�
	bool operator<(const sf::Vector2<T>& lhs, float rhs)
	{
		return lhs.x * lhs.x + lhs.y * lhs.y < rhs* rhs;
	}
}