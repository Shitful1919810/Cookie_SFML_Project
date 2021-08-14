#pragma once
#include "Void.h"
#include "CommonTile.h"
#include "TextTile.h"
namespace Shitful
{
	Tile::Ptr tileFactory(Tile::Type type, TextureHolder& textures, FontHolder& fonts);
}