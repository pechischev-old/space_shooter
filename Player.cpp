#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player) {
	player.bullet = new list<Shoot>;
	player.ship = new Entity(250, 250, NAME_PLAYER_SHIP);
	player.ship->health = player.maxHealth;
	player.playerState.isAlive = true;
	player.ship->damage = player.maxDamage;
	player.ship->speed = SPEED_HERO;
}

void Player::CheckPlayerLife() {
	playerState.isAlive = ship->health > 0;
}

void Player::AddBullet(RenderWindow & window) {
	if (playerState.isShoot) {
		posMouse = Mouse::getPosition(window);
		timeCreateBullet += clock.restart(); 
		if (timeCreateBullet.asSeconds() > TIME_CREATE_BULLET) { // Зависимость появления пули от времени
			directionShoot = RIGHT;
			Shoot addBullet(ship->sprite->getPosition().x, ship->sprite->getPosition().y, ship->width, ship->height, directionShoot, PATH_TO_BLUE_BULLET);
			addBullet.damage = ship->damage;
			bullet->push_back(addBullet); // создание пули и занесение ее в список
			timeCreateBullet = Time::Zero;
		}
		playerState.isShoot = false;
	}
}

void Control(Player & player) {
	if (player.ship->health > 0) {
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = UP_LEFT;
			player.playerState.isMove = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = UP_RIGHT;
			player.playerState.isMove = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = DOWN_LEFT;
			player.playerState.isMove = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = DOWN_RIGHT;
			player.playerState.isMove = true;
			//----------------------------- По вертикали или горизантали ----------------------------
		}
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.direction = UP;
			player.playerState.isMove = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.direction = DOWN;
			player.playerState.isMove = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = RIGHT;
			player.playerState.isMove = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = LEFT;
			player.playerState.isMove = true;
		}
		else {
			player.direction = NONE;
			player.playerState.isMove = false;
		}
	}
}

void MovePlayer(Player & player, const Time & deltaTime) {
	
	Vector2f movement(0.f, 0.f);
	switch (player.direction) {
	case UP: movement.y -= SPEED_HERO;
		break;
	case DOWN: movement.y += SPEED_HERO;
		break;
	case LEFT: movement.x -= SPEED_HERO;
		break;
	case RIGHT: movement.x += SPEED_HERO;
		break;
	case UP_LEFT: movement.x -= SPEED_HERO;
		movement.y -= SPEED_HERO;
		break;
	case UP_RIGHT: movement.x += SPEED_HERO;
		movement.y -= SPEED_HERO;
		break;
	case DOWN_RIGHT: movement.x += SPEED_HERO;
		movement.y += SPEED_HERO;
		break;
	case DOWN_LEFT: movement.x -= SPEED_HERO;
		movement.y += SPEED_HERO;
		break;
	default:
		movement.x = 0;
		movement.y = 0;
		break;
	}
	player.ship->x = movement.x * deltaTime.asSeconds();
	player.ship->y = movement.y * deltaTime.asSeconds();

}

void Player::UpdateStatePlayerBullet(const Time & deltaTime, RenderWindow & window) {
	for (list<Shoot>::iterator it = bullet->begin(); it != bullet->end();) {
		//cout << player.bullet->size() << endl;
		it->CheckForCollisions(window);
		it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
			it = bullet->erase(it);
		}
		else  ++it;
	}
}

Vector2f Border(Player & player, RenderWindow & window) {
	Vector2f limit(0.f, 0.f);
	float heigth = player.ship->height,
		width = player.ship->width,
		X = player.ship->x,
		Y = player.ship->y;
	Vector2f posPlayer = player.ship->sprite->getPosition();
	
	if (window.getSize().x <= posPlayer.x + width / 2) {
		X = -BORDER;
	}
	if (0 >= posPlayer.x - width / 2) {
		X = BORDER;
	}
	if (window.getSize().y <= posPlayer.y + heigth / 2) {
		Y = -BORDER;
	}
	if (0 >= posPlayer.y - heigth / 2) {
		Y = BORDER;
	}
	limit.x = X;
	limit.y = Y;
	return limit;
}