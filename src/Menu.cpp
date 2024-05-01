#include "Menu.h"
#include "ResourcesManager.h"

/*================== Menu constructor =================*/
/**----------------------------------------------
 * initialize the buttons postion (so it'll fit to the menu background)  
 *---------------------------------------------**/
Menu::Menu() : m_game(*this), m_gameRun(false), m_gameOver(false), m_help(false), m_help1Page(false)
{
	m_window.create(sf::VideoMode(WIDTH, HEIGHT), "mouse and cat", sf::Style::None);

	m_buttons.emplace_back(sf::Sprite(ResourcesManager::instance().getTexture(NEW_GAME)));
	m_buttons.back().setPosition({ 580, 160 });

	m_buttons.emplace_back(sf::Sprite(ResourcesManager::instance().getTexture(HELP)));
	m_buttons.back().setPosition({ 580, 278 });

	m_buttons.emplace_back(sf::Sprite(ResourcesManager::instance().getTexture(EXIT)));
	m_buttons.back().setPosition({ 580, 396 });

	m_window.setFramerateLimit(60);
}

/*================== runMenu =================*/
/**----------------------------------------------
 * this function is being called from the "main.cpp".
 * control the whole program according to the user choice   
   (new game/ help/ exit)
 *---------------------------------------------**/
void Menu::runMenu()
{
	sf::Clock clock;
	sf::Time delta;
	sf::Music music;

	if (!music.openFromFile("music.ogg")) exit(1);
	music.setLoop(true);
	music.play();

	while (m_window.isOpen())
	{
		m_window.clear(sf::Color::Color(181, 229, 239)); // rgb of very light blue
		
		if (!m_help && !m_gameOver) showMenu(); // "help" has it own background 
		if (m_help) showHelp(); 
		if (!m_help && m_gameRun && !m_gameOver) m_gameOver = m_game.updateGame(m_window, clock, delta);
		if (m_gameOver)
		{
			m_game.gameOver(m_window);
		}
		
		if (auto event = sf::Event{}; m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break; 

			case sf::Event::MouseButtonReleased:
				handleButtonPress(event.mouseButton);
				break;
			
			case sf::Event::KeyPressed:
				handleKeyPress(event.key);
				break;
			
			default:
				break;
			}
		}
		delta = clock.restart();
		m_window.display();
	}
}

/*================== showMenu =================*/
void Menu::showMenu()
{
	bool scaled = false;
	sf::Mouse mouse;
	
	auto pos = m_window.mapPixelToCoords(mouse.getPosition(m_window)); //mouse position
	
	// Menu's background
	if (!m_gameRun)
	{
		auto menu = sf::Sprite(ResourcesManager::instance().getTexture(MENU));
		m_window.draw(menu);
	}

	// show all buttons. scale the button that if the mouse is "on it" 
	for (auto& button : m_buttons)
	{
		if (button.getGlobalBounds().contains(pos))
		{
			button.scale(1.07f, 1.07f);
			scaled = true;
		}

		m_window.draw(button);

		// the sizes of the buttons is differrent if the game is running / doesnt
		if (scaled && !m_gameRun) button.setScale(1, 1); 
		if (scaled && m_gameRun) button.setScale(0.333f, 0.333f);
	}
}

/*================== showMenu =================*/
void Menu::showHelp()
{
	auto help = sf::Sprite();

	if (m_help1Page)
	{
		help.setTexture(ResourcesManager::instance().getTexture(HELP1));
	}

	else
	{
		help.setTexture(ResourcesManager::instance().getTexture(HELP2));
	}

	m_window.draw(help);
}

/*================== handleButtonPress =================*/
void Menu::handleButtonPress(sf::Event::MouseButtonEvent& click)
{
	if (m_gameOver) return;

	auto pos = sf::Vector2f({ (float)click.x, (float)click.y });
	
	// NEW GAME button - pressed
	// minimize the buttons and set the positions of all of them 
	if (m_buttons[0].getGlobalBounds().contains(pos))
	{
		m_game.playSound(BUTTON_S);
		m_gameRun = true;
		
		// newGame button 
		m_buttons[0].setPosition(0, 0);
		m_buttons[0].setScale(0.333f, 0.333f);
		
		// help button
		m_buttons[1].setPosition(90, 0);
		m_buttons[1].setScale(0.333f, 0.333f);
		
		// exit button
		m_buttons[2].setPosition(1200, 0);
		m_buttons[2].setScale(0.333f, 0.333f);
		
		m_game.newGame();
	}

	// HELP button - pressed
	if (m_buttons[1].getGlobalBounds().contains(pos))
	{
		m_game.playSound(BUTTON_S);
		m_help = true;
		m_help1Page = true;
	}

	// EXIT button - pressed
	if (m_buttons[2].getGlobalBounds().contains(pos))
	{
		m_window.close();
	}
}

/*================== handleButtonPress =================*/
/**----------------------------------------------
 * this function is being used only if - the game is over / one of the help page's is open
 *---------------------------------------------**/
void Menu::handleKeyPress(sf::Event::KeyEvent& press)
{
	// --------- help button pressed ------
	if (press.code == sf::Keyboard::Escape && m_help) // exit "help" pages (program still running)
	{
		m_game.playSound(BUTTON_S);
		m_help = false;
		m_help1Page = false;
	}

	else if (press.code == sf::Keyboard::Right && m_help1Page) // move to help page 2
	{
		m_game.playSound(BUTTON_S);
		m_help1Page = false;
	}

	else if (press.code == sf::Keyboard::Left && !m_help1Page && m_help) // return to help page 1
	{
		m_game.playSound(BUTTON_S);
		m_help1Page = true;
	}

	// -------- game over -------
	if (press.code == sf::Keyboard::Escape && m_gameOver) // user wants to exit the game
	{
		m_window.close();
	}

	else if (press.code == sf::Keyboard::Space && m_gameOver) // the user wants new game
	{
		m_game.playSound(BUTTON_S);
		m_gameRun = true;
		m_gameOver = false;
		m_game.newGame();
	}
}