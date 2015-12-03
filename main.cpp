#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <math.h>

#include "Game.h"

using namespace sf;
using namespace std;

bool g_isRestart = true;

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

void processEvents(RenderWindow & window, Game & game)
{
	Player & player = *game.player;
	Event event;
	while (window.pollEvent(event))
	{
		Control(player);
		//----------------- Restart -----------------------------------
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::N) {
			g_isRestart = true;
			game.window->close();
		}
		else
			g_isRestart = false;
		//--------------------------- ������� --------------------------
		if (player.ship->health > 0) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				player.playerState.isShoot = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				player.playerState.isShoot = true;
			}
		}
		//--------------------------------------------------------------
		// ���� �������
		if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			window.close();
	}
}


void update(Game & game, const Time & deltaTime)
{
	Player & player = *game.player;
	Enemy & enemy = *game.enemy;
	Asteroid & asteroid = *game.asteroid;
	Bonus & bonus = *game.bonus;
	RenderWindow & window = *game.window;
	Star & star = *game.star;
	PlayerState & playerState = player.playerState;

	//--------------- ������� ���� ---------------------
	
	game.IncreaseCharacteristicsObjects();
	game.CheckForCollision();
	game.UseBonus(deltaTime);
	//---------------- ��������� -----------------------
	UpdateText(*game.textInfo, player);
	//---------------- ������� ����� -------------------
	//LoadStarInList(star, deltaTime, window, *game.textureGame); // �������� ����������� �����
	star.AddStar(game.textureGame);
	star.UpdateStateStar(deltaTime, window);
	//---------------- ������� ������ ------------------
	if (player.ship->health <= 0) {
		player.ship->direction = NONE;
		player.ship->Explosion(deltaTime, game.textureGame.explosionTexture);
	}
	else {
		MovePlayer(player, deltaTime); // ������ ���������� ��������
		player.ship->sprite->move(Border(*player.ship, window));
		player.AddBullet(game.textureGame);
		player.RecoveryMove();
		UpdateStateBullet(deltaTime, window, player.bullet);
	}
	//---------------- ������� ����������� -------------
	enemy.UpdateStateEveryEnemy(deltaTime, player.point, window, bonus, game.textureGame);
	enemy.AddEnemy(game.textureGame);
	enemy.CalmBoss();
	UpdateStateBullet(deltaTime, window, enemy.bulletEnemy);
	//--------------- ������� ���������� ---------------
	if (!enemy.isBoss)
		asteroid.AddAsteroid(game.textureGame);
	asteroid.GetMoveEveryAsteroid(deltaTime, window, bonus, game.textureGame);
	//---------------- ������� ������� -----------------
	bonus.GetMoveEveryBonus(deltaTime, window);
}

void render(RenderWindow & window, Game & game)
{
	window.clear(); 
	//if (!game.gameState.isLoading) {
		game.DrawObjects();
		DrawTextToWindow(*game.textInfo, *game.window);
	//}
	window.display();
}

int CallGame()
{
	Game *game = new Game();
	InitializeGame(*game);

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	Player & player = *game->player;
	RenderWindow & window = *game->window;
	game->window->setVerticalSyncEnabled(true);
	
	while (window.isOpen())
	{
		processEvents(window, *game);
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(window, *game);
			update(*game, TIME_PER_FRAME);
		}
		render(window, *game);
	}
	Delete(*game);
	delete game;
	return 0;
}



int main()
{
	while (g_isRestart) {
		CallGame();
	}

	return 0;
}

