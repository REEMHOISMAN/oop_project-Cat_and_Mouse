#pragma once
#include "GameObject/Entity/Entity.h"

using std::vector;
class Level;

class Cat : public Entity
{
public:
	Cat(sf::Sprite&);
	void setDirections(Mouse& , Level&);
	void initWallsAndDoorsAsVisited(vector<vector<bool>>&, vector<Wall> , vector<Door>);
	bool valid(const sf::Vector2f);

	virtual void handleCollusion(GameObject&);
};