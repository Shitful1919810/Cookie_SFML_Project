#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Button.h"

namespace Shitful
{
	constexpr float sqrt2 = 1.4142135623f;
	constexpr float eps = 6e-4f;
	// ����������ת��Ϊ�ַ���������ʾ
	std::string toString(sf::Keyboard::Key key);
	float toRadian(float degree);
	float toDegree(float radian);


	template<typename T>
	// ����������ԭ�����õ�ͼ������
	void centerOrigin(T& element)
	{
		sf::FloatRect bounds = element.getLocalBounds();
		element.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	float length(sf::Vector2f vector);
	// ��õ�λ��������
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
