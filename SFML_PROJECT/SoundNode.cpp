#include "SoundNode.h"
#include "SoundPlayer.h"
#include "Command.h"

Shitful::SoundNode::SoundNode(SoundPlayer& player)
    : SceneNode()
    , mSounds(player)
{
}

void Shitful::SoundNode::playSound(SoundEffectID sound, sf::Vector2f position)
{
    mSounds.play(sound, position);
}

unsigned int Shitful::SoundNode::getCategory() const
{
    return Shitful::Category::SoundEffect;
}
