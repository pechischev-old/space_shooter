#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player, TextureGame & textureGame) {
	player.ship = new Entity(250, 250, NAME_PLAYER_SHIP, textureGame.playerTexture);
	player.ship->health = float(player.maxHealth);
	player.playerState.isAlive = true;
	player.ship->damage = float(player.maxDamage);
	player.ship->speed = SPEED_HERO;
}

void Player::CheckPlayerLife() {
	playerState.isAlive = ship->health > 0;
}

void Player::AddBullet(TextureGame & textureGame) {
	if (playerState.isShoot) {
		timeCreateBullet += clock.restart(); 
		if (timeCreateBullet.asSeconds() > TIME_CREATE_BULLET) { // Зависимость появления пули от времени
			directionShoot = RIGHT;
			Shoot addBullet(ship->sprite->getPosition().x, ship->sprite->getPosition().y, ship->width, ship->height, directionShoot, textureGame.blueLaserTexture);
			addBullet.damage = int(ship->damage);
			addBullet.sprite->setScale(float(scaleBullet), float(scaleBullet));
			bullet.push_back(addBullet); // создание пули и занесение ее в список
			timeCreateBullet = Time::Zero;
		}
		//------------------------------
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