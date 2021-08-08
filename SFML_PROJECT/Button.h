#pragma once
#include <functional>
#include "GUI.h"
#include "ResourceIdentifiers.h"
#include "States.h"

namespace Shitful
{
    class SoundPlayer;

	namespace GUI
	{
		class Button : public Component
		{
        public:
            typedef std::shared_ptr<Button> Ptr;
            typedef std::function<void()> Callback;
             
            enum Type
            {
                Normal,
                Selected,
                Pressed,
                ButtonCount
            };

        public:
            Button(Shitful::State::Context context);

            void setCallback(Callback callback);
            void setText(const std::string& text);
            void setToggle(bool flag);

            sf::Vector2u getSize();

            virtual bool isSelectable() const;
            virtual void select();
            virtual void deselect();

            virtual void activate();
            virtual void deactivate();

            virtual void handleEvent(const sf::Event& event);


        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            void changeTexture(Type buttonType);

        private:
            Callback mCallback;
            //const sf::Texture& mNormalTexture;
            //const sf::Texture& mSelectedTexture;
            //const sf::Texture& mPressedTexture;
            sf::Sprite mSprite;
            sf::Text mText;
            bool mIsToggle;
            SoundPlayer& mSounds;
		};
	}
}