#pragma once
#include "GUI.h"
#include "ResourceIdentifiers.h"
namespace Shitful
{
    namespace GUI
    {
        class Label : public Component
        {
        public:
            using Ptr = std::shared_ptr<Label>;


        public:
            Label(const std::string& text, const FontHolder& fonts,float outlineThickness = 0.f, const sf::Color& outlineColor = sf::Color::Black);

            virtual bool isSelectable() const;
            void setText(const std::string& text);
            void setOutlineThickness(float thickness);
            void setOutlineColor(const sf::Color& color);
            virtual void handleEvent(const sf::Event& event);


        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        private:
            sf::Text mText;
            float mOutlineThickness;
            sf::Color mOutlineColor;
        };
    }
}