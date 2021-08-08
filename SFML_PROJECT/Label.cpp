#include "Label.h"
#include "ResourceIdentifiers.h"
#include "Command.h"
#include "Utilities.h"

Shitful::GUI::Label::Label(const std::string& text, const FontHolder& fonts, float outlineThickness, const sf::Color& outlineColor)
    : mText(text, fonts.get(FontID::Main), 16)
{
    mText.setOutlineThickness(outlineThickness);
    mText.setOutlineColor(outlineColor);
}

bool Shitful::GUI::Label::isSelectable() const
{
    return false;
}

void Shitful::GUI::Label::setText(const std::string& text)
{
    mText.setString(text);
    centerOrigin(mText);
}

void Shitful::GUI::Label::setOutlineThickness(float thickness)
{
    mText.setOutlineThickness(thickness);
}

void Shitful::GUI::Label::setOutlineColor(const sf::Color& color)
{
    mText.setOutlineColor(color);
}

void Shitful::GUI::Label::handleEvent(const sf::Event& event)
{
}

void Shitful::GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mText, states);
}
