#pragma once
#include "Command.h"
#include "NYN.h"
namespace Shitful
{
	struct PlayerMover			// ���ڼ�һ��Command�ĳ�ʼ��
	{
		PlayerMover(float vx, float vy) : ratio(vx, vy)
		{
		}
		PlayerMover(sf::Vector2f speed) : ratio(speed)
		{
		}
		void operator() (SceneNode& node, sf::Time dt) const
		{
			Cookie& entity = static_cast<Cookie&>(node);
			entity.setAcceleration(entity.getAcceleration() + entity.getMaxAcceleration() * ratio);
		}
		sf::Vector2f ratio;
	};
}