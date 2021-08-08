#include "MusicPlayer.h"

Shitful::MusicPlayer::MusicPlayer()
	: mMusic()
	, mFilenames()
	, mVolume(25.f)
{
	mFilenames[MusicID::MenuTheme] = "Music/Title.ogg";
	mFilenames[MusicID::MissionTheme] = "Music/TestScene.ogg";
}

void Shitful::MusicPlayer::play(MusicID theme)
{
	std::string filename = mFilenames[theme];
	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void Shitful::MusicPlayer::stop()
{
	mMusic.stop();
}

void Shitful::MusicPlayer::setPaused(bool paused)
{
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
}

void Shitful::MusicPlayer::setVolume(float volume)
{
	mVolume = volume;
}
