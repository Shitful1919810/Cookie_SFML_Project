#include "GUI.h"

void Shitful::GUI::Component::handleEvent(const sf::Event& event)
{
}

Shitful::GUI::Component::Component() 
    : mIsSelected(false)
    , mIsActive(false)
{
}

Shitful::GUI::Component::~Component()
{
}

bool Shitful::GUI::Component::isSelectable() const
{
    return false;
}

bool Shitful::GUI::Component::isSelected() const
{
    return mIsSelected;
}

void Shitful::GUI::Component::select()
{
    mIsSelected = true;
}

void Shitful::GUI::Component::deselect()
{
    mIsSelected = false;
}

bool Shitful::GUI::Component::isActive() const
{
    return mIsActive;
}

void Shitful::GUI::Component::activate()
{
    mIsActive = true;
}

void Shitful::GUI::Component::deactivate()
{
    mIsActive = false;
}
