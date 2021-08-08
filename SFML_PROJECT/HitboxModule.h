#pragma once
#include <SFML/System.hpp>
#include <memory>
#include "Scene.h"
namespace Shitful
{
	class Entity;

	class HitboxModule : public sf::Transformable
	{
	public:
		using Ptr = std::unique_ptr<HitboxModule>;
		HitboxModule(Entity& master, sf::Vector2f size);
		HitboxModule(Entity& master);
		sf::FloatRect getHitboxRect() const;
		sf::Vector2f getWorldPosition() const;
		sf::FloatRect getNextHitbox(sf::Time dt) const;
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::FloatRect mHitbox;
		sf::RectangleShape mShape;

		Entity& mMaster;
	};
}