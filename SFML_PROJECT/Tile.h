#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "DataTables.h"
#include "ResourceIdentifiers.h"
namespace Shitful
{
	class Tile		// Tile ��ʾ��ͼ�ϵĲ��ᷢ���仯�Ķ���
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
		virtual bool isBlocking();		// ��������Ƿ���赲���ͨ��
		virtual void setGridPosition(sf::Vector2i position, int gridSize);
		virtual void draw(sf::RenderTarget& target);
		virtual Type getType() = 0;
		virtual bool touchTrigger();		// �������Ӵ����Ƿ񴥷��¼�

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