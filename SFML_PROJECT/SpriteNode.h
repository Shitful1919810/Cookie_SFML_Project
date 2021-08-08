#pragma once
#include "Scene.h"
namespace Shitful
{
	class SpriteNode : public SceneNode		// 仅仅用于显示某个纹理，通常是背景纹理
	{
	public:
		explicit SpriteNode(const sf::Texture& texture);
		SpriteNode(const sf::Texture& texture,
			const sf::IntRect& rect);
	private:
		virtual void drawCurrent(sf::RenderTarget& target,
			sf::RenderStates states) const;
	private:
		sf::Sprite mSprite;
	};

}

