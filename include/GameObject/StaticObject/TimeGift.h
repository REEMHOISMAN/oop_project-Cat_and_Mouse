#pragma once
#include "GameObject/StaticObject/InteractableObject.h"

class TimeGift : public InteractableObject
{
public:
	TimeGift(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) override;
};