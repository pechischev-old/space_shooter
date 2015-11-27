#pragma once
#include <string>

const int SCRN_HEIGTH = 600, SCRN_WIDTH = 800;

const float BORDER = 0.3f;

const int NUMBER_OF_FRAMES = 10;

const sf::String TITLE_GAME = "Main Game";

const int POINT_FOR_ADVANCE = 50;

//---------------------- Для игрока ------------------------------------

const int SPEED_HERO = 280;

const int SPEED_BULLET = 350; // скорость пули

const int WIDTH_BULLET = 12, HEIGTH_BULLET = 4;  // размеры пули

const int PLAYER_DAMAGE = 25;

const float TIME_CREATE_BULLET = 0.1;

const int MAX_HEALTH = 400000;

const int MAX_DAMAGE = 50;

const sf::String NAME_PLAYER_SHIP = "sokol";

//---------------------- Для врагов -----------------------------------

const int HEIGTH_ENEMY = 50,
			WIDTH_ENEMY = 70;

const int FIRST_EVER_DAMAGE_ENEMY = 15;

const int FIRST_EVER_HEALTH_ENEMY = 100;

const int SPEED_ENEMY = 150;

const float SPEED_HARD_ENEMY = 1.5;

const float SPEED_BOSS = 150;

const int TIME_CREATE_ENEMY = 2;

const float TIME_CREATE_BULLET_ENEMY = 0.2;

const sf::String NAME_EASY_ENEMY = "enemy1";

const sf::String NAME_MIDDLE_ENEMY = "middleEnemy";

const sf::String NAME_BOSS = "boss";
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

const int SPEED_BONUS = 50;

const int TIME_CREATE_BONUS = 2;
//--------------------------- Path------------------------------



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

const sf::String NAME_STAR = "star";

const sf::String PATH_BOMB = "resourse/images/bomb.png";
const sf::String PATH_DECREASE = "resourse/images/decrease.png";
const sf::String PATH_INCREASE_DAMAGE = "resourse/images/increaseDamage.png";
const sf::String PATH_INVULNERABILITY = "resourse/images/invulnerability.png";
const sf::String PATH_REPAIR = "resourse/images/repair.png";

const sf::String PATH_SMALL_ASTEROID = "resourse/images/asteroid-small.png";
const sf::String PATH_MEIUM_ASTEROID = "resourse/images/asteroid-medium.png";
const sf::String PATH_ASTEROID = "resourse/images/asteroid.png";

const sf::String PATH_MIDDLE_ENEMY = "resourse/images/middleEnemy.png";
const sf::String PATH_EASY_ENEMY = "resourse/images/enemy1.png";
const sf::String PATH_BOSS = "resourse/images/boss.png";

const sf::String PATH_PLAYER_SHIP = "resourse/images/sokol.png";

const sf::String PATH_STAR = "resourse/images/star.png";

//--------------------------------------------------------------

