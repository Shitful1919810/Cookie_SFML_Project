#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <queue>
#include <cassert>
namespace Shitful
{
	using Receiver = unsigned int;
	class SceneNode;
	namespace Category
	{
		enum Type
		{
			None = 0,
			Scene = 1 << 0,
			Player = 1 << 1,
			Allied = 1 << 2,
			Enemy = 1 << 3,
			ParticleSystem = 1 << 4,
			SoundEffect = 1 << 5,

			Alive = Player | Allied | Enemy,
		};
	}

	struct Command
	{
		std::function<void(SceneNode&, sf::Time)> action;
		Receiver category;		// ��flag������Command�ĸ���Ķ������࣬ʹ��|��&��λ����������

		Command() : action(), category(Category::None) {}
	};

	class CommandQueue		// ��Queue�ļ򵥷�װ�������pop()�᷵��pop����Command
	{
	public:
		void push(const Command& command)
		{
			mQueue.emplace(command);
		}
		Command pop()
		{
			Command command = mQueue.front();
			mQueue.pop();
			return command;
		}
		bool isEmpty() const
		{
			{
				return mQueue.empty();
			}

		}
	private:
		std::queue<Command> mQueue;
	};


	template <typename GameObject, typename Function>
	std::function<void(SceneNode&, sf::Time)>
		derivedAction(Function fn)		// Downcast�Ҿ�ر�
	{
		return [=](SceneNode& node, sf::Time dt)
		{
			// Check if cast is safe
			assert(dynamic_cast<GameObject*>(&node) != nullptr);
			// Downcast node and invoke function on it
			fn(static_cast<GameObject&>(node), dt);
		};
	}
}