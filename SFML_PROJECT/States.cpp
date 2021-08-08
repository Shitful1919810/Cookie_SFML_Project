#include "States.h"
#include "StateStack.h"
Shitful::State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer& music, SoundPlayer& sounds)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
	, music(&music)
	, sounds(&sounds)
{
}

Shitful::State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
	
}

Shitful::State::~State()
{
}

void Shitful::State::requestStackPush(StateID stateID)
{
	mStack->pushState(stateID);
}

void Shitful::State::requestStackPop()
{
	mStack->popState();
}

void Shitful::State::requestStateClear()
{
	mStack->clearStates();
}

Shitful::State::Context Shitful::State::getContext() const
{
	return mContext;
}

