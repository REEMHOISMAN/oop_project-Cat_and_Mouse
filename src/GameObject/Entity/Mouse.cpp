#include "GameObject/Entity/Mouse.h"
#include "GameController.h"
#include <iostream>

/*================== Mouse constructor =================*/
Mouse::Mouse(GameController& game, Level& level) : 
			m_game(game), m_level(level), m_keys(0), m_lives(3), m_score(0) {}

/*================== setDirections =================*/
void Mouse::setDirections()
{
	auto newPos = sf::Vector2f(0, 0);
	auto direction = Directions();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction = UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction = DOWN;
	}
	else
	{
		direction = NONE;
	}
	setDirection(direction);
}

/*================== setScore ================*/
void Mouse::setScore(int score)
{
	m_score += score;
}

/*================== getScore ================*/
int Mouse::getScore() const
{
	return m_score;
}

/*================== getLives ================*/
int Mouse::getLives() const
{
	return m_lives;
}

/*================== resetKeys ================*/
void Mouse::resetKeys()
{
	m_keys = 0;
}

/*================== getKeys ================*/
int Mouse::getKeys() const
{
	return m_keys;
}

/*================== resetMouse ================*/
/**----------------------------------------------
 * in case the user wants a new game 
 *---------------------------------------------**/
void Mouse::resetMouse()
{
	m_keys = 0;
	m_lives = 3;
	m_score = 0;
}

/*================== runOutOfTime ================*/
void Mouse::runOutOfTime()
{
	m_lives--;
	m_keys = 0;
}

/*================== handleCollusion (GameObject) ================*/
void Mouse::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}

/*================== handleCollusion (Cheese) ================*/
void Mouse::handleCollusion(Cheese&)
{
	m_level.setCheese(-1);
	m_game.playSound(EAT_CHEESE_S);
	m_score += (int)EAT_CHEESE;
}

/*================== handleCollusion (Key) ================*/
void Mouse::handleCollusion(Key&)
{
	m_game.playSound(KEY_S);
	m_keys++;
}

/*================== handleCollusion (Door) ================*/
void Mouse::handleCollusion(Door& door)
{
	if (m_keys > 0)
	{
		m_keys--;
		m_game.playSound(DOOR_S);
		m_score+= (int)OPEN_DOOR;
		door.removeObject();
	}
}

/*================== handleCollusion (LifeGift) ================*/
void Mouse::handleCollusion(LifeGift&)
{
	if (m_lives < 3)
	{
		m_game.playSound(LIFE_S);
		m_lives++;
		m_score += (int)TAKE_GIFT;
	}
}

/*================== handleCollusion (PopCatGift) ================*/
void Mouse::handleCollusion(PopCatGift&)
{
	m_game.popCat();
	m_score += (int)TAKE_GIFT;
}

/*================== handleCollusion (FreezeGift) ================*/
void Mouse::handleCollusion(FreezeGift&)
{
	m_game.freezeCats();
	m_score += (int)TAKE_GIFT;
}

/*================== handleCollusion (TimeGift) ================*/
void Mouse::handleCollusion(TimeGift&)
{
	m_game.playSound(TIMER_S);
	m_level.addTime(EXTRA_TIME);
	m_score += (int)TAKE_GIFT;
}

/*================== handleCollusion (Cat) ================*/
void Mouse::handleCollusion(Cat&)
{
	m_game.playSound(LOST_LIFE_S);
	setPosition(getStartPos());
	m_game.initCatsToStartPos();
	m_lives--;
}