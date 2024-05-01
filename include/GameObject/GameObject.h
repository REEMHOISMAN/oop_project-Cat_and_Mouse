#pragma once
#include <SFML/Graphics.hpp>
#include "consts.h"

class Wall;
class Mouse;
class Cat;
class Cheese;
class Door;
class Key;
class Gift;
class LifeGift;
class PopCatGift;
class FreezeGift;
class TimeGift;


class GameObject
{
public:
	GameObject() = default;
	GameObject(const sf::Sprite&);
	virtual ~GameObject() = default;
	void drawObject(sf::RenderWindow &)const;
	sf::Vector2f getPosition()const;
	void setPosition(const sf::Vector2f&);
	sf::FloatRect getGlobalBounding()const;
	sf::Sprite& getSprite();
	void setSprite(const sf::Sprite &);
	void scaleSprite(const sf::Vector2f&);
	bool isCollusion(GameObject&, sf::FloatRect&);

	virtual void handleCollusion(GameObject&) = 0;
	virtual void handleCollusion(Wall&) = 0;
	virtual void handleCollusion(Mouse &) = 0;
	virtual void handleCollusion(Cheese&) = 0;
	virtual void handleCollusion(Key&) = 0;
	virtual void handleCollusion(Door&) = 0;
	virtual void handleCollusion(Cat&) = 0;
	virtual void handleCollusion(LifeGift&) = 0;
	virtual void handleCollusion(PopCatGift&) = 0;
	virtual void handleCollusion(FreezeGift&) = 0;
	virtual void handleCollusion(TimeGift&) = 0;

private:
	sf::Sprite m_object;
};