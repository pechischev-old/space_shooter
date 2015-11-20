#pragma once
#include <string>

const int SCRN_HEIGTH = 600, SCRN_WIDTH = 800;

const float BORDER = 0.3f;

const int NUMBER_OF_FRAMES = 10;

const sf::String TITLE_GAME = "Main Game";

//---------------------- Для игрока ------------------------------------

const float SPEED_HERO = 280.f;

const float SPEED_BULLET = 350.f; // скорость пули

const float WIDTH_BULLET = 12, HEIGTH_BULLET = 4;  // размеры пули

const float PLAYER_DAMAGE = 25;

const float TIME_CREATE_BULLET = 0.1;

const int MAX_HEALTH = 400000;

const int MAX_DAMAGE = 50;

const sf::String NAME_PLAYER_SHIP = "sokol";

//---------------------- Для врагов -----------------------------------

const int HEIGTH_ENEMY = 50,
			WIDTH_ENEMY = 70;

const int FIRST_EVER_DAMAGE_ENEMY = 15;

const int FIRST_EVER_HEALTH_ENEMY = 100;

const float SPEED_ENEMY = 150;

const int TIME_CREATE_ENEMY = 2;

const sf::String NAME_EASY_ENEMY = "enemy1";
//-----------------------------Для астероидов  ---------------------------------

const float TIME_CREATE_ASTEROID = 1.1;

const sf::String NAME_ASTEROID = "asteroid";

const int SPEED_ASTEROID = 200;
const int HEALTH_ASTEROID = 250;
const int DAMAGE_ASTEROID = 40;

const sf::String NAME_MEDIUM_ASTEROID = "asteroid-medium";

const int SPEED_MEIUM_ASTEROID = 230;
const int HEALTH_MEDIUM_ASTEROID = 150;
const int DAMAGE_MEDIUM_ASTEROID = 25;

const sf::String NAME_SMALL_ASTEROID = "asteroid-small";

const int SPEED_SMALL_ASTEROID = 250;
const int HEALTH_SMALL_ASTEROID = 50;
const int DAMAGE_SMALL_ASTEROID = 10;

//--------------------- Для взрыва -----------------------------

const int HEIGTH_EXPLOSION = 60, WIDTH_EXPLOSION = 64;

//--------------------- Для бонусов ----------------------------

const sf::String BOMB_IMAGE = "bomb";

const sf::String DECREASE_IMAGE = "decrease";

const sf::String INCREASE_DAMAGE_IMAGE = "increaseDamage";

const sf::String INVULNERABILITY_IMAGE = "invulnerability";

const sf::String REPAIR_IMAGE = "repair";

const float SPEED_BONUS = 50.f;

const float TIME_CREATE_BONUS = 2;

//--------------------------------------------------------------

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

//------------------- Текст и пути файлов ----------------------

const sf::String TEXT_HEALTH = L"Жизнь: ";

const sf::String TEXT_POINT = L"Очки: ";

const sf::String PATH_TO_FONT = "resourse/fonts/Ubuntu-R.ttf";

const sf::String PATH_TO_RED_BULLET = "resourse/images/laser-red.png";

const sf::String PATH_TO_BLUE_BULLET = "resourse/images/laser-blue.png";

const sf::String PATH_TO_EXPLOSION = "resourse/images/explosion.png";

const sf::String PATH_TO_BONUSES = "resourse/images/bonuses";

const sf::String NAME_STAR = "star";

//--------------------------------------------------------------

