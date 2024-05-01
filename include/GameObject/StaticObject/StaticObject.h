#pragma once
#include "GameObject/GameObject.h"

class StaticObject: public GameObject
{
public:
	StaticObject() = default;
	StaticObject(const sf::Sprite&);
	virtual void handleCollusion(Mouse&) {};
	virtual void handleCollusion(Wall&) {}
	virtual void handleCollusion(Cheese&) {}
	virtual void handleCollusion(Key&) {}
	virtual void handleCollusion(Door&) {}
	virtual void handleCollusion(Cat&) {}
	virtual void handleCollusion(LifeGift&) {}
	virtual void handleCollusion(PopCatGift&) {}
	virtual void handleCollusion(FreezeGift&){}
	virtual void handleCollusion(TimeGift&) {}
};