#pragma once
#include "Command.h"
#include <set>
#include <utility>

namespace Shitful
{

	class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable		// ʵ������ÿһ���ڵ�����궼������ڸ��ڵ���������
	{
	public:
		using Ptr = std::unique_ptr<SceneNode>;
		using Pair = std::pair<SceneNode*, SceneNode*>;

	public:
		explicit SceneNode(Category::Type category = Category::None);
		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);
		void update(sf::Time dt, CommandQueue& commands);
		sf::Vector2f getWorldPosition() const;
		virtual Receiver getCategory() const;
		void onCommand(const Command& command, sf::Time dt);
		sf::Transform getWorldTransform() const;	// ͨ��һ��һ�����ݵ����ڵ���������˽ڵ��ʵ������

		virtual sf::FloatRect getBoundingRect() const;
		void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
		void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);

		virtual bool isMarkedForRemoval() const;
		virtual bool isDestroyed() const;
		void removeWrecks();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;	// ͨ���ݹ������draw����ÿ���ڵ�

		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		void updateChildren(sf::Time dt, CommandQueue& commands);			// ͨ���ݹ������update����ÿ���ڵ�
		void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector<Ptr> mChildren;
		SceneNode* mParent;
		Category::Type mDefaultCategory;
	};

	bool collision(const SceneNode& lhs, const SceneNode& rhs);
	float distance(const SceneNode& lhs, const SceneNode& rhs);
}