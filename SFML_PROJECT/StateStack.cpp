#include "StateStack.h"
#include <cassert>
Shitful::State::Ptr Shitful::StateStack::createState(StateID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	return found->second();
}

void Shitful::StateStack::applyPendingChanges()
{
	for (PendingChange& change : mPendingList)
	{
		switch (change.action)
		{
		case ActionID::Push:
			mStack.push_back(createState(change.stateID));
			break;
		case ActionID::Pop:
			mStack.pop_back();
			break;
		case ActionID::Clear:
			mStack.clear();
			break;
		}
	}
	mPendingList.clear();
}

Shitful::StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{
}

void Shitful::StateStack::update(sf::Time dt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void Shitful::StateStack::draw()
{
	for (State::Ptr& state : mStack)
		state->draw();
}

void Shitful::StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			return;
	}
	applyPendingChanges();
}

void Shitful::StateStack::pushState(StateID stateID)
{
	mPendingList.push_back(PendingChange(ActionID::Push, stateID));
}

void Shitful::StateStack::popState()
{
	mPendingList.push_back(PendingChange(ActionID::Pop));
}

void Shitful::StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(ActionID::Clear));
}

bool Shitful::StateStack::isEmpty() const
{
	return mStack.empty();
}

Shitful::StateStack::PendingChange::PendingChange(ActionID action, StateID stateID) : action(action), stateID(stateID)
{
}
