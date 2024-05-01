#include "GameObject/Entity/Cat.h"
#include "GameController.h"
#include "Level.h" //inorder to get the walls and doors
#include <iostream>
#include <queue>

/*================== Cat constructor =================*/
Cat::Cat(sf::Sprite& cat) : Entity::Entity(cat, LEFT, CAT_SPEED){}

/*================== setDirections =================*/
/**----------------------------------------------
 * the next direction of the cat depend on what the
 * shortest path to the cat. using BFS - by marking the shortest
   path to the mouse - the cat knows what the next step suppose to be
   ***more info about the BFS using in README*** 
 *---------------------------------------------**/
void Cat::setDirections(Mouse &mouse, Level &level)
{
	auto doors = level.getDoors();
	auto walls = level.getWalls();
	
	//one matrix of Vector2f inorder to know what position lead to the current position
	//second matrix (boolian) inorder to know if a position has been checked already
	//both matrix sizes are - the game board size / 32  -->(size of each object in the game beside the mouse)
	vector<vector <sf::Vector2f>> positions(22, vector<sf::Vector2f>(34, { -1,-1 }));
	vector<vector <bool>> visited(22, vector<bool>(34, false));
	std::queue < sf::Vector2f> queue;

	//cat cannot go through walls or doors
	initWallsAndDoorsAsVisited(visited, walls, doors);
	
	//the starting position is the cat position
	auto catPos = getPosition();
	auto direction = getDirection();

	//because of the origin of the cat and the mouse
	//considering mouse size's is 28*28 so half of it need to be added 
	if (direction == LEFT || direction == UP)
	{
		catPos.x += 14;
		catPos.y += 14;
	}
	else
	{
		catPos.x -= 14;
		catPos.y -= 14;
	}

	//the actual BFS algorithm - details in README
	queue.push(catPos);
	while (!queue.empty())
	{
		auto pos = queue.front();
		queue.pop();

		size_t x = (size_t)pos.x / 32 - 6;
		size_t y = (size_t)pos.y / 32 - 1;
		if (pos == mouse.getPosition()) //mouse have been found
		{
			break;
		}

		if (visited.at(y).at(x + 1) == false &&
			!valid(positions.at(y).at(x + 1)))
		{
			queue.push({ pos.x + 32, pos.y });
			visited.at(y).at(x + 1) = true;
			positions.at(y).at(x + 1) = pos;
		}

		if (visited.at(y).at(x - 1) == false &&
			!valid(positions.at(y).at(x - 1)))
		{
			queue.push({ pos.x - 32, pos.y });
			visited.at(y).at(x - 1) = true;
			positions.at(y).at(x - 1) = pos;
		}

		if (visited.at(y + 1).at(x) == false &&
			!valid(positions.at(y + 1).at(x)))
		{
			queue.push({ pos.x, pos.y + 32});
			visited.at(y + 1).at(x) = true;
			positions.at(y + 1).at(x) = pos;
		}

		if (visited.at(y - 1).at(x) == false &&
			!valid(positions.at(y - 1).at(x)))
		{
			queue.push({ pos.x, pos.y -32});
			visited.at(y - 1).at(x) = true;
			positions.at(y - 1).at(x) = pos;
		}
	}
	auto mousePos = mouse.getPosition();
	//the cat is surrounded by walls or door - dont have path to the mouse so it will stay static
	if (visited.at((size_t)mousePos.y / 32 - 1).at((size_t)mousePos.x / 32 - 6) == false)
	{
		setDirection(NONE);
		return;
	}

	auto pos = mousePos;
	sf::Vector2f nextMove;
	
	//travel on the position matrix we built until the next move is the cat position
	// he we stop -> because where we are at now it the next direction of the cat!
	while (pos != catPos)
	{
		nextMove = pos;
		pos = positions.at((size_t)pos.y / 32 - 1).at((size_t)pos.x / 32 - 6);
	}

	//if cat reaches the mouse
	if (mousePos == nextMove)
	{
		handleCollusion(mouse);
		return;
	}
	
	//set the next direction (in Entity class)
	if (nextMove.x != catPos.x)
	{
		nextMove.x > catPos.x ? setDirection(RIGHT) : setDirection(LEFT);
	}
	else
	{
		nextMove.y > catPos.y ? setDirection(DOWN) : setDirection(UP);
	}
}

/*================== initWallsAndDoorsAsVisited =================*/
void Cat::initWallsAndDoorsAsVisited(vector<vector<bool>>& visited, vector<Wall> walls, vector<Door>doors)
{
	sf::Vector2f pos;

	for (size_t i = 0; i < walls.size(); ++i)
	{
		pos = walls[i].getPosition();
		visited.at((size_t)pos.y / 32 - 1).at((size_t)pos.x / 32 - 6) = true;
	}

	for (size_t i = 0; i < doors.size(); ++i)
	{
		pos = doors[i].getPosition();
		visited.at((size_t)pos.y / 32 - 1).at((size_t)pos.x / 32 - 6) = true;
	}
}

/*================== valid =================*/
/**----------------------------------------------
 * at the beginning we set all positions to {-1,-1}
 * if the position isn't {-1,-1} its mean that there is not 
 * a position that lead to that position yet - so its valid
 *---------------------------------------------**/
bool Cat::valid(const sf::Vector2f pos)
{
	return pos != sf::Vector2f{ -1, -1 };
}

/*================== handleCollusion =================*/
void Cat::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}