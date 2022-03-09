#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Button.h"

namespace Shitful
{
	constexpr float sqrt2 = 1.4142135623731f;
	// ����������ת��Ϊ�ַ���������ʾ
	std::string toString(sf::Keyboard::Key key);
	float toRadian(float degree);
	float toDegree(float radian);

	// ����������ԭ�����õ�ͼ������
	void centerOrigin(sf::Sprite& sprite);
	// ����������ԭ�����õ�ͼ������
	void centerOrigin(Animation& animation);
	// ����������ԭ�����õ�ͼ������
	void centerOrigin(sf::Text& text);

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
