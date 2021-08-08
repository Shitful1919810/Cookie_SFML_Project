#include "Tile.h"
#include "DataTables.h"
#include "Resources.h"
namespace
{
	const std::vector<Shitful::TileData> Table = Shitful::initializeTileData();
}

Shitful::Tile::Tile(TextureHolder& textures, Type type)
	: mType(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
	, mTextures(textures)
{

}

void Shitful::Tile::setTileType(Type type)
{
	if (Table[type].texture != Table[mType].texture)
		mSprite.setTexture(mTextures.get(Table[type].texture));
	mSprite.setTextureRect(Table[type].textureRect);
	mType = type;
}

bool Shitful::Tile::isBlocking()
{
	switch (mType)
	{
	case Wall:
	case Tree:
		return true;
	}
	return false;
}

void Shitful::Tile::setGridPosition(sf::Vector2i position, int gridSize)
{
	mSprite.setPosition(sf::Vector2f{ static_cast<float>(position.x * gridSize), static_cast<float>(position.y * gridSize) });
}

void Shitful::Tile::draw(sf::RenderTarget& target)
{
	if (mType == Void)
		return;
	target.draw(mSprite);
}

const sf::Vector2f& Shitful::Tile::getPosition() const
{
	return this->mSprite.getPosition();
}

const sf::FloatRect Shitful::Tile::getGlobalBounds() const
{
	return this->mSprite.getGlobalBounds();
}

const bool Shitful::Tile::intersects(const sf::FloatRect bounds) const
{
	return this->mSprite.getGlobalBounds().intersects(bounds);
}
