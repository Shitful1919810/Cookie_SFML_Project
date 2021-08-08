#pragma once
#include "ResourceIdentifiers.h"
#include "NYN.h"
#include <SFML/System/Time.hpp>
#include <vector>
namespace Shitful
{
	struct Direction
	{
		Direction(float angle, float distance);
		float angle;
		float distance;
	};

	struct EntityData
	{
		int hitpoints;
		float speed;
		float acceleration;
		float deceleration;
		TextureID texture;
		sf::IntRect textureRect;
	};

	struct TileData
	{
		bool isBlocking;
		TextureID texture;
		sf::IntRect textureRect;
	};

	struct ParticleData
	{
		sf::Color color;
		sf::Time lifetime;
	};

	std::vector<EntityData>	initializeAircraftData();
	std::vector<ParticleData> initializeParticleData();
	std::vector<TileData> initializeTileData();
}