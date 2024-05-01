#pragma once
#include "GameController.h"
#include "consts.h"
#include <vector>

using std::vector;

class Menu
{
public:
	Menu();
	void runMenu();

private:
	void showMenu();
	void handleButtonPress(sf::Event::MouseButtonEvent& click);
	void handleKeyPress(sf::Event::KeyEvent& press);
	void showHelp();

	sf::RenderWindow m_window;
	GameController m_game;
	vector<sf::Sprite> m_buttons;
	
	bool m_gameRun;
	bool m_gameOver;
	bool m_help;
	bool m_help1Page;
};