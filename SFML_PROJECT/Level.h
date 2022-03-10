#pragma once
#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "SpriteNode.h"
#include "NYN.h"
#include "Player.h"
#include "ResourceIdentifiers.h"
#include "Tile.h"

namespace Shitful
{
	class Level
	{
	public:
		explicit Level(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds);
		void buildLevel(const std::string& file);
		void setPlayerPosition(sf::Vector2f position);

		void update(sf::Time dt);
		void draw();

		bool hasAlivePlayer();
		bool hasPlayerReachedEnd();

		CommandQueue& getCommandQueue();

	private:
		void loadResources();
		void fixPlayerMovement(sf::Time dt);
		void drawTiles();

		void handleTileCollision(Entity * entity, sf::Time dt);
		void handleTileEvents(sf::Time dt);
		void handleBoundaryCollision(Entity* entity, sf::Time dt);
		void handleEntityCollision();
		void updateView();

		void readToInt(std::ifstream& in, int& val);
	private:
		sf::RenderTarget& mTarget;
		sf::View mWorldView;
		FontHolder& mFonts;
		SoundPlayer& mSounds;
		TextureHolder mTextures;
		CommandQueue mCommandQueue;	// 存放所有收到的Command,这些Command将被分发给mSceneGraph中的每一个节点

		std::vector<std::vector<std::vector<Tile::Ptr>>> mMap;
		sf::Vector2i maxGridSize;
		sf::IntRect mWorldBound;
		sf::IntRect mViewBound;
		int Layer;
		SceneNode mSceneGraph;

		Cookie* mPlayerEntity;
		const int mGridSize;
	};
}