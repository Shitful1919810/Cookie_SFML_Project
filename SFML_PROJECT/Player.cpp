#include "Player.h"
#include "PlayerMover.h"
#include <iostream>
#include <functional>

Shitful::Player::Player()
: mCurrentChapterStatus(ChapterStatus::Running)
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::P] = Output;

	initializeActions();

	for(auto& pair:mActionBinding)
		pair.second.category = Category::Player;
}

void Shitful::Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	/*
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << ","
				<< s.getPosition().y << std::endl;
		};
		commands.push(output);
	}
	*/

	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Shitful::Player::handleRealtimeInput(CommandQueue& commands)
{
	/*
	const float playerSpeed = 200.f;
	bool isMovingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool isMovingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool isMovingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool isMovingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	sf::Vector2f movement(0.f, 0.f);
	if (isMovingUp)
		movement.y -= 1.0f;
	if (isMovingDown)
		movement.y += 1.0f;
	if (isMovingLeft)
		movement.x -= 1.0f;
	if (isMovingRight)
		movement.x += 1.0f;
	if ((isMovingUp ^ isMovingDown) || (isMovingLeft ^ isMovingRight))			// 确保movement不是0，否则不能正规化	
		movement /= sqrtf(movement.x * movement.x + movement.y * movement.y);	// 如果没有这个处理，当角色斜向移动时速度是正交移动的sqrt(2)倍
	Command mover;
	mover.category = Category::PlayerAircraft;
	mover.action = derivedAction<Aircraft>(PlayerMover(movement * playerSpeed));
	commands.push(mover);*/
	for (auto& pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Shitful::Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Shitful::Player::getAssignedKey(Action action) const
{
	for(auto& pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}
	return sf::Keyboard::Unknown;
}

void Shitful::Player::setChapterStatus(ChapterStatus status)
{
	mCurrentChapterStatus = status;
}

Shitful::Player::ChapterStatus Shitful::Player::getChapterStatus() const
{
	return mCurrentChapterStatus;
}

void Shitful::Player::initializeActions()
{
	//const float playerSpeed = 200.f;

	mActionBinding[MoveLeft].action = derivedAction<Cookie>(PlayerMover(-1.0f, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Cookie>(PlayerMover(+1.0f, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Cookie>(PlayerMover(0.f, -1.0f));
	mActionBinding[MoveDown].action = derivedAction<Cookie>(PlayerMover(0.f, +1.0f));
	mActionBinding[Output].action = [](SceneNode& target, sf::Time dt) {printf("%f , %f\n", target.getPosition().x, target.getPosition().y); };
}

bool Shitful::Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}
