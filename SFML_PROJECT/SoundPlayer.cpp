#include <SFML/Audio/Listener.hpp>
#include "SoundPlayer.h"

namespace
{
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

Shitful::SoundPlayer::SoundPlayer()
	: mSoundBuffers()
	, mSounds()
{
	mSoundBuffers.load(SoundEffectID::Button, "Sound/PJP.wav");
}

void Shitful::SoundPlayer::play(SoundEffectID effect)
{
	/*
	mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
	mSounds.back().play();*/
	play(effect, getListenerPosition());
}

void Shitful::SoundPlayer::play(SoundEffectID effect, sf::Vector2f position)
{
	mSounds.push_back(sf::Sound());
	sf::Sound& sound = mSounds.back();
	sound.setBuffer(mSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);
	sound.play();
}

void Shitful::SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
}

void Shitful::SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f Shitful::SoundPlayer::getListenerPosition() const
{
	return sf::Vector2f();
}
