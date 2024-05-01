#include "GameController.h"
#include "ResourcesManager.h"
#include "GameObject/StaticObject/Cheese.h"
#include "GameObject/StaticObject/Key.h"
#include "GameObject/StaticObject/LifeGift.h"
#include "GameObject/StaticObject/popCatGift.h"
#include "GameObject/StaticObject/FreezeGift.h"
#include "GameObject/StaticObject/TimeGift.h"

/*================== Level constructor =================*/
Level::Level(GameController& game): m_game(game), m_startTime(0), m_curTime(0)
{
	m_spawnGiftTime = RAND_GIFT_SEC;
	m_cheese = 0;
	srand((unsigned int)time(nullptr));
	m_startTime = (float)80 + rand() % 60; //random level timer in range 20 - 70 seconds
}

/*================== initLevel =================*/
void Level::initLevel(std::ifstream &level)
{
	resetMembers();

	auto board = std::vector <std::string >();
	auto line = std::string();

	while (std::getline(level, line))
	{
		board.push_back(line);
	}

	for (size_t i = 0; i < board.size(); ++i)
	{
		initObjects(board.at(i), (float)i);
	}
}

/*================== resetMembers =================*/
void Level::resetMembers()
{
	m_objects.clear();
	m_objects.shrink_to_fit();
	m_doors.clear();
	m_doors.shrink_to_fit();
	m_walls.clear();
	m_walls.shrink_to_fit();
	
	m_cheese = 0;
	m_curTime = m_startTime;
	m_spawnGiftTime = RAND_GIFT_SEC;
}

/*================== initObjects =================*/
void Level::initObjects(const std::string line, float row)
{
	char c;
	auto sprite = sf::Sprite();

	for (size_t col = 0; col < line.size(); ++col)
	{
		//sprite size is 32*32 because of the "setOrigin" to the middle adding +16 place the sprites 
		//in the wanted pos. first 6 cols used for the gameInfo, first row used for buttons placement
		auto pos = sf::Vector2f((float)(col + 6) * PIXELS + 16, (row + 1) * PIXELS + 16);

		c = line[col];
		switch (c)
		{
		case '%':
			m_game.initMouseOrCat(pos, c);
			break;

		case '^':
			m_game.initMouseOrCat(pos, c);
			break;

		case '#':
			sprite = createSprite(WALL, pos);
			m_walls.emplace_back(sprite);
			break;
		
		case '*':
			sprite = createSprite(CHEESE, pos);
			m_objects.push_back(new Cheese(sprite));
			++m_cheese;
			break;

		case 'F':
			sprite = createSprite(KEY, pos);
			m_objects.push_back(new Key(sprite));
			break;

		case 'D':
			sprite = createSprite(DOOR, pos);
			m_doors.emplace_back(sprite);
			break;


		default:
			break;
		}
	}
}

/*================== drawLevel =================*/
void Level::drawLevel(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_walls.size(); ++i)
	{
		m_walls.at(i).drawObject(window);
	}
	for (size_t i = 0; i < m_doors.size(); ++i)
	{
		m_doors.at(i).drawObject(window);
	}
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		m_objects.at(i)->drawObject(window);
	}
}

/*================== timeLeft =================*/
int Level::timeLeft()const
{
	return (int)m_curTime;
}
/*================== spawnGift =================*/
/**----------------------------------------------
 * every 15 seconds (a random gift out of the four gift will be spawn
   into the game board and will be contained in Interatable object vetor
 *---------------------------------------------**/
void Level::spawnGift()
{
	if ((int)m_spawnGiftTime > 0) return; // the time of spawning gift havnt pass yet

	InteractableObject* gift = nullptr; //no gift have bean grill yet
	
	sf::Sprite sprite;
	auto randomGift =(Gifts) rand() % GIFT;

	//again - the position is because of the set Origin
	switch (randomGift)
	{
	case POP_CAT_GIFT:
		sprite = createSprite(POP, { 213,PIXELS + 16});
		gift = new PopCatGift(sprite);
		randomPosGift(gift);
		m_objects.push_back(gift);
		break;

	case LIFE_GIFT:
		sprite = createSprite(LIVES, { 213,PIXELS +16 });
		gift = new LifeGift(sprite);
		randomPosGift(gift);
		m_objects.push_back(gift);
		break;

	case FREEZE_GIFT:
		sprite = createSprite(FREEZE, { 213,PIXELS + 16 });
		gift = new FreezeGift(sprite);
		randomPosGift(gift);
		m_objects.push_back(gift);
		break;

	case TIME_GIFT:
		sprite = createSprite(TIMER, { 213,PIXELS + 16 });
		gift = new TimeGift(sprite);
		randomPosGift(gift);
		m_objects.push_back(gift);
		break;
	}

	m_spawnGiftTime = RAND_GIFT_SEC;
}

/*================== randomPosGift =================*/
/**----------------------------------------------
 * the gift will be spawn ONLY in the game board erea
 *---------------------------------------------**/
void Level::randomPosGift(InteractableObject* gift)
{
	auto sprite = sf::Sprite();
	float randX, randY;

	while (checkCollusion(*gift))
	{
		randX = (float)(213 + rand() % 1083);
		randY = (float)(PIXELS + 16 + rand() % 704);
		gift->setPosition({ randX, randY });
	}
}

/*================== checkCollusion =================*/
/**----------------------------------------------
 * this function is beign use by the mouse and by the one og the gifts only.
 ** if the GameObject is a mouse then there are handle collusions involve
 *** if the GameObject is one of the gifts then this function is being used only to know
	 if there is any collusion - if so a gift cannot be spawn there
*---------------------------------------------**/
bool Level::checkCollusion(GameObject& object)
{
	bool isMouse = (dynamic_cast<Mouse*>(&object) != nullptr);
	sf::FloatRect intersectRect(0, 0, 0, 0);

	for (size_t i = 0; i < m_walls.size(); ++i) //check collusion with walls
	{
		if (m_walls[i].isCollusion(object, intersectRect))
		{
			return true;
		}
	}

	for (size_t i = 0; i < m_doors.size(); ++i) //check collusion with doors
	{
		if (m_doors[i].isCollusion(object, intersectRect))
		{
			if (!isMouse) return true;

			m_doors[i].handleCollusion(object);
			if (m_doors[i].isRemoved()) m_doors.erase(m_doors.begin() + i);
			return true;
		}
	}
	for (size_t i = 0; i < m_objects.size(); ++i) //check collusion with the interactable objects
	{
		if (m_objects[i]->isCollusion(object, intersectRect))
		{
			if (!isMouse) return true;

			m_objects[i]->handleCollusion(object);
			delete m_objects[i];
			m_objects.erase(m_objects.begin() + i);
			return true;
		}
	}
	return false;
}

/*================== setCheese =================*/
void Level::setCheese(int num)
{
	m_cheese += num;
}

/*================== getCheese =================*/
int Level::getCheese() const
{
	return m_cheese;
}

/*================== reduseTimers =================*/
void Level::reduseTimers(float seconds)
{
	if (m_curTime >= 0) m_curTime -= seconds;
	if (m_spawnGiftTime >= 0) m_spawnGiftTime -= seconds;
}

/*================== addTime =================*/
//timeGift was taken
void Level::addTime(int seconds)
{
	m_curTime += seconds;
}

/*================== getWalls =================*/
// being used for BFS algorithm in cats movement
vector<Wall> Level::getWalls()const
{
	return m_walls;
}

/*================== getDoors =================*/
// being used for BFS algorithm in cats movement
vector<Door> Level::getDoors() const
{
	return m_doors;
}

/*================== createSprite =================*/
sf::Sprite Level::createSprite(const Textures type, const sf::Vector2f& pos)
{
	sf::Texture& texture = ResourcesManager::instance().getTexture(type);
	sf::Sprite sprite(texture);
	sprite.setPosition(pos);
	return sprite;
}