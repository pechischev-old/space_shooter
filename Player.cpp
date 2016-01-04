#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player, TextureGame & textureGame, SSound & sSound) {
	player.ship = new Entity(Vector2f(SCRN_WIDTH / 2, SCRN_HEIGTH / 2), NAME_PLAYER_SHIP, textureGame.playerTexture, sSound, 15);
	player.ship->health = float(player.maxHealth);
	player.playerState.isAlive = true;
	player.ship->damage = float(player.maxDamage);
	player.ship->speed = SPEED_HERO;
	player.playerState.isMove = true;
	player.takeBonus.setBuffer(sSound.takeBonusSound);
}

void Player::CheckPlayerLife() {
	playerState.isAlive = ship->health > 0;
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

void  Player::ChangeTypeFire(TextureGame & textureGame, Vector2f posPoint) {
	if (playerState.isShoot) {
		timeCreateBullet += clock.restart();
		if (timeCreateBullet.asSeconds() > TIME_CREATE_BULLET) { // Зависимость появления пули от времени
			ship->shootSound.play();
			Vector2f posShip = ship->sprite->getPosition();
			int begin;
			int count;
			int diff;
			Texture *texture = NULL;
			float angle = ship->sprite->getRotation();
			if (playerState.isDoubleShot) {
				begin = -1;
				count = 2;
				diff = 2;
				texture = &textureGame.blueLaserTexture;
			}
			else if (playerState.isTripleShot) {
				begin = -1;
				count = 2;
				diff = 1;
				texture = &textureGame.greenLaserTexture;
			}
			else {
				begin = 0;
				count = 1;
				diff = 1;
				texture = &textureGame.blueLaserTexture;
			}
		//	cout << Math::Normalize(posShip, posPoint).x << "  " << Math::Normalize(posShip, posPoint).y << endl;
			Vector2f normalizePath = Math::Normalize(posShip, posPoint);
			for (int i = begin; i < count; i += diff) {
				Shoot addBullet(Vector2f(posShip.x + i * 15, posShip.y + i * 15), RIGHT, *texture, NAME_BULLET);
				addBullet.damage = int(ship->damage);
				addBullet.isOtherBullet = true;
				addBullet.rememPos = Vector2f(posPoint.x + i *20, posPoint.y + i * 20);
				addBullet.sprite->setScale(float(scaleBullet), float(scaleBullet));
				bullet.push_back(addBullet); // создание пули и занесение ее в список
			}
			timeCreateBullet = Time::Zero;
		}
		//------------------------------
		playerState.isShoot = false;
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
			//----------------------------- По вертикали или горизонтали ----------------------------
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
			player.ship->animationFrame = 0;
		}
	}
	else {
		player.direction = NONE;
		player.ship->direction = NONE;
		
	}
}

void Player::PlaySoundAtDead() {
	if (ship->explosionSound.getStatus() != ship->explosionSound.Playing)
		ship->explosionSound.play();
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
	Vector2u sizeTexture = textureGame.playerTexture.getSize();
	player.ship->sprite->setOrigin(sizeTexture.x / 2.f, sizeTexture.y / 2.f);
	player.ship->health = float(player.maxHealth);
	player.playerState.isAlive = true;
	player.ship->damage = float(player.maxDamage);
	player.ship->isLife = true;
	player.playerState.isMove = true;
	player.ship->isKilled = false;
	player.levelGame = 1;

	player.playerState.isIncreaseDamage = false;
	player.playerState.isInvulnerability = false;
	player.playerState.isDecrease = false; 
	player.playerState.isTripleShot = false;
	player.playerState.isDoubleShot = false;

	player.ship->sprite->setColor(Color::White);
}