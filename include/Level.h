#pragma once
#include "GameObject/StaticObject/Wall.h"
#include "GameObject/StaticObject/Door.h"
#include <vector>

class GameController;
class Mouse;
class InteractableObject;

using std::vector;

class Level
{
public:
	Level(GameController&);
	void initLevel(std::ifstream&);
	void drawLevel(sf::RenderWindow&);
	int timeLeft()const;
	void spawnGift();
	bool checkCollusion(GameObject&);
	void setCheese(int);
	int getCheese() const;
	void reduseTimers(float);
	void addTime(int seconds);
	vector <Wall> getWalls()const;
	vector <Door> getDoors()const;
	void resetMembers();

private:
	void initObjects(const std::string, float);
	void randomPosGift(InteractableObject*);
	sf::Sprite createSprite(const Textures, const sf::Vector2f&);

	GameController& m_game;
	vector <InteractableObject*> m_objects;
	vector <Wall> m_walls;
	vector <Door> m_doors;
	std::string m_level;
	int m_cheese;
	float m_curTime;
	float m_startTime;
	float m_spawnGiftTime;
};