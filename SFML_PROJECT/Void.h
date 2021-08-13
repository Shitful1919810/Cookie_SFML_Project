#pragma once
#include "Tile.h"

namespace Shitful
{
	class Void : public Tile
	{
	public:
		using Tile::Tile;
		virtual Type getType();
		virtual bool isBlocking();

	private:
		sf::Sprite mSprite;
	};
}