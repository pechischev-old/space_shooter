#pragma once
#include <string>

const int SCRN_HEIGTH = 600, SCRN_WIDTH = 800;

const float BORDER = 0.3f;

const int NUMBER_OF_FRAMES = 10;

const sf::String TITLE_GAME = "Main Game";
//---------------------- Для игрока ------------------------------------
const float SPEED_HERO = 200.f;

const float SPEED_BULLET = 350.f; // скорость пули

const float WIDTH_BULLET = 12, HEIGTH_BULLET = 4;  // размеры пули

const float PLAYER_DAMAGE = 25;

const float TIME_CREATE_BULLET = 0.1;

const sf::String NAME_PLAYER_SHIP = "sokol";

const sf::String PATH_TO_BLUE_BULLET = "resourse/images/laser-blue.png";

//---------------------- Для врагов -----------------------------------

const int HEIGTH_ENEMY = 50,
			WIDTH_ENEMY = 70;

const float SPEED_ENEMY = 150;

const float ENEMY_DAMAGE = 15;

const int TIME_CREATE_ENEMY = 2;

const sf::String NAME_EASY_ENEMY = "enemy1";

const sf::String PATH_TO_RED_BULLET = "resourse/images/laser-red.png";
//-----------------------------  ---------------------------------

const float TIME_CREATE_ASTEROID = 1.1;

const sf::String NAME_ASTEROID = "asteroid";

const sf::String NAME_MEDIUM_ASTEROID = "asteroid-medium";

const sf::String NAME_SMALL_ASTEROID = "asteroid-small";

const int HEIGTH_EXPLOSION = 60, WIDTH_EXPLOSION = 64;

const sf::String PATH_TO_EXPLOSION = "resourse/images/explosion.png";

typedef enum
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
} Direction;

//------------------- Имена файлов и текст ----------------------

const sf::String TEXT_HEALTH = L"Жизнь: ";

const sf::String TEXT_POINT = L"Очки: ";

const sf::String PATH_TO_FONT = "resourse/fonts/Ubuntu-R.ttf";

