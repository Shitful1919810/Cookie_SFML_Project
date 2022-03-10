#include "Entity.h"
Shitful::Entity::Entity(int hitpoints) : mHitpoints(hitpoints), mHitbox(nullptr)
{
}
void Shitful::Entity::repair(int points)
{
	assert(points > 0);

	mHitpoints += points;
}
void Shitful::Entity::damage(int points)
{
	assert(points > 0);

	mHitpoints -= points;
}
void Shitful::Entity::destroy()
{
	mHitpoints = 0;
}
int Shitful::Entity::getHitpoints() const
{
	return mHitpoints;
}
bool Shitful::Entity::isDestroyed() const
{
	return mHitpoints <= 0;
}
void Shitful::Entity::remove()
{
	destroy();
}
sf::FloatRect Shitful::Entity::getDisplayBound()
{
	return sf::FloatRect();
}
void Shitful::Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}
void Shitful::Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}
void Shitful::Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}
void Shitful::Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}
sf::Vector2f Shitful::Entity::getVelocity() const
{
	return mVelocity;
}

int Shitful::Entity::getHitPoints() const
{
	return mHitpoints;
}

sf::Vector2i Shitful::Entity::getGridCoord(int gridSize)
{
	if (mHitbox)
	{
		return sf::Vector2i(
			static_cast<int>(this->mHitbox->getWorldPosition().x) / gridSize,
			static_cast<int>(this->mHitbox->getWorldPosition().y) / gridSize
		);
	}
	return sf::Vector2i(
		static_cast<int>(this->getWorldPosition().x) / gridSize,
		static_cast<int>(this->getWorldPosition().y) / gridSize
	);
}

void Shitful::Entity::stopVelocity()
{
	setVelocity({ 0.f,0.f });
}

void Shitful::Entity::stopVelocityX()
{
	setVelocity({ 0.f,getVelocity().y });
}

void Shitful::Entity::stopVelocityY()
{
	setVelocity({ getVelocity().x,0.f });
}

const Shitful::HitboxModule* Shitful::Entity::getHitbox()
{
	return mHitbox.get();
}


void Shitful::Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	move(mVelocity * dt.asSeconds());
}
