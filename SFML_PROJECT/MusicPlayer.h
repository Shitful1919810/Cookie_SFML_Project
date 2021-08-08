#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include <map>
#include <string>
#include "Command.h"
#include "ResourceIdentifiers.h"
namespace Shitful
{
	enum class MusicID
	{
		MenuTheme,
		MissionTheme,
	};

	class MusicPlayer : private sf::NonCopyable
	{
	public:
		MusicPlayer();
		void play(MusicID theme);
		void stop();
		void setPaused(bool paused);
		void setVolume(float volume);
	private:
		sf::Music mMusic;
		std::map<MusicID, std::string> mFilenames;
		float mVolume;
	};
}