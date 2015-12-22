#pragma once
#include <SFML/Graphics.hpp>

#include "Math.h"
#include <string>

struct GlobalBool {
	bool g_isMenu = true;
};

const static int SCRN_HEIGTH = 768, SCRN_WIDTH = 1390;

const static double BORDER = 0.3f;

const static sf::String TITLE_GAME = "Main Game";

const static int POINT_FOR_ADVANCE = 15;

const static int MAX_LEVEL_GAME = 15;

//---------------------- Для игрока ------------------------------------

const static int SPEED_HERO = 500;

const static int SPEED_BULLET = 400; // скорость пули

const static int PLAYER_DAMAGE = 25;

const static double TIME_CREATE_BULLET = 0.1;

const static int MAX_HEALTH = 1000;

const static int MAX_DAMAGE = 50;

const static sf::String NAME_PLAYER_SHIP = "sokol";

const static float MAX_TIME_RECOVERY_MOVE = 3;

//--------------

static const int SPEED_OTHER_BULLET = 20;

static const int SPEED_ROCKET = 8;

static const int BORDER_CREATE = 80;

//---------------------- Для врагов -----------------------------------

const static int HEIGTH_ENEMY = 50,
			WIDTH_ENEMY = 70;

const static int FIRST_EVER_DAMAGE_ENEMY = 15;

const static int FIRST_EVER_HEALTH_ENEMY = 100;

const static int POINT_FOR_RAGE = 30;

const static int SPEED_ENEMY = 300;

const static double SPEED_HARD_ENEMY = 7.0;

const static float SPEED_BOSS = 150;

const static int SPEED_KAMIKAZE = 7;

const static int TIME_CREATE_ENEMY = 2;
const static float TIME_CREATE_ROCKET = 0.45f;

const static float TIME_CREATE_BULLET_ENEMY = 0.2f;

const static float DISTANCE_FOR_ATACK = 500.f;

static const int COUNT_EASY_ENEMY = 3;
static const int COUNT_MIDDLE_ENEMY = 0;
static const int COUNT_TOWER_ENEMY = 0;
static const int COUNT_KAMIKAZE_ENEMY = 0;

const static sf::String NAME_EASY_ENEMY = "easyEnemy";

const static sf::String NAME_MIDDLE_ENEMY = "middleEnemy";

const static sf::String NAME_BOSS = "boss";

const static sf::String NAME_TOWER_ENEMY = "tower";

const static int SPEED_TOWER = 70;

const static sf::String NAME_KAMIKAZE_ENEMY = "kamikaze";

const static int RATE_HEALTH_BOSS = 50;

		// увеличение характеристик
		const static int INCREASED_DAMAGE_ENEMY = 5;
		const static int INCREASED_HEALTH_ENEMY = 30;
		const static int INCREASED_COUNT_ENEMY = 10;

const static float DIFFERENT_TIME_CREATE_ENEMY = 0.1f;
//-----------------------------Для астероидов  ---------------------------------

const static float TIME_CREATE_ASTEROID = 1.1f;

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

static const float DIFFERENT_TIME_CREATE_ASTEROID = 0.07f;

//--------------------- Для взрыва -----------------------------

const static int HEIGTH_EXPLOSION = 60, WIDTH_EXPLOSION = 64;

const static int NUMBER_OF_FRAMES = 16;
const static int SPEED_FRAMES = 12;

const static int NUMBER_OF_FRAMES_BULLET = 10;
const static int SPEED_FRAMES_BULLET = 10;

//--------------------- Для бонусов ----------------------------

const static sf::String BOMB_IMAGE = "bomb";

const static sf::String DECREASE_IMAGE = "decrease";

const static sf::String INCREASE_DAMAGE_IMAGE = "increaseDamage";

const static sf::String INVULNERABILITY_IMAGE = "invulnerability";

const static sf::String REPAIR_IMAGE = "repair";

const static int SPEED_BONUS = 50;

const static int TIME_CREATE_BONUS = 2;

const static int SPEED_FRAME_ANIMATION = 7;

	// время использования
	const static int TIME_USE_INVULNERABILITY_IN_SECONDS = 25;
	const static int TIME_USE_INCREASE_IN_SECONDS = 20;
	const static int TIME_USE_DECREASE_IN_SECONDS = 20;
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

const static int COUNT_STRING_IN_MENU = 5;

const static float RATE_LINE_SPACING = 1.f;

const static sf::String TEXT_HEALTH = L"Жизнь: ";

const static sf::String TEXT_POINT = L"Врагов осталось: ";

const static sf::String TEXT_LEVEL = L"Уровень ";

const static sf::String TEXT_NEW_GAME = L"Новая игра";
const static sf::String TEXT_CONTINUE = L"Продолжить";
const static sf::String TEXT_INSTRUCTION = L"Как играть";
const static sf::String TEXT_OPTIONS = L"Настройки";
const static sf::String TEXT_EXIT = L"Выход";
const static sf::String TEXT_ABOUT_LOSING = L"Вы проиграли. Нажмите Esc для выхода в меню";
const static sf::String TEXT_SCORE = L"Ваш счет: ";


const static sf::String PATH_TO_FONT = "resourse/fonts/Ubuntu-R.ttf";

const static sf::String PATH_TO_RED_BULLET = "resourse/images/laser-red.png";
const static sf::String PATH_TO_BLUE_BULLET = "resourse/images/laser-blue.png";
const static sf::String PATH_TO_GREEN_BULLET = "resourse/images/laser-green.png";

const static sf::String PATH_TO_EXPLOSION = "resourse/images/explosion_2.png";

const static sf::String PATH_TO_EXPLOSION_BULLET = "resourse/images/explosion.png";

const static sf::String NAME_STAR = "star";

const static sf::String NAME_BULLET = "laser";

const static sf::String NAME_ROCKET= "rocket";

const static sf::String NAME_ELECTRIC_BULLET = "electric_bulet";

const static sf::String PATH_BOMB = "resourse/images/bomb.png";
const static sf::String PATH_DECREASE = "resourse/images/decrease.png";
const static sf::String PATH_INCREASE_DAMAGE = "resourse/images/increaseDamage.png";
const static sf::String PATH_INVULNERABILITY = "resourse/images/invulnerability.png";
const static sf::String PATH_REPAIR = "resourse/images/repair.png";

const static sf::String PATH_SMALL_ASTEROID = "resourse/images/asteroid-small.png";
const static sf::String PATH_MEDIUM_ASTEROID = "resourse/images/asteroid-medium.png";
const static sf::String PATH_ASTEROID = "resourse/images/asteroid.png";

const static sf::String PATH_KAMIKAZE_ENEMY = "resourse/images/kamikaze.png";
const static sf::String PATH_TOWER_ENEMY = "resourse/images/tower.png";
const static sf::String PATH_MIDDLE_ENEMY = "resourse/images/middleEnemy.png";
const static sf::String PATH_EASY_ENEMY = "resourse/images/enemy1.png";
const static sf::String PATH_BOSS = "resourse/images/boss2.png";

const static sf::String PATH_PLAYER_SHIP = "resourse/images/sokol.png";

const static sf::String PATH_STAR = "resourse/images/star.png";

const static sf::String PATH_ELECTRIC_BULLET = "resourse/images/electricBullet.png";

const static sf::String PATH_ROCKET = "resourse/images/rocket.png";

const static sf::String PATH_HEALTH_BAR = "resourse/GUI/RedBar.png";

const static sf::String PATH_EMPTY_BAR = "resourse/GUI/EmptyBar.png";

const static sf::String PATH_RAGE_BAR = "resourse/GUI/YellowBar.png";

const static sf::String PATH_FIELD = "resourse/images/map.png";

const static sf::String PATH_INSTRUCTION = "resourse/images/instruction.png";

//--------------------------------------------------------------

static float SIZE_VOLUME_SHOOT = 10.f;
static float SIZE_VOLUME_EXPLOSION = 15.f;
static float SIZE_VOLUME_TAKE_BONUS = 50.f;

const static sf::String PATH_SHOOT_SOUND = "resourse/Music/laser1.ogg";

const static sf::String PATH_EXPLOSION_SOUND = "resourse/Music/explosion5.ogg";

const static sf::String PATH_MOUSECLICK_SOUND = "resourse/Music/mouseclick.wav";

const static sf::String PATH_PICK_UP_BONUS_SOUND = "resourse/Music/pick_up_bonus.ogg";