#include "SpriteNode.h"

Shitful::SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{
}

Shitful::SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
	: mSprite(texture, rect)
{
}

void Shitful::SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
