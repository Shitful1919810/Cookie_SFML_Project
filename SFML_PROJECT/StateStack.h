#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

#include "States.h"
#include "StateIdentifier.h"
namespace Shitful
{
	class StateStack : private sf::NonCopyable
	{
	public:
		enum class ActionID
		{
			Push,
			Pop,
			Clear,
		};
	public:
		explicit StateStack(State::Context context);
		template <typename T>
		void registerState(StateID stateID);
		void update(sf::Time dt);
		void draw();
		void handleEvent(const sf::Event& event);
		void pushState(StateID stateID);
		void popState();
		void clearStates();
		bool isEmpty() const;
	private:
		State::Ptr createState(StateID stateID);
		void applyPendingChanges();
	private:
		struct PendingChange
		{
			explicit PendingChange(ActionID action, StateID stateID = StateID::None);
				ActionID action;
			StateID stateID;
		};
	private:
		std::vector<State::Ptr> mStack;
		std::vector<PendingChange> mPendingList;
		State::Context mContext;
		std::map<StateID,
			std::function<State::Ptr()>> mFactories;
	};


	template <typename T>
	void StateStack::registerState(StateID stateID)
	{
		mFactories[stateID] = [this]()
		{
			return State::Ptr(new T(*this, mContext));
		};
	}
}
