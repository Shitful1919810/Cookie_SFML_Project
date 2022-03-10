#pragma once
#include "Command.h"
#include <set>
#include <utility>

namespace Shitful
{

	class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable		// 实体树，每一个节点的坐标都是相对于父节点的相对坐标
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
		sf::Transform getWorldTransform() const;	// 通过一步一步回溯到根节点来推算出此节点的实际坐标

		virtual sf::FloatRect getBoundingRect() const;
		void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
		void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);

		virtual bool isMarkedForRemoval() const;
		virtual bool isDestroyed() const;
		void removeWrecks();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;	// 通过递归调用来draw树上每个节点

		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		void updateChildren(sf::Time dt, CommandQueue& commands);			// 通过递归调用来update树上每个节点
		void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector<Ptr> mChildren;
		SceneNode* mParent;
		Category::Type mDefaultCategory;
	};

	bool collision(const SceneNode& lhs, const SceneNode& rhs);
	float distance(const SceneNode& lhs, const SceneNode& rhs);
}