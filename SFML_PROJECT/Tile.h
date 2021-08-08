#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
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
			TypeCount
		};

	public:
		Tile(TextureHolder& textures, Type type = Void);
		void setTileType(Type type);
		bool isBlocking();		// ��������Ƿ���赲���ͨ��
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