#pragma once
#include "Tile.h"
namespace Shitful
{
	class CommonTile : public Tile
	{
	public:
		CommonTile(TextureHolder& textures,Tile::Type type);
		virtual void setGridPosition(sf::Vector2i position, int gridSize);
		virtual void draw(sf::RenderTarget& target);
		virtual bool isBlocking();		// ��������Ƿ���赲���ͨ��
		virtual Type getType();
	protected:
		sf::Sprite mSprite;
		Tile::Type mType;
	};


}