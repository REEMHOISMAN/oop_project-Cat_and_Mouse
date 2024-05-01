#pragma once

const int TEXTURES = 19;
const int INFO_LOGOS = 2;
const int WIDTH = 1280;
const int HEIGHT = 736;
const int PIXELS = 32;
const int TEXTS = 4;
const int BUTTONS = 3;
const int TEXT_SIZE = 15;
const int GIFT = 4;
const int EXTRA_TIME = 30;
const int SOUNDS = 10;
const float FREEZE_TIME = 5;
const float RAND_GIFT_SEC = 15;
const float CAT_SPEED = 90.f;
const float MOUSE_SPEED = 105.F;

// sounds are arranged to be same as the index of the sound it represent
//  in m_sounds in "ResourcesManager class"
// for example: DOOR_S -> index 2 in the sounds arrey

enum Sounds
{
	LEVEL_PASS,
	LIFE_S,
	DOOR_S,
	FREEZE_S, 
	KEY_S,
	LOST_LIFE_S,
	EAT_CHEESE_S, 
	POP_CAT_S,
	TIMER_S,
	BUTTON_S
};

//same logic as sounds
enum Textures 
{
	MENU,
	NEW_GAME,
	HELP,
	HELP1,
	HELP2,
	GAME_OVER,
	EXIT,
	INFO, 
	TIMER, 
	LIVES, 
	BACKGROUND, 
	WALL, 
	MOUSE, 
	CHEESE, 
	KEY, 
	DOOR, 
	CAT, 
    POP,
	FREEZE
};

//scores (points)
enum Scores
{
	EAT_CHEESE = 10,
	OPEN_DOOR = 2,
	TAKE_GIFT = 5,
	END_LEVEL = 25 // ** different calculation -> 25 + (5 * catsAmount) 
};

enum Gifts {POP_CAT_GIFT, LIFE_GIFT, FREEZE_GIFT ,TIME_GIFT};

enum Directions {NONE, LEFT, RIGHT, UP, DOWN};