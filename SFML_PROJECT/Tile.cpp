#include "Tile.h"
#include "DataTables.h"
namespace
{
	const std::vector<Shitful::TileData> Table = Shitful::initializeTileData();
}

Shitful::Tile::Tile(TextureHolder& textures)
	: mTextures(textures)
{

}

void Shitful::Tile::setGridPosition(sf::Vector2i position, int gridSize)
{
	mCoordPosition = position;
}

void Shitful::Tile::draw(sf::RenderTarget& target)
{
}

sf::Vector2f Shitful::Tile::getPosition(int gridSize) const
{
	return static_cast<sf::Vector2f>(mCoordPosition) * static_cast<float>(gridSize);
}

sf::FloatRect Shitful::Tile::getGlobalBounds(int gridSize) const
{
	return { getPosition(gridSize),{static_cast<float>(gridSize),static_cast<float>(gridSize)} };
}

bool Shitful::Tile::intersects(const sf::FloatRect bounds, int gridSize) const
{
	return getGlobalBounds(gridSize).intersects(bounds);
}

const std::vector<Shitful::TileData>& Shitful::Tile::getDataTable()
{
	return Table;
}
