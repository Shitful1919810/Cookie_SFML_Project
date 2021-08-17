#include "CommonTile.h"
Shitful::CommonTile::CommonTile(TextureHolder& textures,Shitful::Tile::Type type)
	: Tile(textures)
	, mSprite(textures.get(getDataTable()[type].texture), getDataTable()[type].textureRect)
	, mType(type)
{
}

void Shitful::CommonTile::setGridPosition(sf::Vector2i position, int gridSize)
{
	mSprite.setPosition(static_cast<sf::Vector2f>(position)*static_cast<float>(gridSize));
	Tile::setGridPosition(position, gridSize);
}

void Shitful::CommonTile::draw(sf::RenderTarget& target)
{
	target.draw(mSprite);
}

bool Shitful::CommonTile::isBlocking()
{
	return getDataTable()[mType].isBlocking;
}

Shitful::Tile::Type Shitful::CommonTile::getType()
{
	return mType;
}