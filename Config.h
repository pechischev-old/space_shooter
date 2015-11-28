#pragma once
#include <string>

const static int SCRN_HEIGTH = 600, SCRN_WIDTH = 800;

const static float BORDER = 0.3f;

const static int NUMBER_OF_FRAMES = 10;

const static sf::String TITLE_GAME = "Main Game";

const static int POINT_FOR_ADVANCE = 500;

//---------------------- Для игрока ------------------------------------

const static int SPEED_HERO = 280;

const static int SPEED_BULLET = 350; // скорость пули

const static int WIDTH_BULLET = 12, HEIGTH_BULLET = 4;  // размеры пули

const static int PLAYER_DAMAGE = 25;

const static float TIME_CREATE_BULLET = 0.1;

const static int MAX_HEALTH = 400000;

const static int MAX_DAMAGE = 50;

const static sf::String NAME_PLAYER_SHIP = "sokol";

//---------------------- Для врагов -----------------------------------

const static int HEIGTH_ENEMY = 50,
			WIDTH_ENEMY = 70;

const static int FIRST_EVER_DAMAGE_ENEMY = 15;

const static int FIRST_EVER_HEALTH_ENEMY = 100;

const static int SPEED_ENEMY = 150;

const static float SPEED_HARD_ENEMY = 1.5;

const static float SPEED_BOSS = 150;

const static int TIME_CREATE_ENEMY = 2;

const static float TIME_CREATE_BULLET_ENEMY = 0.2;

const static sf::String NAME_EASY_ENEMY = "enemy1";

const static sf::String NAME_MIDDLE_ENEMY = "middleEnemy";

const static sf::String NAME_BOSS = "boss";
//-----------------------------Для астероидов  ---------------------------------

const static float TIME_CREATE_ASTEROID = 1.1;

const static sf::String NAME_ASTEROID = "asteroid";

const static int SPEED_ASTEROID = 200;
const static int HEALTH_ASTEROID = 250;
const static int DAMAGE_ASTEROID = 40;

const static sf::String NAME_MEDIUM_ASTEROID = "asteroid-medium";

const static int SPEED_MEIUM_ASTEROID = 230;
const static int HEALTH_MEDIUM_ASTEROID = 150;
const static int DAMAGE_MEDIUM_ASTEROID = 25;

const static sf::String NAME_SMALL_ASTEROID = "asteroid-small";

const static int SPEED_SMALL_ASTEROID = 250;
const static int HEALTH_SMALL_ASTEROID = 50;
const static int DAMAGE_SMALL_ASTEROID = 10;

//--------------------- Для взрыва -----------------------------

const static int HEIGTH_EXPLOSION = 60, WIDTH_EXPLOSION = 64;

//--------------------- Для бонусов ----------------------------

const static sf::String BOMB_IMAGE = "bomb";

const static sf::String DECREASE_IMAGE = "decrease";

const static sf::String INCREASE_DAMAGE_IMAGE = "increaseDamage";

const static sf::String INVULNERABILITY_IMAGE = "invulnerability";

const static sf::String REPAIR_IMAGE = "repair";

const static int SPEED_BONUS = 50;

const static int TIME_CREATE_BONUS = 2;

//--------------------------------------------------------------

enum Direction
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
};

//------------------- Текст и пути файлов ----------------------

const static sf::String TEXT_HEALTH = L"Жизнь: ";

const static sf::String TEXT_POINT = L"Очки: ";

const static sf::String PATH_TO_FONT = "resourse/fonts/Ubuntu-R.ttf";

const static sf::String PATH_TO_RED_BULLET = "resourse/images/laser-red.png";

const static sf::String PATH_TO_BLUE_BULLET = "resourse/images/laser-blue.png";

const static sf::String PATH_TO_EXPLOSION = "resourse/images/explosion.png";

const static sf::String NAME_STAR = "star";

const static sf::String PATH_BOMB = "resourse/images/bomb.png";
const static sf::String PATH_DECREASE = "resourse/images/decrease.png";
const static sf::String PATH_INCREASE_DAMAGE = "resourse/images/increaseDamage.png";
const static sf::String PATH_INVULNERABILITY = "resourse/images/invulnerability.png";
const static sf::String PATH_REPAIR = "resourse/images/repair.png";

const static sf::String PATH_SMALL_ASTEROID = "resourse/images/asteroid-small.png";
const static sf::String PATH_MEIUM_ASTEROID = "resourse/images/asteroid-medium.png";
const static sf::String PATH_ASTEROID = "resourse/images/asteroid.png";

const static sf::String PATH_MIDDLE_ENEMY = "resourse/images/middleEnemy.png";
const static sf::String PATH_EASY_ENEMY = "resourse/images/enemy1.png";
const static sf::String PATH_BOSS = "resourse/images/boss.png";

const static sf::String PATH_PLAYER_SHIP = "resourse/images/sokol.png";

const static sf::String PATH_STAR = "resourse/images/star.png";

//--------------------------------------------------------------

