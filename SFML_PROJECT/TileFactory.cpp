#include "TileFactory.h"

Shitful::Tile::Ptr Shitful::tileFactory(const Tile::Type type, TextureHolder& textures)
{
	switch (type)
	{
	case Tile::Void:
		return std::make_unique<Shitful::Void>(textures);
	case Tile::Floor:
	case Tile::Tree:
	case Tile::Wall:
		return std::make_unique<CommonTile>(textures, type);
	}
}
