#include <cstdio>
#include <string>
#include <exception>
#include "Utilities.h"
#include "Level.h"
#include "TileFactory.h"

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
	//loadfile >> Layer >> maxGridSize.x >> maxGridSize.y >> mWorldBound.left >> mWorldBound.top >> mWorldBound.width >> mWorldBound.height;
	readToInt(loadfile, Layer);
	readToInt(loadfile, maxGridSize.x);
	readToInt(loadfile, maxGridSize.y);
	readToInt(loadfile, mWorldBound.left);
	readToInt(loadfile, mWorldBound.top);
	readToInt(loadfile, mWorldBound.width);
	readToInt(loadfile, mWorldBound.height);
	readToInt(loadfile, mViewBound.left);
	readToInt(loadfile, mViewBound.top);
	readToInt(loadfile, mViewBound.width);
	readToInt(loadfile, mViewBound.height);
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
				readToInt(loadfile, tileId);
				//loadfile >> tileId;
				if (tileId < 0 || tileId >= Tile::TypeCount)
					throw std::runtime_error("Invalid input in " + file);
				layer[row].emplace_back(tileFactory(static_cast<Tile::Type>(tileId), mTextures, mFonts));
				layer[row].back()->setGridPosition({ col, row }, mGridSize);
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
	mPlayerEntity->applyAcceleration(dt);
	fixPlayerMovement(dt);
	handleTileEvents(dt);
	mSceneGraph.update(dt, mCommandQueue);
	mSceneGraph.removeWrecks();
	//printf("%f,%f\n", mPlayerEntity->getVelocity().x, mPlayerEntity->getVelocity().y);
}

void Shitful::Level::draw()
{
	updateView();
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
	mTextures.load(TextureID::PlayerWalking, "Image/walk3.png");
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
				layer[row][col]->draw(mTarget);
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
				sf::FloatRect wallBounds = layer[y][x]->getGlobalBounds(mGridSize);
				sf::FloatRect nextPositionBounds = entity->getHitbox()->getNextHitbox(dt);
				if (layer[y][x]->isBlocking() &&
					layer[y][x]->intersects(nextPositionBounds,mGridSize)
					)
				{
					// 障碍物在下方
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
#ifdef SHITFUL_PRINT_COLLISION
						printf("Bottom Collision\n");
#endif
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left + playerBounds.width / 2.f, wallBounds.top - playerBounds.height / 2.f);
					}

					// 障碍物在上方
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
#ifdef SHITFUL_PRINT_COLLISION
						printf("Top Collision\n");
#endif
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left + playerBounds.width / 2.f, wallBounds.top + wallBounds.height + playerBounds.height / 2.f);
					}

					// 障碍物在右侧
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
#ifdef SHITFUL_PRINT_COLLISION
						printf("Right Collision\n");
#endif
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width / 2.f, playerBounds.top + playerBounds.height / 2.f);
					}

					// 障碍物在左侧
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
#ifdef SHITFUL_PRINT_COLLISION
						//printf("Left Collision\n");
						printf("%f\n", playerBounds.left);
#endif
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width + playerBounds.width / 2.f, playerBounds.top + playerBounds.height / 2.f);
					}
				}
			}
		}
	}
}

void Shitful::Level::handleTileEvents(sf::Time dt)
{
	sf::Vector2i position = mPlayerEntity->getGridCoord(mGridSize);
	int fromX = bound(position.x - 1, 0, maxGridSize.x);
	int fromY = bound(position.y - 1, 0, maxGridSize.y);
	int toX = bound(position.x + 3, 0, maxGridSize.x);
	int toY = bound(position.y + 3, 0, maxGridSize.y);
	sf::FloatRect playerBounds = mPlayerEntity->getHitbox()->getHitboxRect();

	for (auto& layer : mMap)
	{
		for (int x = fromX; x < toX; x++)
		{
			for (int y = fromY; y < toY; y++)
			{
				if (layer[y][x]->touchTrigger() &&
					layer[y][x]->intersects(playerBounds, mGridSize)
					)
				{
					layer[y][x]->onActive(mCommandQueue);
				}
				else
				{
					layer[y][x]->onDeactive(mCommandQueue);
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

void Shitful::Level::updateView()
{
	sf::Vector2f playerPosition = mPlayerEntity->getPosition();
	sf::Vector2f halfViewSize = mWorldView.getSize() / 2.f;
	sf::Vector2f viewCenter;
	if (mViewBound.width * mGridSize <= halfViewSize.x * 2.f)
		viewCenter.x = (2.f * mViewBound.left + mViewBound.width) / 2.f * mGridSize;
	else
		viewCenter.x = bound(playerPosition.x, mViewBound.left * mGridSize + halfViewSize.x, (mViewBound.left + mViewBound.width) * mGridSize - halfViewSize.x);
	if (mViewBound.height * mGridSize <= halfViewSize.y * 2.f)
		viewCenter.y = (2.f * mViewBound.top + mViewBound.height) / 2.f * mGridSize;
	else
		viewCenter.y = bound(playerPosition.y, mViewBound.top * mGridSize + halfViewSize.y, (mViewBound.top + mViewBound.height) * mGridSize - halfViewSize.y);

	mWorldView.setCenter(viewCenter);
}

void Shitful::Level::readToInt(std::ifstream& in, int& val)
{
	char c;
	std::string line;
	while (true)
	{
		in >> c;
		if (!in)
			throw std::runtime_error("File is corrupted.");
		if (isspace(c))
			continue;
		if (c == '#')
		{
			std::getline(in, line);
			continue;
		}
		in.unget();
		in >> val;
		break;



	}
}
