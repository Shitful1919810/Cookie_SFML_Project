#include "HitboxModule.h"
#include "Entity.h"
Shitful::HitboxModule::HitboxModule(Entity& master, sf::Vector2f size) 
	: mMaster(master)
	, mHitbox()
	, mShape(size)
{
	mShape.setPosition(-0.5f * size);
	mShape.setOutlineColor(sf::Color::Green);
	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineThickness(3.f);
	mHitbox = sf::FloatRect(-0.5f * size, size);

}

Shitful::HitboxModule::HitboxModule(Entity& master)
	: HitboxModule(master
		, { master.getDisplayBound().width / 2.f,master.getDisplayBound().height / 2.f})
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
