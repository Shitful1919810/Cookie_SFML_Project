#include "Animation.h"

Shitful::Animation::Animation()
	: mSprite()
	, mFrameSize()
	, mNumFrames(0)
	, mCurrentFrame(0)
	, mDuration(sf::Time::Zero)
	, mElapsedTime(sf::Time::Zero)
	, mRepeat(false)
{
}

Shitful::Animation::Animation(const sf::Texture& texture)
	: mSprite(texture)
	, mFrameSize()
	, mNumFrames(0)
	, mCurrentFrame(0)
	, mDuration(sf::Time::Zero)
	, mElapsedTime(sf::Time::Zero)
	, mRepeat(false)
{
}

void Shitful::Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
	mElapsedTime += dt;
	sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
	sf::IntRect textureRect = mSprite.getTextureRect();
	if (mCurrentFrame == 0)
		textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);

	while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mNumFrames || mRepeat))
	{
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}
		mElapsedTime -= timePerFrame;
		if (mRepeat)
		{
			mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;
			if (mCurrentFrame == 0)
				textureRect = sf::IntRect(0, 0, mFrameSize.x,
					mFrameSize.y);
		}
		else
		{
			mCurrentFrame++;
		}
	}

	mSprite.setTextureRect(textureRect);
}

void Shitful::Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

void Shitful::Animation::setTexture(const sf::Texture& texture)
{
	mSprite.setTexture(texture);
}

const sf::Texture* Shitful::Animation::getTexture() const
{
	return mSprite.getTexture();
}

void Shitful::Animation::setFrameSize(sf::Vector2i frameSize)
{
	mFrameSize = frameSize;
}

sf::Vector2i Shitful::Animation::getFrameSize() const
{
	return mFrameSize;
}

void Shitful::Animation::setNumFrames(std::size_t numFrames)
{
	mNumFrames = numFrames;
}

std::size_t Shitful::Animation::getNumFrames() const
{
	return mNumFrames;
}

void Shitful::Animation::setDuration(sf::Time duration)
{
	mDuration = duration;
}

sf::Time Shitful::Animation::getDuration() const
{
	return mDuration;
}

void Shitful::Animation::setRepeating(bool flag)
{
	mRepeat = flag;
}

bool Shitful::Animation::isRepeating() const
{
	return mRepeat;
}

void Shitful::Animation::restart()
{
	mCurrentFrame = 0;
}

bool Shitful::Animation::isFinished() const
{
	return mCurrentFrame >= mNumFrames;
}

sf::FloatRect Shitful::Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect Shitful::Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}
