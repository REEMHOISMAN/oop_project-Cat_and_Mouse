#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class Door : public StaticObject
{
public:
	Door(const sf::Sprite&);
	void removeObject();
	bool isRemoved()const;
	virtual void handleCollusion(GameObject&) override;

private:
	bool m_removed;
};