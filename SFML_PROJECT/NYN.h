#pragma once
#include "Entity.h"
#include "TextNode.h"
#include "Animation.h"
#include "SoundPlayer.h"
#include "ResourceIdentifiers.h"

namespace Shitful
{
	class Cookie : public Entity
	{
	public:
		enum EntityType
		{
			Player_ID,
			Enemy_ID,
			SubEnemy_ID,
			TypeCount
		};

		Cookie(EntityType type, const TextureHolder& textures, const FontHolder& fonts);
		virtual Receiver getCategory() const;
		virtual bool isMarkedForRemoval() const;
		virtual void remove();
		bool isAllied() const;
		float getMaxSpeed() const;
		sf::Vector2f getAcceleration() const;
		float getMaxAcceleration() const;
		virtual sf::FloatRect getBoundingRect() const;
		void setAcceleration(sf::Vector2f acceleration);
		void setDeacceleration(float deacceleration);
		void playLocalSound(CommandQueue& commands, SoundEffectID effect);

		void applyAcceleration(sf::Time dt);
	private:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		EntityType mType;
		sf::Sprite mSprite;
		float mTravelledDistance;

		sf::Vector2f mAcceleration;
		float mDeacceleration;

		sf::Time mFireCountdown;
		bool mIsMarkedForRemoval;

	};
}

