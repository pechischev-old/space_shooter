#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <math.h>

#include "Game.h"

using namespace sf;
using namespace std;

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

void processEvents(RenderWindow & window, Game & game)
{
	Player & player = *game.player;
	Event event;
	while (window.pollEvent(event))
	{
		Control(player);
		//--------------------------- Выстрел --------------------------
		if (player.ship->health > 0) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				player.playerState.isShoot = true;
				player.AddBullet(window);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				player.playerState.isShoot = true;
				player.AddBullet(window);
			}
		}
		//--------------------------------------------------------------
		// Окно закрыли
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
	PlayerState & playerState = player.playerState;

	//--------------- Функции игры ---------------------
	
	game.IncreaseCharacteristicsObjects();
	game.CheckForCollision();
	game.UseBonus(deltaTime);
	//---------------- Интерфейс -----------------------
	UpdateText(*game.textInfo, player);
	//---------------- Функции игрока ------------------
	if (player.ship->health <= 0) {
		player.ship->direction = NONE;
		player.ship->Explosion(deltaTime);
	}
	else {
		MovePlayer(player, deltaTime); // задает координаты движения
		player.ship->sprite->move(Border(player, window));
		player.UpdateStatePlayerBullet(deltaTime, window);
	}
	//---------------- Функции противников -------------
	enemy.SetMoveEveryEnemy(deltaTime, player.point, window, bonus);
	enemy.AddEnemy();
	enemy.UpdateStateEnemyBullet(deltaTime, window);
	//--------------- Функции астероидов ---------------
	asteroid.AddAsteroid();
	asteroid.GetMoveEveryAsteroid(deltaTime, window, bonus);
	//---------------- Функции бонусов -----------------
	bonus.GetMoveEveryBonus(deltaTime, window);
}

void render(RenderWindow & window, Game & game)
{
	window.clear(); 
	game.DrawObjects();
	DrawTextToWindow(*game.textInfo, *game.window);
	window.display();
}

void CallGame()
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
}

int main()
{
	CallGame();
	return 0;
}

