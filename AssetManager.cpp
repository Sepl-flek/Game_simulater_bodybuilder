#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
	auto& texMap = sInstance->m_Textures;
	auto pairFound = texMap.find(filename);
	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else 
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& filename)
{
	auto& sMap = sInstance->m_SoundBuffers;
	auto pairFound = sMap.find(filename);
	if (pairFound != sMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& sound = sMap[filename];
		sound.loadFromFile(filename);
		return sound;
	}
}

sf::Font& AssetManager::GetFont(std::string const& filename)
{
	auto& fMap = sInstance->m_Fonts;
	auto pairFound = fMap.find(filename);
	if (pairFound != fMap.end())
	{
		return pairFound->second;
	}
	else
	{
		auto& found = fMap[filename];
		found.loadFromFile(filename);
		return found;
	}
}
