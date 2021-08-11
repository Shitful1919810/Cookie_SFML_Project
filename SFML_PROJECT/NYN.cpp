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
	, mWalkingAnimation(textures.get(TextureID::PlayerWalking))
	, mPattern(MovingPattern::Idling)
	, mPatternSwitcher(mSprite)
{
	mWalkingAnimation.setFrameSize(sf::Vector2i(120, 166));
	mWalkingAnimation.setNumFrames(4);
	mWalkingAnimation.setDuration(sf::seconds(1));
	mWalkingAnimation.setRepeating(true);
	centerOrigin(mSprite);
	centerOrigin(mWalkingAnimation);
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

	// 模拟摩擦力
	if (velocity.x > 0.f)
	{
		velocity.x -= mDeacceleration * dt.asSeconds() / factor;
		velocity.x = std::max(0.f, velocity.x);
	}
	else if (velocity.x < 0.f)
	{
		velocity.x += mDeacceleration * dt.asSeconds() / factor;
		velocity.x = std::min(0.f, velocity.x);
	}
	if (velocity.y > 0.f)
	{
		velocity.y -= mDeacceleration * dt.asSeconds() / factor;
		velocity.y = std::max(0.f, velocity.y);
	}
	else if (velocity.y < 0.f)
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
	// 确保速率不超过规定限度
	if (velocity > getMaxSpeed())
		setVelocity(unitVector(velocity) * getMaxSpeed());
	Entity::updateCurrent(dt, commands);
	updatePattern(dt);
}


void Shitful::Cookie::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(mSprite, states);
	target.draw(mPatternSwitcher.getDrawable(), states);
#ifndef NDEBUG
	mHitbox->drawCurrent(target, states);
#endif // NDEBUG
}

void Shitful::Cookie::updatePattern(sf::Time dt)
{
	sf::Vector2f velocity = getVelocity();


	if (velocity.x != 0.f || velocity.y != 0.f)
	{
		if (mPattern != MovingPattern::Walking)
		{
			mWalkingAnimation.restart();
			mPattern = MovingPattern::Walking;
			mPatternSwitcher.switchTo(mWalkingAnimation);
		}
	}
	else
	{
		if (mPattern != MovingPattern::Idling)
		{
			mPattern = MovingPattern::Idling;
			mPatternSwitcher.switchTo(mSprite);

		}
	}

	if (velocity.x > 0.f)
		//mPatternSwitcher.getTransformable().setScale(1.f, 1.f);
		setScale(1.f, 1.f);
	if (velocity.x < 0.f)
		//mPatternSwitcher.getTransformable().setScale(-1.f, 1.f);
		setScale(-1.f, 1.f);

	switch (mPattern)
	{
	case MovingPattern::Idling:
		break;
	case MovingPattern::Walking:
		mWalkingAnimation.update(dt);
		break;
	}
}
