#pragma once
#include "GameObject/GameObject.h"

class Entity : public GameObject
{
public:
	Entity();
	Entity(const sf::Sprite&, const Directions, float);
	void setDirection(const Directions);
	void setSpeed(float);
	Directions getDirection() const;
	void setStartPos(const sf::Vector2f&);
	sf::Vector2f getStartPos()const;
	void move(float delta);
	void moveHead();

	virtual void handleCollusion(Mouse&) {}
	virtual void handleCollusion(Cheese&) {}
	virtual void handleCollusion(Key&) {}
	virtual void handleCollusion(Door&) {}
	virtual void handleCollusion(Cat&) {}
	virtual void handleCollusion(Wall&) {}
	virtual void handleCollusion(LifeGift&) {}
	virtual void handleCollusion(PopCatGift&) {}
	virtual void handleCollusion(FreezeGift&) {}
	virtual void handleCollusion(TimeGift&) {}

private:
	Directions m_direction;
	bool m_headDirectionLeft;
	float m_speed;
	sf::Vector2f m_startPos;
};