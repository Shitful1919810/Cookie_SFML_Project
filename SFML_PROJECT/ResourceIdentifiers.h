#pragma once
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}
namespace Shitful
{

	enum class TextureID
	{
		TitleScreen,
		Buttons,
		Player,
		PlayerWalking,

		TileSet
	};

	enum class  FontID
	{
		Main,
		Label
	};

	enum class SoundEffectID
	{
		Button,
	};
	template <typename Resource, typename Identifier>
	class ResourceHolder;

	using TextureHolder = ResourceHolder<sf::Texture, TextureID>;
	using FontHolder = ResourceHolder<sf::Font, FontID>;
	using SoundBufferHolder = ResourceHolder<sf::SoundBuffer, SoundEffectID>;
}