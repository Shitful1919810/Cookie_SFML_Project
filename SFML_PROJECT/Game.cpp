#include "Game.h"

#include "GameState.h"
#include "TitleState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "SettingsState.h"
#include "GameOverState.h"

Shitful::Game::Game()
	: mWindow(sf::VideoMode(1280, 720), "SFML Application", sf::Style::Close)
	, mTextures()
	, mFonts()
	, mPlayer()
	, mMusic()
	, mSounds()
	, mIsPaused(false)
	, PlayerSpeed(250.0f)
	, frameRate(sf::seconds(1.0f / 144.0f))
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSounds))
	//, mWorld(mWindow)
{
	mFonts.load(FontID::Main, "kenvector_future.ttf");
	
	mTextures.load(TextureID::TitleScreen, "Image/NYN_BG.png");
	mTextures.load(TextureID::Buttons, "Image/greenSheet.png");
	mWindow.setKeyRepeatEnabled(false);
	registerStates();
	mStateStack.pushState(StateID::Title);
}
void Shitful::Game::run()
{
	sf::Clock clock;
	sf::Time TimeSince = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		TimeSince += elapsedTime;

		while (TimeSince >= frameRate)
		{
			//printf("%f\n", TimeSince.asSeconds());
			processInput();
			TimeSince -= frameRate;
			update(frameRate);
			if (mStateStack.isEmpty())
				mWindow.close();
		}
		render();
	}
}
void Shitful::Game::registerStates()
{
	mStateStack.registerState<TitleState>(StateID::Title);
	mStateStack.registerState<MenuState>(StateID::Menu);
	mStateStack.registerState<GameState>(StateID::Game);
	mStateStack.registerState<PauseState>(StateID::Pause);
	mStateStack.registerState<SettingsState>(StateID::Settings);
	mStateStack.registerState<GameOverState>(StateID::GameOver);
}
void Shitful::Game::processInput()
{
	/*
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::GainedFocus:
			mIsPaused = false;
			break;
		case sf::Event::LostFocus:
			mIsPaused = true;
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}*/
	//CommandQueue& commands = mWorld.getCommandQueue();
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		//mPlayer.handleEvent(event, commands);
		switch (event.type)
		{
		case sf::Event::GainedFocus:
			mIsPaused = false;
			break;
		case sf::Event::LostFocus:
			mIsPaused = true;
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		default:
			mStateStack.handleEvent(event);
			break;
		}
	}
	//mPlayer.handleRealtimeInput(commands);
}

void Shitful::Game::update(sf::Time deltaTime)
{
	/*
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= PlayerSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += PlayerSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= PlayerSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += PlayerSpeed;
	if ((mIsMovingUp ^ mIsMovingDown) || (mIsMovingLeft ^ mIsMovingRight))		// 确保movement不是0，否则不能正规化		
		movement /= sqrtf(movement.x * movement.x + movement.y * movement.y);	// 如果没有这个处理，当角色斜向移动时速度是正交移动的sqrt(2)倍
	mPlayer.move(movement * PlayerSpeed * deltaTime.asSeconds());
	*/

	//mWorld.update(deltaTime);
	mStateStack.update(deltaTime);
}
void Shitful::Game::render()
{
	/*
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();*/
	mWindow.clear();
	//mWorld.draw();
	mStateStack.draw();
	//mWindow.setView(mWindow.getDefaultView());
	//mWindow.draw(mStatisticsText);
	mWindow.display();
}
