#include "Button.h"
#include "Utilities.h"
#include "Command.h"
#include "States.h"
#include "SoundPlayer.h"
Shitful::GUI::Button::Button(Shitful::State::Context context)
    : mCallback()
    , mSprite(context.textures->get(TextureID::Buttons))
    , mText("", context.fonts->get(FontID::Main), 16)
    , mIsToggle(false)
    , mSounds(*context.sounds)
{
    changeTexture(Normal);
    //mText.setOutlineColor(sf::Color(255, 255, 255, 0));
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
    mText.setCharacterSize(40);
}

void Shitful::GUI::Button::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void Shitful::GUI::Button::setText(const std::string& text)
{
    mText.setString(sf::String(text));
    centerOrigin(mText);
}

void Shitful::GUI::Button::setToggle(bool flag)
{
    mIsToggle = flag;
}

sf::Vector2u Shitful::GUI::Button::getSize()
{
    return mSprite.getTexture()->getSize();
}

bool Shitful::GUI::Button::isSelectable() const
{
    return true;
}

void Shitful::GUI::Button::select()
{
    Component::select();
    changeTexture(Selected);
}

void Shitful::GUI::Button::deselect()
{
    Component::deselect();
    changeTexture(Normal);
}

void Shitful::GUI::Button::activate()
{
    Component::activate();
    if (mIsToggle)
        changeTexture(Pressed);
    if (mCallback)
        mCallback();
    if (!mIsToggle)
        deactivate();
    mSounds.play(SoundEffectID::Button);
}

void Shitful::GUI::Button::deactivate()
{
    Component::deactivate();
    if (mIsToggle)
    {
        if (isSelected())
            changeTexture(Selected);
        else
            changeTexture(Normal);
    }
}

void Shitful::GUI::Button::handleEvent(const sf::Event& event)
{
}

void Shitful::GUI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
    
}

void Shitful::GUI::Button::changeTexture(Type buttonType)
{
    sf::IntRect textureRect;
    switch (buttonType)
    {
    case Normal:
        textureRect = { 0, 188, 380, 98 };
        break;
    case Selected:
        textureRect = { 0, 0, 380, 98 };
        break;
    case Pressed:
        textureRect = { 0, 98, 380, 90 };
        break;
    }
    mSprite.setTextureRect(textureRect);
}
