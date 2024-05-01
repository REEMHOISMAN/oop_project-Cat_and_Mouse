#pragma once
#include <SFML/Graphics.hpp>
#include "consts.h"
#include <vector>

using std::vector;

class GameInfo
{
public:
	GameInfo() = default;
	void showInfoText(sf::RenderWindow&, const sf::Vector2f&,  int);
	void showInfoSprite(sf::RenderWindow&, const Textures, const sf::Vector2f&);
	void showTimer(sf::RenderWindow&, int);
	void showFinalResult(sf::RenderWindow&, int, int);
};