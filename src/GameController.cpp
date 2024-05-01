#include <iostream>
#include <string>
#include "GameController.h"
#include "Menu.h"
#include "ResourcesManager.h"

/*================== GameController constructor =================*/
GameController::GameController(Menu& menu) : m_menu(menu),m_level(*this), m_mouse(*this, m_level),
							m_freeze(false), m_freezeCatTime(0),m_curLevel(0), m_catsAmount(0)
{
	//init mouse
	auto mouse = sf::Sprite(ResourcesManager::instance().getTexture(MOUSE));
	mouse.setOrigin(mouse.getGlobalBounds().width / 2, mouse.getGlobalBounds().height / 2);
	m_mouse.setSprite(mouse);

	auto playlist = std::ifstream("Playlist.txt");
	auto LevelName = std::string();
	
	//all level numbers will be contain in that vector 
	int num = 0;
	m_levelsNum.push_back(num++);
	while (std::getline(playlist, LevelName))
	{
		m_levelsNum.push_back(num++);
	}
}

/*================== updateGame =================*/
/**----------------------------------------------
 * if the game is running this function update the game
   by showing the info, the objects of the game and the entities
 
 * updates the Menu if the game is over or not
 *---------------------------------------------**/
bool GameController::updateGame(sf::RenderWindow& window, sf::Clock &clock, sf::Time& delta)
{
	showGameInfo(window);
	updateLevel(window, clock);
	moveEntities(window, clock,delta);
	
	return (isGameOver());
}

/*================== showGameInfo =================*/
void GameController::showGameInfo(sf::RenderWindow& window)
{
	auto sprite = sf::Sprite();
	auto string = std::string();

	sprite = createSprite(BACKGROUND, { 192,PIXELS }); //board background
	window.draw(sprite);

	sprite = createSprite(INFO, { 0,PIXELS }); //game info background
	window.draw(sprite);

	//show score
	m_info.showInfoText(window, { 90, 130 }, m_mouse.getScore());
	//show lives
	for (int i = 0; i < m_mouse.getLives(); ++i)
	{
		m_info.showInfoSprite(window, LIVES, { (float)(i + 1) * PIXELS + 16, 220 });
	}
	//show level
	m_info.showInfoText(window, { 120, 375 }, (int)m_curLevel);
	//show cheese
	m_info.showInfoSprite(window, CHEESE, { 40 , 460 });
	m_info.showInfoText(window, { 80, 460 }, m_level.getCheese());
	//show keys
	m_info.showInfoSprite(window, KEY, { 40 , 560 });
	m_info.showInfoText(window, { 80, 560 }, m_mouse.getKeys());
	//show timer
	m_info.showInfoSprite(window, TIMER, { 40 , 650 });
	m_info.showTimer(window, m_level.timeLeft());

}

/*================== updateLevel =================*/
void GameController::updateLevel(sf::RenderWindow& window, sf::Clock& clock)
{
	if (m_level.getCheese() == 0)
	{
		m_curLevel++;
		resetCats();
		m_mouse.resetKeys();
		openLevelFile();
	}
	//update level
	m_level.drawLevel(window);
	m_level.reduseTimers(clock.getElapsedTime().asSeconds());
	timerCheck();
	m_level.spawnGift();
}

/*================== moveEntities =================*/
void GameController::moveEntities(sf::RenderWindow& window, sf::Clock& clock, sf::Time& delta)
{
	checkCatsFreeze(clock.getElapsedTime().asSeconds());
	for (size_t i = 0; i < m_cats.size(); ++i)
	{
		if (!m_freeze)
		{
			m_cats[i].setDirections(m_mouse, m_level);
			m_cats[i].move(delta.asSeconds());
		}
		m_cats[i].drawObject(window);
	}
	m_mouse.setDirections();
	m_mouse.move(delta.asSeconds());
	m_level.checkCollusion(m_mouse);
	m_mouse.drawObject(window);
}

/*================== initMouseOrCat =================*/
void GameController::initMouseOrCat(sf::Vector2f& pos, char c)
{
	if (c == '%')
	{
		m_mouse.setPosition(pos);
		m_mouse.setStartPos(pos);
	}
	else
	{
		auto cat = sf::Sprite(ResourcesManager::instance().getTexture(CAT));

		cat.setPosition(pos);
		m_cats.emplace_back(cat);
		m_cats.back().setStartPos(pos);

	}
}

/*================== openLevelFile =================*/
void GameController::openLevelFile()
{
	if (m_curLevel > 1)
	{
		int score = (int)END_LEVEL;
		score += m_catsAmount * 5;
		playSound(LEVEL_PASS);
		m_mouse.setScore(score);
	}

	//load new level
	auto levelFile = std::ifstream();
	auto LevelName = std::string("level00");

	LevelName += ((std::to_string(m_levelsNum.at(m_curLevel))) += ".txt");
	levelFile.open(LevelName);

	checkFile(levelFile);

	m_level.initLevel(levelFile);
	m_catsAmount = (int)m_cats.size();
}

/*================== initCatsToStartPos =================*/
void GameController::initCatsToStartPos()
{
	for (size_t i = 0; i < m_cats.size(); ++i)
	{
		m_cats[i].setPosition(m_cats[i].getStartPos());
	}
}

/*================== popCat =================*/
void GameController::popCat()
{
	playSound(POP_CAT_S);
	if (m_cats.size() > 0) m_cats.pop_back();
}

/*================== checkCatsFreeze =================*/
void GameController::checkCatsFreeze(float seconds)
{
	if (m_freeze && (int)m_freezeCatTime == 0)
	{
		setCatsColor(sf::Color::White);
		m_freeze = !m_freeze;
	}
	if (m_freeze && (int)m_freezeCatTime > 0)
	{
		m_freezeCatTime -= seconds;
	}
}

/*================== freezeCats =================*/
void GameController::freezeCats()
{
	playSound(FREEZE_S);
	m_freeze = true;
	m_freezeCatTime = FREEZE_TIME;
	setCatsColor(sf::Color::Cyan);
}

/*================== setCatsColor =================*/
/**----------------------------------------------
 * if the cats are frozen than their color is Cyan
 * if the cats were frozen but the freeze time is up the color is white (regular)
 *---------------------------------------------**/
void GameController::setCatsColor(const sf::Color& color)
{
	sf::Sprite sprite;
	for (auto& cat : m_cats)
	{
		sprite = cat.getSprite();
		sprite.setColor(color);
		cat.setSprite(sprite);
	}
}

/*================== timerCheck =================*/
void GameController::timerCheck()
{
	if (m_level.timeLeft() > 0)
	{
		return;
	}

	// time's up level is about to restart
	std::string levelName("Level00");
	levelName += (std::to_string(m_levelsNum.at(m_curLevel))) += ".txt";
	ifstream levelfile;
	levelfile.open(levelName);
	
	//reset mouse and cat, read same level again
	playSound(LOST_LIFE_S);
	resetCats();
	m_mouse.runOutOfTime();
	m_level.initLevel(levelfile);
}

/*================== resetCats =================*/
void GameController::resetCats()
{
	m_cats.clear();
	m_cats.shrink_to_fit();
}

/*================== createSprite =================*/
sf::Sprite GameController::createSprite(const Textures type,const sf::Vector2f& pos)
{
	sf::Sprite sprite = sf::Sprite(ResourcesManager::instance().getTexture(type));
	sprite.setPosition(pos);
	return sprite;
}

/*================== checkFile =================*/
void GameController::checkFile(std::ifstream& file) const
{
	if (!file.is_open())
	{
		std::cerr << "error - Couldn't open the file!";
		exit(1);
	}
}

/*================== playSound =================*/
void GameController::playSound(const Sounds type)
{
	m_sound.setBuffer(ResourcesManager::instance().getSound(type));
	m_sound.play();
}

/*================== isGameOver =================*/
bool GameController::isGameOver()const
{
	if (m_mouse.getLives() == 0) return true;
	if (m_level.getCheese() == 0 && m_curLevel + 1 == m_levelsNum.size()) return true;

	return false;
}

/*================== gameOver =================*/
void GameController::gameOver(sf::RenderWindow& window)
{
	//Game Over background
	auto sprite = sf::Sprite(ResourcesManager::instance().getTexture(GAME_OVER));
	window.draw(sprite);
	m_level.resetMembers();
	m_info.showFinalResult(window,(int)m_curLevel, m_mouse.getScore());
}

/*================== newGame =================*/
//NEW GAME button was pressed
void GameController::newGame()
{
	m_curLevel = 1;
	resetCats();
	m_mouse.resetMouse();
	openLevelFile();
}