#pragma once
#include "Scene.h"
#include "ResourceIdentifiers.h"


namespace Shitful
{
	class SoundPlayer;

	class SoundNode : public SceneNode
	{
	public:
		explicit SoundNode(SoundPlayer& player);
		void playSound(SoundEffectID sound, sf::Vector2f position);
		virtual unsigned int getCategory() const;
	private:
		SoundPlayer& mSounds;
	};

}