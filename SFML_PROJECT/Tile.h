#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.h"
namespace Shitful
{
	class Tile		// Tile 表示地图上的不会发生变化的东西
	{
	public:
		enum Type
		{
			Void,
			Floor,
			Wall,
			Tree,
			TypeCount
		};

	public:
		Tile(TextureHolder& textures, Type type = Void);
		void setTileType(Type type);
		bool isBlocking();		// 这个方格是否会阻挡玩家通过
		void setGridPosition(sf::Vector2i position, int gridSize);
		void draw(sf::RenderTarget& target);

		virtual const sf::Vector2f& getPosition() const;
		virtual const sf::FloatRect getGlobalBounds() const;
		virtual const bool intersects(const sf::FloatRect bounds) const;
	private:

	private:
		Type mType;
		sf::Sprite mSprite;

		TextureHolder& mTextures;
	};
}