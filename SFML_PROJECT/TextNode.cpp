#include "TextNode.h"
#include "Utilities.h"

Shitful::TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
	mText.setFont(fonts.get(FontID::Main));
	mText.setCharacterSize(20);
	setString(text);
}

void Shitful::TextNode::setString(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void Shitful::TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states);
}
