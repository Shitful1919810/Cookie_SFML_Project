#pragma once
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "Command.h"
#include "Player.h"
#include "StateIdentifier.h"
#include "ResourceIdentifiers.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
namespace Shitful
{
	class StateStack;

	class State
	{
	public:
		using Ptr = std::unique_ptr<State>;
		struct Context 
		{
			Context() = default;
			Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player,
				MusicPlayer& music, SoundPlayer& sounds);
			sf::RenderWindow* window;
			TextureHolder* textures;
			FontHolder* fonts;
			Player* player;

			MusicPlayer* music;
			SoundPlayer* sounds;
		};
	public:
		State(StateStack& stack, Context context);
		virtual ~State();
		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;
	protected:
		void requestStackPush(StateID stateID);
		void requestStackPop();
		void requestStateClear();
		Context getContext() const;
	private:
		StateStack* mStack;
		Context mContext;
	};

}