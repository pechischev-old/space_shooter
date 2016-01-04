#pragma once
#include <SFML/Graphics.hpp>
//#include <vld.h>
#include "Math.h"
#include <string>

struct GlobalBool {
	bool g_isMenu = true;
};

static const  int SCRN_HEIGTH = 768, SCRN_WIDTH = 1390;

static const  double BORDER = 0.3f;

static const  sf::String TITLE_GAME = "Main Game";

static const  int POINT_FOR_ADVANCE = 15;

static const  int MAX_LEVEL_GAME = 15;

//---------------------- Для игрока ------------------------------------

static const  int SPEED_HERO = 500;

static const  int SPEED_BULLET = 400; // скорость пули

static const  int PLAYER_DAMAGE = 25;

static const  double TIME_CREATE_BULLET = 0.1;

static const  int MAX_HEALTH = 1000;

static const  int MAX_DAMAGE = 50;

static const  sf::String NAME_PLAYER_SHIP = "sokol";

static const  float MAX_TIME_RECOVERY_MOVE = 3;
//--------------

static const int SPEED_OTHER_BULLET = 20;

static const int SPEED_ROCKET = 8;

static const int BORDER_CREATE = 80;

//---------------------- Для врагов -----------------------------------

static const  int FIRST_EVER_DAMAGE_ENEMY = 15;

static const  int FIRST_EVER_HEALTH_ENEMY = 100;

static const  int SPEED_ENEMY = 300;

static const  double SPEED_HARD_ENEMY = 7.0;


static const  int SPEED_KAMIKAZE = 7;

static const  int TIME_CREATE_ENEMY = 2;
static const  float TIME_CREATE_ROCKET = 0.45f;

static const  float TIME_CREATE_BULLET_ENEMY = 0.2f;

static const  float DISTANCE_FOR_ATACK = 500.f;

static const int COUNT_EASY_ENEMY = 2;
static const int COUNT_MIDDLE_ENEMY = 0;
static const int COUNT_TOWER_ENEMY = 0;
static const int COUNT_KAMIKAZE_ENEMY = 0;

static const  sf::String NAME_EASY_ENEMY = "easyEnemy";

static const  sf::String NAME_MIDDLE_ENEMY = "middleEnemy";

static const  sf::String NAME_TOWER_ENEMY = "tower";

static const  int SPEED_TOWER = 70;

static const  sf::String NAME_KAMIKAZE_ENEMY = "kamikaze";

static const  sf::String NAME_BOSS = "boss";
static const  int POINT_FOR_RAGE = 1500;
static const int POINT_FOR_CALM = 150;
static const  float SPEED_BOSS = 150;
static const int HEALTH_BOSS = 100000;

		// увеличение характеристик
		static const  int INCREASED_DAMAGE_ENEMY = 5;
		static const  int INCREASED_HEALTH_ENEMY = 30;
		static const  int INCREASED_COUNT_ENEMY = 10;

static const  float DIFFERENT_TIME_CREATE_ENEMY = 0.1f;
//-----------------------------Для астероидов  ---------------------------------

static const  float TIME_CREATE_ASTEROID = 1.1f;

static const  sf::String NAME_ASTEROID = "asteroid";

static const  int SPEED_ASTEROID = 200;
static const  int HEALTH_ASTEROID = 250;
static const  int DAMAGE_ASTEROID = 40;

static const  sf::String NAME_MEDIUM_ASTEROID = "asteroid-medium";

static const  int SPEED_MEIUM_ASTEROID = 230;
static const  int HEALTH_MEDIUM_ASTEROID = 150;
static const  int DAMAGE_MEDIUM_ASTEROID = 25;

static const  sf::String NAME_SMALL_ASTEROID = "asteroid-small";

static const  int SPEED_SMALL_ASTEROID = 250;
static const  int HEALTH_SMALL_ASTEROID = 50;
static const  int DAMAGE_SMALL_ASTEROID = 10;

static const float DIFFERENT_TIME_CREATE_ASTEROID = 0.07f;

//--------------------- Для взрыва -----------------------------

static const  int HEIGTH_EXPLOSION = 60, WIDTH_EXPLOSION = 64;

static const  int NUMBER_OF_FRAMES = 16;
static const  int SPEED_FRAMES = 12;

static const  int NUMBER_OF_FRAMES_BULLET = 10;
static const  int SPEED_FRAMES_BULLET = 10;

//--------------------- Для бонусов ----------------------------

static const  sf::String BOMB_IMAGE = "bomb";

static const  sf::String DECREASE_IMAGE = "decrease";

static const  sf::String INCREASE_DAMAGE_IMAGE = "increaseDamage";

static const  sf::String INVULNERABILITY_IMAGE = "invulnerability";

static const  sf::String REPAIR_IMAGE = "repair";

static const  sf::String TRIPLE_SHOT_IMAGE = "tripleShot";

static const  sf::String DOUBLE_SHOT_IMAGE = "doubleShot";

static const  int SPEED_BONUS = 50;

static const  int TIME_CREATE_BONUS = 2;

static const  int SPEED_FRAME_ANIMATION = 7;

	// время использования
	static const  int TIME_USE_INVULNERABILITY_IN_SECONDS = 25;
	static const  int TIME_USE_INCREASE_IN_SECONDS = 20;
	static const  int TIME_USE_DECREASE_IN_SECONDS = 20;
	static const  int TIME_USE_TRIPLE_SHOT_IN_SECONDS = 30;
	static const  int TIME_USE_DOUBLE_SHOT_IN_SECONDS = 30;
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

enum MenuSelector {
	NEW_GAME = 1,
	CONTINUE,
	RECORDS,
	OPTIONS,
	EXIT,
	BACK,
	NO_SELECT
};

//------------------- Текст и пути файлов ----------------------

static const  int COUNT_STRING_IN_MENU = 5;

static const  float RATE_LINE_SPACING = 1.f;

static const  sf::String TEXT_HEALTH = L"Жизнь: ";

static const  sf::String TEXT_POINT = L"Врагов осталось: ";

static const  sf::String TEXT_LEVEL = L"Уровень ";

static const  sf::String TEXT_NEW_GAME = L"Новая игра";
static const  sf::String TEXT_CONTINUE = L"Продолжить";
static const  sf::String TEXT_INSTRUCTION = L"Как играть";
static const  sf::String TEXT_OPTIONS = L"Настройки";
static const  sf::String TEXT_EXIT = L"Выход";
static const  sf::String TEXT_ABOUT_LOSING = L"Вы проиграли. Нажмите Esc для выхода в меню";
static const  sf::String TEXT_ABOUT_WIN = L"Вы выйграли! Нажмите Esc для выхода в меню";
static const  sf::String TEXT_SCORE = L"Ваш счет: ";

//---------------------
static const  sf::String PATH_TO_EXPLOSION = "resourse/images/explosion_2.png";
static const  sf::String PATH_TO_EXPLOSION_BULLET = "resourse/images/explosion.png";
//---------------------
static const  sf::String NAME_STAR = "star";
static const  sf::String NAME_BULLET = "laser";
static const  sf::String NAME_ROCKET= "rocket";
static const  sf::String NAME_ELECTRIC_BULLET = "electric_bulet";
//---------------------
static const  sf::String PATH_BOMB = "resourse/images/bomb.png";
static const  sf::String PATH_DECREASE = "resourse/images/decrease.png";
static const  sf::String PATH_INCREASE_DAMAGE = "resourse/images/increaseDamage.png";
static const  sf::String PATH_INVULNERABILITY = "resourse/images/invulnerability.png";
static const  sf::String PATH_REPAIR = "resourse/images/repair.png";
static const  sf::String PATH_TRIPLE_SHOT = "resourse/images/tripleShot.png";
static const  sf::String PATH_DOUBLE_SHOT = "resourse/images/straight_gun.png";
//---------------------
static const  sf::String PATH_SMALL_ASTEROID = "resourse/images/asteroid-small.png";
static const  sf::String PATH_MEDIUM_ASTEROID = "resourse/images/asteroid-medium.png";
static const  sf::String PATH_ASTEROID = "resourse/images/asteroid.png";
//---------------------
static const  sf::String PATH_KAMIKAZE_ENEMY = "resourse/images/kamikaze.png";
static const  sf::String PATH_TOWER_ENEMY = "resourse/images/tower.png";
static const  sf::String PATH_MIDDLE_ENEMY = "resourse/images/middleEnemy.png";
static const  sf::String PATH_EASY_ENEMY = "resourse/images/enemy1.png";
static const  sf::String PATH_BOSS = "resourse/images/boss2.png";
//---------------------
static const  sf::String PATH_PLAYER_SHIP = "resourse/images/player.png";
//---------------------
static const  sf::String PATH_STAR = "resourse/images/star.png";
//---------------------
static const  sf::String PATH_TO_FONT = "resourse/fonts/Ubuntu-R.ttf";
//---------------------
static const  sf::String PATH_TO_RED_BULLET = "resourse/images/laser-red.png";
static const  sf::String PATH_TO_BLUE_BULLET = "resourse/images/laser-blue.png";
static const  sf::String PATH_TO_GREEN_BULLET = "resourse/images/laser-green.png";
static const  sf::String PATH_ELECTRIC_BULLET = "resourse/images/electricBullet.png";
static const  sf::String PATH_ROCKET = "resourse/images/rocket.png";
//---------------------
static const  sf::String PATH_FIELD = "resourse/images/map.png";
//---------------------
static const  sf::String PATH_INSTRUCTION = "resourse/images/instruction.png";
//--------------------------------------------------------------
static float SIZE_VOLUME_SHOOT = 5.5f;
static float SIZE_VOLUME_EXPLOSION = 15.5f;
static float SIZE_VOLUME_TAKE_BONUS = 10.5f;
//---------------------

static const  sf::String PATH_SHOOT_SOUND = "resourse/Music/laser1.ogg";

static const  sf::String PATH_EXPLOSION_SOUND = "resourse/Music/explosion5.ogg";

static const  sf::String PATH_MOUSECLICK_SOUND = "resourse/Music/mouseclick.wav";

static const  sf::String PATH_PICK_UP_BONUS_SOUND = "resourse/Music/pick_up_bonus.ogg";