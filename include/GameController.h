#pragma once
#include <fstream>
#include "Level.h"
//#include "GameObject/StaticObject/Wall.h"
#include "GameObject/Entity/Mouse.h"
#include "GameInfo.h"
#include "GameObject/Entity/Cat.h"
#include <SFML/Audio.hpp>

class Menu;

using std::ifstream;

class GameController
{
public:
	GameController(Menu&);
	bool updateGame(sf::RenderWindow& , sf::Clock& , sf::Time& );
	void initMouseOrCat(sf::Vector2f&, char);
	void initCatsToStartPos();
	void popCat();
	void freezeCats();
	void playSound(const Sounds);
	void gameOver(sf::RenderWindow&);
	void newGame();

private:
	void showGameInfo(sf::RenderWindow&);
	void updateLevel(sf::RenderWindow&, sf::Clock&);
	void moveEntities(sf::RenderWindow&, sf::Clock&, sf::Time&);
	void openLevelFile();
	void checkCatsFreeze(float);
	void setCatsColor(const sf::Color&);
	void timerCheck();
	void resetCats();
	void checkFile(std::ifstream&) const;
	sf::Sprite createSprite(const Textures, const sf::Vector2f&);
	bool isGameOver() const;


	Menu& m_menu;
	Mouse m_mouse;
	Level m_level;
	GameInfo m_info;
	
	sf::Sound m_sound;
	vector<int> m_levelsNum;
	vector <Cat> m_cats;
	bool m_freeze;
	float m_freezeCatTime;
	int m_catsAmount;
	size_t m_curLevel;
};