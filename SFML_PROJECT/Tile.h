#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "DataTables.h"
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
			TestText,
			TypeCount
		};

		using Ptr = std::unique_ptr<Tile>;

		friend Tile::Ptr tileFactory(Tile::Type type, TextureHolder& textures, FontHolder& fonts);

	public:
		Tile(TextureHolder& textures);
		virtual bool isBlocking();		// 这个方格是否会阻挡玩家通过
		virtual void setGridPosition(sf::Vector2i position, int gridSize);
		virtual void draw(sf::RenderTarget& target);
		virtual Type getType() = 0;
		virtual bool touchTrigger();		// 这个方格接触后是否触发事件

		virtual void onActive(CommandQueue & command);
		virtual void onDeactive(CommandQueue & command);

		sf::Vector2f getPosition(int gridSize) const;
		sf::FloatRect getGlobalBounds(int gridSize) const;
		bool intersects(const sf::FloatRect bounds, int gridSize) const;
		

	protected:
		static const std::vector<Shitful::TileData>& getDataTable();
		TextureHolder& mTextures;
	private:
		sf::Vector2i mCoordPosition;
	};
}