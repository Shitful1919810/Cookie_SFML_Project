#pragma once
#include "States.h"
#include "Level.h"
namespace Shitful
{
    class GameState : public State
    {
    public:
        GameState(StateStack& stack,
            Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        Level mWorld;
        Player& mPlayer;
    };

}