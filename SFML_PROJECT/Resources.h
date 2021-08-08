#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <array>
#include <exception>
namespace Shitful
{
	template<typename Resource, typename Identifier>
	class ResourceHolder
	{
	public:
		void load(Identifier id, const std::string& filename);
		template <typename Parameter>
		void load(Identifier id, const std::string& filename, const Parameter& secondParam);	// ����ͼ����Դ��loadFromFile�ڶ�������ָ����ȡ���򣻶�����ɫ�������ļ����ڶ�������ָ����ɫ������
		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;
	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
	};

}



template<typename Resource, typename Identifier>
void Shitful::ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& Shitful::ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *(found->second);
}
template <typename Resource, typename Identifier>
const Resource& Shitful::ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *(found->second);
}


template <typename Resource, typename Identifier>
template <typename Parameter>
void Shitful::ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}