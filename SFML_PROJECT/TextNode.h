#pragma once
#include <string>
#include "ResourceIdentifiers.h"
#include "Scene.h"
namespace Shitful
{
    class TextNode : public SceneNode       // ��ʾ�ı�
    {
    public:
        explicit TextNode(const FontHolder& fonts, const std::string& text);
        void setString(const std::string& text);
        virtual bool isMarkedForRemoval() const;
        virtual Receiver getCategory() const;
        void destroy();
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::Text mText;
        bool isRemoved;
    };

}