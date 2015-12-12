#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player, TextureGame & textureGame) {
	player.ship = new Entity(SCRN_WIDTH / 2, SCRN_HEIGTH / 2, NAME_PLAYER_SHIP, textureGame.playerTexture);
	player.ship->health = float(player.maxHealth);
	player.playerState.isAlive = true;
	player.ship->damage = float(player.maxDamage);
	player.ship->speed = SPEED_HERO;
	player.playerState.isMove = true;
}

void Player::CheckPlayerLife() {
	playerState.isAlive = ship->health > 0;
}

void Player::AddBullet(TextureGame & textureGame, Vector2f posPoint) {
	if (playerState.isShoot) {
		timeCreateBullet += clock.restart(); 
		if (timeCreateBullet.asSeconds() > TIME_CREATE_BULLET) { // Зависимость появления пули от времени
			directionShoot = RIGHT;
			Shoot addBullet(ship->sprite->getPosition().x, ship->sprite->getPosition().y, ship->width, ship->height, directionShoot, textureGame.blueLaserTexture, NAME_BULLET);
			addBullet.damage = int(ship->damage);
			addBullet.sprite->setScale(float(scaleBullet), float(scaleBullet));
			addBullet.isOtherBullet = true;
			addBullet.rememPos = posPoint;
			bullet.push_back(addBullet); // создание пули и занесение ее в список
			timeCreateBullet = Time::Zero;
		}
		//------------------------------
		playerState.isShoot = false;
	}
}

void Player::RecoveryMove() {
	if (!playerState.isMove) {
		timeRecoveryMove += clock.restart();
		if (timeRecoveryMove.asSeconds() > MAX_TIME_RECOVERY_MOVE) {
			playerState.isMove = true;
			timeRecoveryMove = Time::Zero;
		}
	}
}

void Control(Player & player) {
	if (player.ship->health > 0 && player.playerState.isMove) {
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = UP_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = UP_RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = DOWN_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = DOWN_RIGHT;
			//----------------------------- По вертикали или горизантали ----------------------------
		}
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.direction = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.direction = DOWN;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = LEFT;
		}
		else {
			player.direction = NONE;
		}
	}
	else {
		player.direction = NONE;
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

void ResetPlayer(Player & player, TextureGame & textureGame) {
	player.maxHealth = MAX_HEALTH;
	player.maxDamage = MAX_DAMAGE;
	player.ship->sprite->setPosition(SCRN_WIDTH / 2, SCRN_HEIGTH / 2);
	player.ship->sprite->setTexture(textureGame.playerTexture);
	player.ship->health = float(player.maxHealth);
	player.playerState.isAlive = true;
	player.ship->damage = float(player.maxDamage);
	player.ship->isLife = true;
	player.playerState.isMove = true;
	player.ship->isKilled = false;
}