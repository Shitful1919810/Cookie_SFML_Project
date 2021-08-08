#include <functional>
#include "DataTables.h"
#include "NYN.h"
#include "Tile.h"
#include "Particle.h"
#include "ResourceIdentifiers.h"

using namespace std::placeholders;

std::vector<Shitful::EntityData> Shitful::initializeAircraftData()
{
	std::vector<EntityData> data(Cookie::EntityType::TypeCount);
	data[Cookie::EntityType::Player_ID].hitpoints = 100;
	data[Cookie::EntityType::Player_ID].speed = 600.f;
	data[Cookie::EntityType::Player_ID].acceleration = 6000.f;
	data[Cookie::EntityType::Player_ID].deceleration = 3000.f;
	data[Cookie::EntityType::Player_ID].texture = TextureID::Player;
	data[Cookie::EntityType::Player_ID].textureRect = sf::IntRect(0, 0, 1024 / 16, 128 / 2);
	return data;
}



std::vector<Shitful::ParticleData> Shitful::initializeParticleData()
{
	std::vector<ParticleData> data(Particle::ParticleCount);

	return data;
}

std::vector<Shitful::TileData> Shitful::initializeTileData()
{

	const int gridSize = 64;

	std::vector<TileData> data(Tile::TypeCount);
	data[Tile::Void].isBlocking = true;
	data[Tile::Void].texture = TextureID::TileSet;
	data[Tile::Void].textureRect = sf::IntRect(0, gridSize * 12, gridSize, gridSize);

	data[Tile::Floor].isBlocking = false;
	data[Tile::Floor].texture = TextureID::TileSet;
	data[Tile::Floor].textureRect = sf::IntRect(gridSize, gridSize, gridSize, gridSize);

	data[Tile::Wall].isBlocking = true;
	data[Tile::Wall].texture = TextureID::TileSet;
	data[Tile::Wall].textureRect = sf::IntRect(gridSize, gridSize * 5, gridSize, gridSize);

	data[Tile::Tree].isBlocking = true;
	data[Tile::Tree].texture = TextureID::TileSet;
	data[Tile::Tree].textureRect = sf::IntRect(0, gridSize * 9, gridSize, gridSize);
	return data;
}


Shitful::Direction::Direction(float angle, float distance) : angle(angle), distance(distance)
{
}
