#pragma once
#include "GameObject/StaticObject/InteractableObject.h"

class PopCatGift : public InteractableObject
{
public:
	PopCatGift(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) override;
};