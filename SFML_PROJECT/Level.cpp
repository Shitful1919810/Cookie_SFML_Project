#include <fstream>
#include <exception>
#include "Utilities.h"
#include "Level.h"

Shitful::Level::Level(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds)
	: mTarget(outputTarget)
	, mTextures()
	, maxGridSize()
	, mFonts(fonts)
	, mSounds(sounds)
	, mWorldView(outputTarget.getDefaultView())
	, mSceneGraph()
	, mGridSize(64)
{
	loadResources();
	buildLevel("Level\\Test.lvl");
	mWorldView.setSize(mWorldView.getSize() * 2.f);
}

void Shitful::Level::buildLevel(const std::string& file)
{
	std::ifstream loadfile(file);
	if (!loadfile.is_open())
		throw std::runtime_error("Level file " + file + " could not be loaded.");
	loadfile >> Layer >> maxGridSize.x >> maxGridSize.y >> mWorldBound.left >> mWorldBound.top >> mWorldBound.width >> mWorldBound.height;
	mMap.clear();

	mMap.resize(Layer);
	for (auto& layer : mMap)
	{
		layer.resize(maxGridSize.y);
		for (int row = 0; row < maxGridSize.y; ++row)
		{
			for (int col = 0; col < maxGridSize.x; ++col)
			{
				int tileId;
				loadfile >> tileId;
				if (tileId < 0 || tileId >= Tile::TypeCount)
					throw std::runtime_error("Invalid input in " + file);
				layer[row].emplace_back(mTextures, static_cast<Tile::Type>(tileId));
				layer[row].back().setGridPosition({ col, row }, mGridSize);
			}
		}
	}
	if(mPlayerEntity)
		mPlayerEntity->destroy();
	mSceneGraph.removeWrecks();

	std::unique_ptr<Cookie> player(new Cookie(Cookie::Player_ID, mTextures, mFonts));
	mPlayerEntity = player.get();
	mPlayerEntity->setPosition(mGridSize * 5, mGridSize * 20);
	mSceneGraph.attachChild(std::move(player));
	loadfile.close();
}

void Shitful::Level::setPlayerPosition(sf::Vector2f position)
{
	mPlayerEntity->setPosition(position);
}

void Shitful::Level::update(sf::Time dt)
{
	mPlayerEntity->setAcceleration({ 0.f, 0.f });

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	mSceneGraph.removeWrecks();
	mPlayerEntity->applyAcceleration(dt);
	fixPlayerMovement(dt);
	mSceneGraph.update(dt, mCommandQueue);
	//printf("%f,%f\n", mPlayerEntity->getVelocity().x, mPlayerEntity->getVelocity().y);
	mWorldView.setCenter(mPlayerEntity->getPosition());
}

void Shitful::Level::draw()
{

	mTarget.setView(mWorldView);

	drawTiles();
	mTarget.draw(mSceneGraph);
}

bool Shitful::Level::hasAlivePlayer()
{
	return true;
}

bool Shitful::Level::hasPlayerReachedEnd()
{
	return false;
}

Shitful::CommandQueue& Shitful::Level::getCommandQueue()
{
	return mCommandQueue;
}

void Shitful::Level::loadResources()
{
	mTextures.load(TextureID::Player, "Image/NYN_WALK.png");
	mTextures.load(TextureID::TileSet, "Image/RPGpack_sheet.png");
}

void Shitful::Level::fixPlayerMovement(sf::Time dt)
{

	handleTileCollision(mPlayerEntity, dt);
	handleBoundaryCollision(mPlayerEntity, dt);

}

void Shitful::Level::drawTiles()
{
	sf::Vector2f position = mWorldView.getCenter();
	sf::Vector2f size = mWorldView.getSize();

	int fromX = bound(static_cast<int>(position.x - size.x / 2.f) / mGridSize - 1, 0, maxGridSize.x);
	int fromY = bound(static_cast<int>(position.y - size.y / 2.f) / mGridSize - 1, 0, maxGridSize.y);
	int toX = bound(static_cast<int>(position.x + size.x / 2.f) / mGridSize + 1, 0, maxGridSize.x);
	int toY = bound(static_cast<int>(position.y + size.y / 2.f) / mGridSize + 1, 0, maxGridSize.y);
	for (auto& layer : mMap)
	{
		for (int row = fromY; row < toY; ++row)
		{
			for (int col = fromX; col < toX; ++col)
			{
				layer[row][col].draw(mTarget );
			}
		}
	}
}

void Shitful::Level::handleTileCollision(Entity * entity, sf::Time dt)
{
	sf::Vector2i position = entity->getGridCoord(mGridSize);
	int fromX = bound(position.x - 1, 0, maxGridSize.x);
	int fromY = bound(position.y - 1, 0, maxGridSize.y);
	int toX = bound(position.x + 3, 0, maxGridSize.x);
	int toY = bound(position.y + 3, 0, maxGridSize.y);


	for(auto& layer : mMap)
	{
		for (int x = fromX; x < toX; x++)
		{
			for (int y = fromY; y < toY; y++)
			{
				assert(entity->getHitbox());
				sf::FloatRect playerBounds = entity->getHitbox()->getHitboxRect();
				sf::FloatRect wallBounds = layer[y][x].getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getHitbox()->getNextHitbox(dt);
				if (layer[y][x].isBlocking() &&
					layer[y][x].intersects(nextPositionBounds)
					)
				{
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left + playerBounds.width / 2.f, wallBounds.top - playerBounds.height / 2.f);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left + playerBounds.width / 2.f, wallBounds.top + wallBounds.height + playerBounds.height / 2.f);
					}

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width / 2.f, playerBounds.top + playerBounds.height / 2.f);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width + playerBounds.width / 2.f, playerBounds.top + playerBounds.height / 2.f);
					}
				}
			}
		}
	}
}

void Shitful::Level::handleBoundaryCollision(Entity* entity, sf::Time dt)
{
	sf::FloatRect playerBounds = entity->getHitbox()->getHitboxRect();
	sf::FloatRect nextPositionBounds = entity->getHitbox()->getNextHitbox(dt);
	sf::FloatRect realWorldBound(mWorldBound.left * mGridSize,mWorldBound.top * mGridSize,mWorldBound.width * mGridSize,mWorldBound.height * mGridSize);
	if (nextPositionBounds.top < realWorldBound.top)
	{
		entity->stopVelocityY();
		entity->setPosition(playerBounds.left + playerBounds.width / 2.f, realWorldBound.top + playerBounds.height / 2.f);
	}
	if (nextPositionBounds.top + nextPositionBounds.height > realWorldBound.top + realWorldBound.height)
	{
		entity->stopVelocityY();
		entity->setPosition(playerBounds.left + playerBounds.width / 2.f, realWorldBound.top + realWorldBound.height - playerBounds.height / 2.f);
	}
	if (nextPositionBounds.left < realWorldBound.left)
	{
		entity->stopVelocityX();
		entity->setPosition(realWorldBound.left + playerBounds.width / 2.f, playerBounds.top + playerBounds.height / 2.f);
	}
	if (nextPositionBounds.left + nextPositionBounds.width > realWorldBound.left + realWorldBound.width)
	{
		entity->stopVelocityX();
		entity->setPosition(realWorldBound.left + realWorldBound.width - playerBounds.width / 2.f, playerBounds.top + playerBounds.height / 2.f);
	}

}