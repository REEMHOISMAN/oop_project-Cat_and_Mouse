#pragma once
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class ResourcesManager
{
public:
	static ResourcesManager& instance();

	sf::Texture& getTexture(const Textures);
	sf::Font& getFont();
	sf::SoundBuffer& getSound(const Sounds);

private:
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager&operator=(const ResourcesManager&) = delete;
	ResourcesManager();
	void initTextures();
	void initSounds();
	void failedLoad(const std::string) const;
	
	sf::Texture m_textures[TEXTURES];
	sf::SoundBuffer m_sounds[SOUNDS];
	sf::Font m_font;
};