#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Button.h"

namespace Shitful
{
	constexpr float sqrt2 = 1.4142135623f;
	constexpr float eps = 6e-4f;
	// 将按键名称转化为字符串用于显示
	std::string toString(sf::Keyboard::Key key);
	float toRadian(float degree);
	float toDegree(float radian);


	template<typename T>
	// 将本地坐标原点设置到图象中心
	void centerOrigin(T& element)
	{
		sf::FloatRect bounds = element.getLocalBounds();
		element.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	float length(sf::Vector2f vector);
	// 获得单位方向向量
	sf::Vector2f unitVector(sf::Vector2f vector);
	int randomInt(int exclusiveMax);

	template<typename T>
	//			^  ret
	// upper	|               /------------- 
	//			|              /
	//			|             /
	//			|            /
	//			|           /
	// lower	|  --------/
	//			|
	//			|
	//			_______________________________>  x
	T bound(T x, T lower, T upper)
	{
		if (x < lower)
			return lower;
		if (x > upper)
			return upper;
		return x;
	}
}
