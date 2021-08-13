#pragma once
#include "Void.h"
#include "CommonTile.h"

namespace Shitful
{
	Tile::Ptr tileFactory(Tile::Type type, TextureHolder& textures);
}