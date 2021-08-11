#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
namespace Shitful
{
	class PatternSwitcher
	{
	public:
		template<typename P>
		PatternSwitcher(P& pattern);
		template<typename P>
		void switchTo(P& pattern);
		sf::Transformable& getTransformable() const;
		sf::Drawable& getDrawable() const;
	private:
		sf::Transformable* transformable;
		sf::Drawable* drawable;
	};



	template<typename P>
	inline PatternSwitcher::PatternSwitcher(P& pattern)
	{
		switchTo(pattern);
	}


	template<typename P>
	inline void PatternSwitcher::switchTo(P& pattern)
	{
		assert(dynamic_cast<sf::Transformable*>(&pattern));
		assert(dynamic_cast<sf::Drawable*>(&pattern));
		transformable = &pattern;
		drawable = &pattern;
	}
}