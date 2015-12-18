#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player, TextureGame & textureGame) {
	player.ship = new Entity(Vector2f(SCRN_WIDTH / 2, SCRN_HEIGTH / 2), NAME_PLAYER_SHIP, textureGame.playerTexture);
	player.ship->health = float(player.maxHealth);
	player.playerState.isAlive = true;
	player.ship->damage = float(player.maxDamage);
	player.ship->speed = SPEED_HERO;
	player.playerState.isMove = true;
}

void Player::CheckPlayerLife() {
	playerState.isAlive = ship->health > 0;
}

void Player::AddBullet(Texture & texture, Vector2f posPoint, float time, String name) {
	if (playerState.isShoot) {
		timeCreateBullet += clock.restart(); 
		if (timeCreateBullet.asSeconds() > time) { // Зависимость появления пули от времени
			directionShoot = RIGHT;
			Shoot addBullet(ship->sprite->getPosition(), ship->sizeObject, directionShoot, texture, name);
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

void Control(Player & player, Event & event) {
	if (player.ship->health > 0 && player.playerState.isMove) {
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = UP_LEFT;
			player.ship->direction = UP_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = UP_RIGHT;
			player.ship->direction = UP_RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = DOWN_LEFT;
			player.ship->direction = DOWN_LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = DOWN_RIGHT;
			player.ship->direction = DOWN_RIGHT;
			//----------------------------- По вертикали или горизантали ----------------------------
		}
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.direction = UP;
			player.ship->direction = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.direction = DOWN;
			player.ship->direction = DOWN;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.direction = RIGHT;
			player.ship->direction = RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.direction = LEFT;
			player.ship->direction = LEFT;
		}
		else {
			player.direction = NONE;
			player.ship->direction = NONE;
		}
		if (event.type == Event::MouseWheelMoved) {
			if (event.mouseWheel.delta == 1) {
				if (player.gun < 2) {
					player.gun += 1;
				}
				else {
					player.gun = 0;
				}
			}
			if (event.mouseWheel.delta == -1) {
				if (player.gun > 0) {
					player.gun -= 1;
				}
				else {
					player.gun = 2;
				}
			}
		}
	}
	else {
		player.direction = NONE;
		player.ship->direction = NONE;
	}
}

void Player::ChangeWeapons(TextureGame & textureGame, Vector2f posPoint) {
	if (playerState.isShoot) {
		if (gun == 0) { 
			AddBullet(textureGame.blueLaserTexture, posPoint, float(TIME_CREATE_BULLET), NAME_BULLET);
		}
		else if (gun == 1) { 
			AddBullet(textureGame.redLaserTexture, posPoint, float(TIME_CREATE_BULLET), NAME_BULLET);
		}
		else if (gun == 2) {
			AddBullet(textureGame.greenLaserTexture, posPoint, float(TIME_CREATE_BULLET), NAME_BULLET);
		}
	}
}

void MovePlayer(Player & player, const Time & deltaTime, RenderWindow & window) {
	player.ship->MoveObject(deltaTime);
	player.ship->sprite->move(Border(*player.ship, window));
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
	player.gun = 0;
	player.levelGame = 1;
	player.playerState.isIncreaseDamage = false;
	player.playerState.isInvulnerability = false;
	player.playerState.isDecrease = false; 
	player.ship->sprite->setColor(Color::White);
}