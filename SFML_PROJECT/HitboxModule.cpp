#include "HitboxModule.h"
#include "Entity.h"
Shitful::HitboxModule::HitboxModule(Entity& master, sf::Vector2f size) 
	: mMaster(master)
	, mHitbox()
	, mShape(size)
{
	mShape.setPosition(getPosition() - 0.5f * size);
	mShape.setOutlineColor(sf::Color::Green);
	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineThickness(1.f);
	mHitbox = sf::FloatRect(getPosition() - 0.5f * size, size);
	setPosition(master.getPosition());

}

Shitful::HitboxModule::HitboxModule(Entity& master)
	: HitboxModule(master
		, { master.getBoundingRect().width / 2.f,master.getBoundingRect().height / 2.f })
{
}

sf::FloatRect Shitful::HitboxModule::getHitboxRect() const
{
	sf::Vector2f masterPosition = mMaster.getWorldPosition();
	return { masterPosition.x + mHitbox.left, masterPosition.y + mHitbox.top, mHitbox.width, mHitbox.height };
}

sf::Vector2f Shitful::HitboxModule::getWorldPosition() const
{
	return mMaster.getWorldPosition();
}

sf::FloatRect Shitful::HitboxModule::getNextHitbox(sf::Time dt) const
{
	sf::Vector2f masterPosition = mMaster.getWorldPosition();
	return { masterPosition.x + mHitbox.left + mMaster.getVelocity().x * dt.asSeconds(), masterPosition.y + mHitbox.top + mMaster.getVelocity().y * dt.asSeconds()
		, mHitbox.width, mHitbox.height };
}

void Shitful::HitboxModule::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mShape, states);

}
