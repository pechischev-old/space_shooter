#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player) {
	player.bullet = new list<Shoot>;
	player.ship = new Entity(250, 250, 120, 50, "heroship2");
	player.ship->sprite->setRotation(90);
	player.ship->health = 100;
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
			Shoot addBullet(ship->sprite->getPosition().x, ship->sprite->getPosition().y, WIDTH_BULLET, HEIGTH_BULLET, directionShoot, "resourse/images/laser-blue.png");
			bullet->push_back(addBullet); // создание пули и занесение ее в список
			timeCreateBullet = Time::Zero;
		}
		playerState.isShoot = false;
	}
}

void Control(Player & player) {
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

Vector2f Border(float X, float Y, Vector2f posPlayer, int rotation) {
	Vector2f limit(0.f, 0.f);
	float heigth = HEIGTH,
		width = WIDTH;
	if (SCRN_WIDTH <= posPlayer.x + heigth / 2) {
		X = -BORDER;
	}
	if (0 >= posPlayer.x - heigth / 2) {
		X = BORDER;
	}
	if (SCRN_HEIGTH <= posPlayer.y + width / 2) {
		Y = -BORDER;
	}
	if (0 >= posPlayer.y - width / 2) {
		Y = BORDER;
	}
	limit.x = X;
	limit.y = Y;
	return limit;
}