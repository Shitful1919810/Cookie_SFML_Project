#include "Scene.h"
#include "Command.h"
#include "Utilities.h"

Shitful::SceneNode::SceneNode(Category::Type category)
	: mChildren()
	, mParent(nullptr)
	, mDefaultCategory(category)
{
}

void Shitful::SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.emplace_back(std::move(child));
}

Shitful::SceneNode::Ptr Shitful::SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p) -> bool { return p.get() == &node; });
	assert(found != mChildren.end());
	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void Shitful::SceneNode::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

sf::Transform Shitful::SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;
	return transform;
}

sf::FloatRect Shitful::SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

void Shitful::SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);
	for (Ptr& child : sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs);
}

void Shitful::SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node)
		&& !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));
	for (Ptr& child : mChildren)
		child->checkNodeCollision(node, collisionPairs);
}

bool Shitful::SceneNode::isMarkedForRemoval() const
{
	return isDestroyed();
}

bool Shitful::SceneNode::isDestroyed() const
{
	return false;
}

void Shitful::SceneNode::removeWrecks()
{
	auto wreckfieldBegin = std::remove_if(mChildren.begin(),
		mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());
	//std::for_each(mChildren.begin(), mChildren.end(),
		//std::mem_fn(&SceneNode::removeWrecks));
	for (auto& child : mChildren)
		child->removeWrecks();
}

sf::Vector2f Shitful::SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

Shitful::Receiver Shitful::SceneNode::getCategory() const
{
	return mDefaultCategory;
}

void Shitful::SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);
	for (const Ptr& child : mChildren)
		child->onCommand(command, dt);
}

void Shitful::SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);
}

void Shitful::SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Shitful::SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& pChild : mChildren)
		pChild->draw(target, states);
}

void Shitful::SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
}

void Shitful::SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
	for (const Ptr& pChild : mChildren)
		pChild->update(dt, commands);
}

void Shitful::SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

bool Shitful::collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float Shitful::distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}
