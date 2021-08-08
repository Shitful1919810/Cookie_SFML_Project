#pragma once
#pragma once
#include "States.h"
#include "Container.h"

namespace Shitful
{
    class PauseState : public State
    {
    public:
        PauseState(StateStack& stack, Context context);
        ~PauseState();
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        sf::Sprite mBackgroundSprite;
        sf::Text mPausedText;
        Shitful::GUI::Container mGUIContainer;
    };

}