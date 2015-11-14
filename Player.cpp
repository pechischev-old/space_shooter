#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player) {
	player.bullet = new list<Shoot>;
	player.ship = new Entity(250, 250, "sokol");
	player.ship->health = 500;
	player.playerState.isAlive = true;
	/*
	// »нициализаци€ носа корабл€ (нужно дл€ вектора направлени€)
	Vector2f size = { a, a };
	player.shape->setSize(size);
	player.shape->setFillColor(Color::White);
	
	player.shape->setOrigin(WIDTH / 2, HEIGTH / 2);
	//player.vX = player.sprite->getPosition().x + WIDTH / 2;
	//player.vY = player.sprite->getPosition().y - HEIGTH / 4;
	//player.shape->setPosition(player.sprite->getPosition().x, player.sprite->getPosition().y);
	//cout << player.shape->getPosition().x << " " << player.shape->getPosition().y << endl;*/
}

void Player::CheckPlayerLife() {
	playerState.isAlive = ship->health > 0;
}

void Player::AddBullet(RenderWindow & window) {
	if (playerState.isShoot) {
		posMouse = Mouse::getPosition(window);
		timeCreateBullet += clock.restart(); 
		if (timeCreateBullet.asSeconds() > 0.1) { // «ависимость по€влени€ пули от времени
			//directionShoot = GetDirectionShoot(Mouse::getPosition(window), sprite->getPosition());
			directionShoot = RIGHT;
			Shoot addBullet(ship->sprite->getPosition().x, ship->sprite->getPosition().y, ship->width, ship->height, directionShoot, "resourse/images/laser-blue.png");
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
			//----------------------------- ѕо вертикали или горизантали ----------------------------
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
		//-----------------------------------------  лавиши поворота спрайта ----------------------------

		if (Keyboard::isKeyPressed(Keyboard::Left)) // против часовой
			player.dirRotation = { -1, 0 };
		else if (Keyboard::isKeyPressed(Keyboard::Right)) // по часовой
			player.dirRotation = { 1, 0 };
		else if (Keyboard::isKeyPressed(Keyboard::Up)) // пo часовой
			player.dirRotation = { 0, 1 };
		else if (Keyboard::isKeyPressed(Keyboard::Down)) // против часовой
			player.dirRotation = { 0, -1 };
		else player.dirRotation = { 0, 0 };

	}
}

Direction GetDirectionShoot(Vector2i posMouse, Vector2f posPlayer) {
	Direction dir;
	if (posPlayer.x > posMouse.x && ((posPlayer.y - 50) <= posMouse.y <= (posPlayer.y + 50)))
		dir = LEFT;
	if (posPlayer.x < posMouse.x && posPlayer.y == posMouse.y)
		dir = RIGHT;
	if (posPlayer.y > posMouse.y && posPlayer.x == posMouse.x)
		dir = DOWN;
	if (posPlayer.y < posMouse.y && posPlayer.x == posMouse.x)
		dir = UP;
	if (posPlayer.x > posMouse.x && posPlayer.y > posMouse.y)
		dir = UP_LEFT;
	if (posPlayer.x < posMouse.x && posPlayer.y > posMouse.y)
		dir = UP_RIGHT;
	if (posPlayer.x > posMouse.x && posPlayer.y < posMouse.y)
		dir = DOWN_LEFT;
	if (posPlayer.x < posMouse.x && posPlayer.y < posMouse.y)
		dir = DOWN_RIGHT;
	return dir;
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
		break;
	}
	player.ship->x = movement.x * deltaTime.asSeconds();
	player.ship->y = movement.y * deltaTime.asSeconds();


	//------------------------- ѕоворот персонажа -----------------------------------
	/*player.rotation += player.dirRotation.x * ANGLE;
		player.rotation += player.dirRotation.y * ANGLE;*/

	/*player.sprite->setRotation(player.rotation);
	player.shape->setRotation(player.rotation);
	player.shape->setPosition(player.sprite->getPosition());

	player.vX = player.sprite->getPosition().x + WIDTH / 2; // Ќаправл€юща€ вектора
	player.vY = player.sprite->getPosition().y - HEIGTH / 4;*/
}

void Player::UpdateStatePlayerBullet(const Time & deltaTime) {
	for (list<Shoot>::iterator it = bullet->begin(); it != bullet->end();) {
		//cout << player.bullet->size() << endl;
		it->MoveBullet(deltaTime);
		if (!it->life) {
			it->texture->~Texture();
			it = bullet->erase(it);
		}
		else  it++;
	}
}

Vector2f Border(Player & player) {
	Vector2f limit(0.f, 0.f);
	float heigth = player.ship->height,
		width = player.ship->width,
		X = player.ship->x,
		Y = player.ship->y;
	Vector2f posPlayer = player.ship->sprite->getPosition();
	
	if (SCRN_WIDTH <= posPlayer.x + width / 2) {
		X = -BORDER;
	}
	if (0 >= posPlayer.x - width / 2) {
		X = BORDER;
	}
	if (SCRN_HEIGTH <= posPlayer.y + heigth / 2) {
		Y = -BORDER;
	}
	if (0 >= posPlayer.y - heigth / 2) {
		Y = BORDER;
	}
	limit.x = X;
	limit.y = Y;
	return limit;
}