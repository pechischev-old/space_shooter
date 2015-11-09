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
		//--------------------------- ¬ыстрел --------------------------
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
		//--------------------------------------------------------------
		// ќкно закрыли
		if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			window.close();
	}
}


void update(Game & game, const Time & deltaTime)
{
	Player & player = *game.player;
	RenderWindow & window = *game.window;
	PlayerState & playerState = player.playerState;

	Vector2i pixelPos = Mouse::getPosition(window);
	
	Vector2f posMouse = window.mapPixelToCoords(pixelPos);
	//cout << posMouse.x << "  " << posMouse.y << endl;
	//game.AddEnemy();
	game.CheckForCollision();

	game.enemy->AddEnemy();
	player.CheckPlayerLife();

	game.enemy->GetMoveEveryEnemy(deltaTime);
	MovePlayer(player, deltaTime); // задает координаты движени€ и отвечает за поворот персонажа

	Vector2f posPlayer = player.ship->sprite->getPosition();
	float rotation = player.ship->sprite->getRotation();
	player.ship->sprite->move(Border(player.ship->x, player.ship->y, posPlayer, rotation));

	for (list<Shoot>::iterator it = player.bullet->begin(); it != player.bullet->end();) {
		//cout << player.bullet->size() << endl;
		it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
			it = player.bullet->erase(it);
		}
		else  it++;
	}
	for (list<Shoot>::iterator it = game.enemy->bulletEnemy->begin(); it != game.enemy->bulletEnemy->end();) {
		//cout << game.bulletEnemy->size() << endl;
		it->MoveBullet(deltaTime);

		if (!it->life) {
			it->texture->~Texture();
			it = game.enemy->bulletEnemy->erase(it);
		}
		else  it++;
	}
}

void render(RenderWindow & window, Game & game)
{
	list<Shoot>::iterator it;
	list<Entity>::iterator it3;
	Player & player = *game.player;

	window.clear();
	for (it3 = game.enemy->enemyShip->begin(); it3 != game.enemy->enemyShip->end(); it3++)
		window.draw(*it3->sprite);
	for (it = player.bullet->begin(); it != player.bullet->end(); it++)
		window.draw(*it->sprite);
	if (player.playerState.isAlive) {
		window.draw(*player.ship->sprite);
	}
	//window.draw(*player.shape);
	for (it = game.enemy->bulletEnemy->begin(); it != game.enemy->bulletEnemy->end(); it++)
		window.draw(*it->sprite);
	
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
	DestroyGame(*game);
}

int main()
{
	startGame();
	return 0;
}

