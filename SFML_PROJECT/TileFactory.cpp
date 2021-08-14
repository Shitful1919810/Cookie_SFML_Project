#include "TileFactory.h"

Shitful::Tile::Ptr Shitful::tileFactory(Tile::Type type, TextureHolder& textures, FontHolder& fonts)
{
	switch (type)
	{
	case Tile::Void:
		return std::make_unique<Shitful::Void>(textures);
	case Tile::Floor:
	case Tile::Tree:
	case Tile::Wall:
		return std::make_unique<CommonTile>(textures, type);
	case Tile::TestText:
		return std::make_unique<TextTile>(textures, fonts, "TestTextTile");
	}
}
