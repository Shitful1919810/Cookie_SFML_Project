#pragma once
#include "NYN.h"
namespace Shitful
{
	class Player
	{
	public:
		enum Action
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			Output,
			ActionCount
		};

		enum class ChapterStatus
		{
			Running,
			Success,
			Failure
		};

	public:
		Player();

		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleRealtimeInput(CommandQueue& commands);
		void assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key getAssignedKey(Action action) const;

		void setChapterStatus(ChapterStatus status);
		ChapterStatus getChapterStatus() const;

	private:
		void initializeActions();
		static bool isRealtimeAction(Action action);

	private:
		std::map<sf::Keyboard::Key, Action> mKeyBinding;		// 将按键映射为Action
		std::map<Action, Command> mActionBinding;				// 将Action变为Command
		ChapterStatus mCurrentChapterStatus;


	};

}