#pragma once
#include "Tile.h"
namespace Shitful
{
	class Floor : public Tile
	{
	public:
		Floor(TextureHolder& textures);
		virtual bool isBlocking();		// 这个方格是否会阻挡玩家通过
		virtual void setGridPosition(sf::Vector2i position, int gridSize);
		virtual void draw(sf::RenderTarget& target);
		virtual Type getType();

	private:
		sf::Sprite mSprite;
	};

}