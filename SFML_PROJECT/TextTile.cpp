#include "TextTile.h"
#include "TextNode.h"

Shitful::TextTile::TextTile(TextureHolder& textures, FontHolder& fonts, const std::string& text)
    : mFonts(fonts)
    , mText(text)
    , mTextPtr(nullptr)
    , Tile(textures)
    , mShape({ 64, 64 })
{
    mShape.setFillColor(sf::Color::Green);
}

void Shitful::TextTile::setGridPosition(sf::Vector2i position, int gridSize)
{
    mShape.setPosition(static_cast<sf::Vector2f>(position) * static_cast<float>(gridSize));
    Tile::setGridPosition(position, gridSize);
}

void Shitful::TextTile::draw(sf::RenderTarget& target)
{
    target.draw(mShape);
}

Shitful::Tile::Type Shitful::TextTile::getType()
{
    return Tile::TestText;
}

bool Shitful::TextTile::touchTrigger()
{
    return true;
}

void Shitful::TextTile::onActive(CommandQueue& command)
{
    if (mTextPtr)
        return;
    Command text;
    text.category = Shitful::Category::Player;
    text.action = [this](SceneNode& node, sf::Time)
    {
        std::unique_ptr<Shitful::TextNode> textNode = std::make_unique<Shitful::TextNode>(mFonts, mText);
        textNode->setPosition(0, -100.f);
        textNode->setRotation(-node.getRotation());
        textNode->setScale({ 1.f / node.getScale().x ,1.f / node.getScale().y });
        mTextPtr = textNode.get();
        node.attachChild(std::move(textNode));
    };
    command.push(text);
}

void Shitful::TextTile::onDeactive(CommandQueue& command)
{
    if (mTextPtr)
    {
        mTextPtr->destroy();
        mTextPtr = nullptr;
    }
}
