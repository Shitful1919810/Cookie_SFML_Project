#include "MovingPatternSwitcher.h"

sf::Transformable& Shitful::PatternSwitcher::getTransformable() const
{
	return *transformable;
}
sf::Drawable& Shitful::PatternSwitcher::getDrawable() const
{
	return *drawable;
}