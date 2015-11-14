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
				//player.posMouse = Mouse::getPosition(window);
				//cout << player.posMouse.x << "  " << player.posMouse.y << endl;
				player.playerState.isShoot = true;
				player.AddBullet(window);
			}
			//if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
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
	RenderWindow & window = *game.window;
	PlayerState & playerState = player.playerState;

	game.CheckForCollision();

	UpdateText(*game.textInfo, player);
	
	//---------------- Функции игрока ------------------
	if (player.ship->health <= 0)
		player.ship->Explosion(deltaTime);
	MovePlayer(player, deltaTime); // задает координаты движения и отвечает за поворот персонажа
	player.ship->sprite->move(Border(player)); 
	player.UpdateStatePlayerBullet(deltaTime);

	//---------------- Функции противников -------------
	enemy.GetMoveEveryEnemy(deltaTime, player.point);
	enemy.AddEnemy();
	enemy.UpdateStateEnemyBullet(deltaTime);

	//---------------
	asteroid.AddAsteroid();
	asteroid.GetMoveEveryAsteroid(deltaTime);
}

void render(RenderWindow & window, Game & game)
{
	window.clear(); 
	game.DrawObjects();
	DrawTextToWindow(*game.textInfo, *game.window);
	window.display();
}

void startGame()
{
	Game *game = new Game();
	InitializeGame(*game);

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	Player & player = *game->player;
	RenderWindow & window = *game->window;
	
	//view.reset(sf::FloatRect(0, 0, SCRN_HEIGTH, SCRN_WIDTH));
	
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
		//ChangeView();
		render(window, *game);
	}
	delete game;
}

int main()
{
	startGame();
	return 0;
}

