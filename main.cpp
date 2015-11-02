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
		//--------------------------- ������� --------------------------
		/*if (Mouse::isButtonPressed(Mouse::Left)) {
			player.posMouse = Mouse::getPosition(window);
			player.playerState.isShoot = true;
			player.AddBullet();
		}*/
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
		//if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.playerState.isShoot = true;
			player.AddBullet();

		}
		//--------------------------------------------------------------
		// ���� �������
		if ((event.type == Event::Closed) || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			window.close();
	}
}

Vector2f Border(float X, float Y, Vector2f posPlayer, int rotation) {
	Vector2f limit(0.f, 0.f);
	float heigth = HEIGTH,
		width = WIDTH;
	if (SCRN_HEIGTH <= posPlayer.x + heigth / 2) {
		X = -BORDER;
	}
	if (0 >= posPlayer.x - heigth / 2) {
		X = BORDER;
	}
	if (SCRN_WIDTH <= posPlayer.y + width / 2) {
		Y = -BORDER;
	}
	if (0 >= posPlayer.y - width / 2) {
		Y = BORDER;
	}
	limit.x = X;
	limit.y = Y;
	return limit;
}

void update(Game & game, const Time & deltaTime)
{
	Player & player = *game.player;
	RenderWindow & window = *game.window;
	PlayerState & playerState = player.playerState;

	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f posMouse = window.mapPixelToCoords(pixelPos);

	game.AddEnemy();
	game.CheckForCollision();

	player.CheckPlayerLife();

	MovePlayer(player, deltaTime); // ������ ���������� �������� � �������� �� ������� ���������

	Vector2f posPlayer = player.sprite->getPosition();
	float rotation = player.sprite->getRotation();
	player.sprite->move(Border(player.x, player.y, posPlayer, rotation));

	for (list<Shoot>::iterator it = player.bullet->begin(); it != player.bullet->end();) {
		//cout << player.bullet->size() << endl;
		it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
			it = player.bullet->erase(it);
		}
		else  it++;
	}
	for (list<Enemy>::iterator it2 = game.enemy->begin(); it2 != game.enemy->end();) {
		//cout << game.enemy->size() << endl;
		it2->MoveEnemy(deltaTime);
		if (it2->life < 0)
			it2->GetExplosion(deltaTime);
		if (!it2->isLife) {
			it2->texture->~Texture();
			delete it2->sprite;
			it2 = game.enemy->erase(it2);
		}
		else  it2++;
	}
}

void render(RenderWindow & window, Game & game)
{
	list<Shoot>::iterator it;
	list<Enemy>::iterator it2;
	Player & player = *game.player;

	
	window.clear();
	
	for (it = player.bullet->begin(); it != player.bullet->end(); it++)
		window.draw(*it->sprite);
	if (player.playerState.isAlive)
		window.draw(*player.sprite);
	window.draw(*player.shape);
	for (it2 = game.enemy->begin(); it2 != game.enemy->end(); it2++)
		window.draw(*it2->sprite);
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
