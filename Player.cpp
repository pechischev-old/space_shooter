#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player, TextureGame & textureGame) {
	player.bullet = new list<Shoot>;
	
	player.ship = new Entity(250, 250, NAME_PLAYER_SHIP, *textureGame.playerTexture);
	player.ship->health = player.maxHealth;
	player.playerState.isAlive = true;
	player.ship->damage = player.maxDamage;
	player.ship->speed = SPEED_HERO;
}

void Player::CheckPlayerLife() {
	playerState.isAlive = ship->health > 0;
}

void Player::AddBullet() { 
	if (playerState.isShoot) {
		timeCreateBullet += clock.restart(); 
		if (timeCreateBullet.asSeconds() > TIME_CREATE_BULLET) { // ����������� ��������� ���� �� �������
			directionShoot = RIGHT;
			Shoot addBullet(ship->sprite->getPosition().x, ship->sprite->getPosition().y, ship->width, ship->height, directionShoot, PATH_TO_BLUE_BULLET);
			addBullet.damage = ship->damage;
			addBullet.sprite->setScale(scaleBullet, scaleBullet);
			bullet->push_back(addBullet); // �������� ���� � ��������� �� � ������
			timeCreateBullet = Time::Zero;
		}
		//------------------------------
		playerState.isShoot = false;
	}
}

void Player::UpdateStateBulletPlayer(const Time & deltaTime, RenderWindow & window) {
	for (list<Shoot>::iterator it = bullet->begin(); it != bullet->end();) {
		it->CheckForCollisions(window);
		it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
			delete it->sprite;
			it = bullet->erase(it);
		}
		else  ++it;
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
			//----------------------------- �� ��������� ��� ����������� ----------------------------
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