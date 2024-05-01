#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class Wall : public StaticObject
{
public:
	Wall(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) override;
};