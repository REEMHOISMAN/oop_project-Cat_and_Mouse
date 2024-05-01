#include "GameInfo.h"
#include "ResourcesManager.h"
#include <string>

/*================== showInfoText =================*/
void GameInfo::showInfoText(sf::RenderWindow& window,const sf::Vector2f& pos, int info)
{
	sf::Text text;
	auto string = std::to_string(info);
	text.setFillColor(sf::Color::Black);
	text.setFont(ResourcesManager::instance().getFont());
	text.setString(string);
	text.setPosition(pos);
	window.draw(text);
}

/*================== showInfoSprite =================*/
void GameInfo::showInfoSprite(sf::RenderWindow& window, const Textures type, const sf::Vector2f& pos)
{
	auto sprite = sf::Sprite(ResourcesManager::instance().getTexture(type));
	sprite.setPosition(pos);
	window.draw(sprite);
}

/*================== showTimer =================*/
void GameInfo::showTimer(sf::RenderWindow& window, int levelTime)
{
	std::string string;
	sf::Text text;
	text.setFillColor(sf::Color::Black);
	text.setFont(ResourcesManager::instance().getFont());
	auto minutes = levelTime;
	auto seconds = minutes % 60;
	minutes /= 60;
	string = "0";
	string += std::to_string(minutes);
	string += ":";
	if (seconds < 10)
	{
		string += "0";
	}
	string += std::to_string(seconds);
	text.setString(string);
	if (seconds < 10 && minutes == 0)
	{
		text.setFillColor(sf::Color::Red);
	}
	text.setPosition(80, 650);
	window.draw(text);
}

/*================== showFinalResult =================*/
void GameInfo::showFinalResult(sf::RenderWindow& window, int levelReached, int score)
{
	auto text = sf::Text();
	auto string = std::string();

	text.setFont(ResourcesManager::instance().getFont());

	//prints the tite "Game over"
	string = "GAME OVER";
	text.setString(string);
	text.setCharacterSize(160);
	text.Bold;
	text.setLetterSpacing(1.4);
	text.setPosition(130, 110);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Color(225, 165, 0)); //orange outline
	text.setOutlineThickness(4);
	window.draw(text);
	text.setLetterSpacing(1);

	//prints the final score
	string = "FINAL SCORE: ";
	string += std::to_string(score);
	text.setString(string);
	text.setCharacterSize(60);
	text.setPosition(330, 290);
	text.setOutlineThickness(0);
	window.draw(text);

	//prints the level the user reached
	string = "LEVEL REACHED: ";
	string += std::to_string(levelReached);
	text.setString(string);
	text.setPosition(330, 340);
	window.draw(text);

	//prints options
	text.Regular;
	text.setCharacterSize(25);
	string = "press 'ESC' button to exit.\npress 'SPACE' button to start a new game.";
	text.setString(string);
	text.setPosition(80, 510);
	window.draw(text);
}