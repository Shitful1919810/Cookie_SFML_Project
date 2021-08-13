#pragma once
#include "StateStack.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
namespace Shitful
{

	class Game
	{
	public:
		Game();
		Game(const Game&) = delete;
		void run();
	private:

		void registerStates();

		void processInput();
		void update(sf::Time deltaTime);
		void render();
	private:
		TextureHolder			mTextures;
		FontHolder				mFonts;

		sf::RenderWindow mWindow;
		Player mPlayer;
		bool mIsPaused;

		sf::Time frameRate;
		float PlayerSpeed;

		MusicPlayer mMusic;
		SoundPlayer mSounds;
		StateStack mStateStack;
	};
}