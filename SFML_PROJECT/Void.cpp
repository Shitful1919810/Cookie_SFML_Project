#include "Void.h"

Shitful::Tile::Type Shitful::Void::getType()
{
	return Tile::Void;
}

bool Shitful::Void::isBlocking()
{
	return false;
}
