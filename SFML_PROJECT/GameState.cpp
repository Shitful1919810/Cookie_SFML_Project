#include "GameState.h"

Shitful::GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.fonts, *context.sounds)
	, mPlayer(*context.player)
{
	mPlayer.setChapterStatus(Player::ChapterStatus::Running);
	try
	{
		context.music->play(MusicID::MissionTheme);
	}
	catch (std::exception& e)
	{
		printf("%s\n", e.what());
		printf("%s\n", "为回避版权诉讼，已移除音乐文件，请用户自己将合适的文件(.ogg)重命名后放入Music文件夹");
	}
}

void Shitful::GameState::draw()
{
	mWorld.draw();
}

bool Shitful::GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	if (!mWorld.hasAlivePlayer())
	{
		mPlayer.setChapterStatus(Player::ChapterStatus::Failure);
		requestStackPush(StateID::GameOver);
	}
	else if (mWorld.hasPlayerReachedEnd())
	{
		mPlayer.setChapterStatus(Player::ChapterStatus::Success);
		requestStackPush(StateID::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool Shitful::GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(StateID::Pause);

	return true;
}
