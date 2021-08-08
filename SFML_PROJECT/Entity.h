#pragma once
#include <SFML/System/Vector2.hpp>
#include "Command.h"
#include "Scene.h"
#include "HitboxModule.h"

namespace Shitful
{
	class Entity : public SceneNode
	{
	public:
		explicit Entity(int hitpoints);

		void repair(int points);
		void damage(int points);
		void destroy();
		int getHitpoints() const;
		virtual bool isDestroyed() const;
		virtual void remove();

		void setVelocity(sf::Vector2f velocity);
		void setVelocity(float vx, float vy);
		void accelerate(sf::Vector2f velocity);
		void accelerate(float vx, float vy);
		sf::Vector2f getVelocity() const;
		int getHitPoints() const;
		sf::Vector2i getGridCoord(int gridSize);
		void stopVelocity();
		void stopVelocityX();
		void stopVelocityY();

		const HitboxModule* getHitbox();

	private:
		int mHitpoints;
		sf::Vector2f mVelocity;
	protected:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	protected:
		HitboxModule::Ptr mHitbox;
	};

}