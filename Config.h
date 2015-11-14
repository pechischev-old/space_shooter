#pragma once

const int SCRN_HEIGTH = 600, SCRN_WIDTH = 800;

const float BORDER = 0.3f;
//---------------------- ��� ������ ------------------------------------
const float SPEED_HERO = 200.f, SPEED_HERO_BACK = 150.f;

const float a = 1; // ������ ������� �����������

const float ANGLE = 1.5f; // ���� �� ������� ����� �������������� ������

const float SPEED_BULLET = 350.f; // �������� ����

const float WIDTH_BULLET = 12, HEIGTH_BULLET = 4;  // ������� ����

const float PLAYER_DAMAGE = 25;

//---------------------- ��� ������ -----------------------------------

const int HEIGTH_ENEMY = 50,
			WIDTH_ENEMY = 70;

const float SPEED_ENEMY = 150;

const float ENEMY_DAMAGE = 15;

//-----------------------------  ---------------------------------

const int HEIGTH_EXPLOSION = 60, WIDTH_EXPLOSION = 64;

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