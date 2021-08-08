#include "NYN.h"
#include "DataTables.h"
#include "Utilities.h"
#include "VectorHelper.h"

namespace
{
	const std::vector<Shitful::EntityData> Table = Shitful::initializeAircraftData();
}

Shitful::Cookie::Cookie(EntityType type, const TextureHolder& textures, const FontHolder& fonts)
	: Entity(Table[type].hitpoints)
	, mType(type)
	, mSprite(textures.get(Table[type].texture)/*, Table[type].textureRect*/)
	, mIsMarkedForRemoval(false)
	, mAcceleration()
	, mDeacceleration(Table[type].deceleration)
{
	centerOrigin(mSprite);
	mHitbox.reset(new HitboxModule(*this));
}

Shitful::Receiver Shitful::Cookie::getCategory() const
{
	if (mType == EntityType::Player_ID)
		return Shitful::Category::Player;
	else
		return Shitful::Category::Enemy;
}		

bool Shitful::Cookie::isMarkedForRemoval() const
{
	return mIsMarkedForRemoval;
}

void Shitful::Cookie::remove()
{
	Entity::remove();
}

bool Shitful::Cookie::isAllied() const
{
	return mType == Player_ID;
}

float Shitful::Cookie::getMaxSpeed() const
{
	return Table[mType].speed;
}

sf::Vector2f Shitful::Cookie::getAcceleration() const
{
	return mAcceleration;
}

float Shitful::Cookie::getMaxAcceleration() const
{
	return Table[mType].acceleration;
}

sf::FloatRect Shitful::Cookie::getBoundingRect() const
{
	return mSprite.getGlobalBounds();
}

void Shitful::Cookie::setAcceleration(sf::Vector2f acceleration)
{
	mAcceleration = acceleration;
}

void Shitful::Cookie::setDeacceleration(float deacceleration)
{
	mDeacceleration = deacceleration;
}

void Shitful::Cookie::playLocalSound(CommandQueue& commands, SoundEffectID effect)
{
}

void Shitful::Cookie::applyAcceleration(sf::Time dt)
{
	float factor = 1.f;
	sf::Vector2f velocity = getVelocity();
	if (mAcceleration.x != 0 && mAcceleration.y != 0)
		factor = sqrt2;										// 对角线正规化
	velocity += mAcceleration * dt.asSeconds() / factor;
	if (velocity.x > 0.f) //Check for positive x
	{
		velocity.x -= mDeacceleration * dt.asSeconds() / factor;
		velocity.x = std::max(0.f, velocity.x);
	}
	else if (velocity.x < 0.f) //Check for negative x
	{
		velocity.x += mDeacceleration * dt.asSeconds() / factor;
		velocity.x = std::min(0.f, velocity.x);
	}
	if (velocity.y > 0.f) //Check for positive y
	{
		velocity.y -= mDeacceleration * dt.asSeconds() / factor;
		velocity.y = std::max(0.f, velocity.y);
	}
	else if (velocity.y < 0.f) //Check for negative y
	{
		velocity.y += mDeacceleration * dt.asSeconds() / factor;
		velocity.y = std::min(0.f, velocity.y);
	}

	setVelocity(velocity);
}


void Shitful::Cookie::updateCurrent(sf::Time dt, CommandQueue& commands)
{

	if (isDestroyed())
	{
		return;
	}
	sf::Vector2f velocity = getVelocity();
	if (velocity > getMaxSpeed())
		setVelocity(unitVector(velocity) * getMaxSpeed());
	Entity::updateCurrent(dt, commands);

}


void Shitful::Cookie::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
	mHitbox->drawCurrent(target, states);
}
