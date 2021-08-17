#include "TextNode.h"
#include "Utilities.h"

Shitful::TextNode::TextNode(const FontHolder& fonts, const std::string& text)
	: isRemoved(false)
{
	mText.setFont(fonts.get(FontID::Main));
	mText.setCharacterSize(40);
	setString(text);
}

void Shitful::TextNode::setString(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}

bool Shitful::TextNode::isMarkedForRemoval() const
{
	return isRemoved;
}

Shitful::Receiver Shitful::TextNode::getCategory() const
{
	return Shitful::Category::TestText;
}

void Shitful::TextNode::destroy()
{
	isRemoved = true;
}

void Shitful::TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states);
}
