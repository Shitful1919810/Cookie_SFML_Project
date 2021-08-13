#include "Floor.h"

Shitful::Floor::Floor(TextureHolder& textures) : Tile(textures)
{
    mSprite.setTexture(mTextures.get(getDataTable()[Tile::Floor].texture));
}

bool Shitful::Floor::isBlocking()
{
    return false;
}

void Shitful::Floor::setGridPosition(sf::Vector2i position, int gridSize)
{
    mSprite.setPosition(getPosition(gridSize));
    Tile::setGridPosition(position, gridSize);
}

void Shitful::Floor::draw(sf::RenderTarget& target)
{
    target.draw(mSprite);
}

Shitful::Tile::Type Shitful::Floor::getType()
{
    return Tile::Floor;
}
