#pragma once
#include "Tile.h"
namespace Shitful
{
	class TextTile : public Tile
	{
	public:
		TextTile(TextureHolder& textures, FontHolder& fonts, const std::string& text);
		virtual void setGridPosition(sf::Vector2i position, int gridSize);
		virtual void draw(sf::RenderTarget& target);
		virtual Type getType();
		virtual bool touchTrigger();		// 这个方格接触后是否触发事件

		virtual void onActive(CommandQueue& command);
		virtual void onDeactive(CommandQueue& command);

	private:
		FontHolder& mFonts;
		std::string mText;
		TextNode* mTextPtr;
		sf::RectangleShape mShape;
	};

}