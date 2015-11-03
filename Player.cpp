#include "Player.h"

using namespace sf;
using namespace std;

void InitializePlayer(Player & player) {
	player.bullet = new list<Shoot>;
	player.shape = new RectangleShape;
	player.texture = new Texture;
	player.sprite = new Sprite;
	player.texture->loadFromFile("resourse/images/heroship2.png");
	player.sprite->setTexture(*player.texture);
	player.sprite->setTextureRect(IntRect(0, 0, WIDTH, HEIGTH));
	player.sprite->setPosition(SCRN_HEIGTH / 2, SCRN_WIDTH / 2);
	player.sprite->setOrigin(WIDTH / 2, HEIGTH / 2);
	player.sprite->setRotation(90);

	// ������������� ���� ������� (����� ��� ������� �����������)
	Vector2f size = { a, a };
	player.shape->setSize(size);
	player.shape->setFillColor(Color::White);
	
	player.shape->setOrigin(WIDTH / 2, HEIGTH / 2);
	//player.vX = player.sprite->getPosition().x + WIDTH / 2;
	//player.vY = player.sprite->getPosition().y - HEIGTH / 4;
	//player.shape->setPosition(player.sprite->getPosition().x, player.sprite->getPosition().y);
	//cout << player.shape->getPosition().x << " " << player.shape->getPosition().y << endl;
}

Shoot::Shoot(float X, float Y, float width, float heigth, Direction direction, String path) {
	texture = new Texture;
	sprite = new Sprite;
	texture->loadFromFile(path);
	sprite->setTexture(*texture);
	sprite->setOrigin(WIDTH_BULLET / 2, HEIGTH_BULLET / 2);
	sprite->setPosition(X + HEIGTH / 8, Y + WIDTH / 8);
	dir = direction;
	x = X;
	y = Y;
	life = true;
}

void Player::CheckPlayerLife() {
	playerState.isAlive = lifePlayer > 0;
}

void Shoot::MoveBullet(const Time & deltaTime) {
	Vector2f movement = sprite->getPosition();
	
	switch (dir) {
	case UP: movement.y = -SPEED_BULLET;
		movement.x = 0;
		sprite->setRotation(-90);
		break;
	case DOWN: movement.y = SPEED_BULLET; 
		movement.x = 0;
		sprite->setRotation(90);
		break;
	case LEFT: movement.x = -SPEED_BULLET;
		movement.y = 0;
		sprite->setRotation(-180);
		break;
	case RIGHT: movement.x = SPEED_BULLET;
		movement.y = 0;
		break;
	case UP_LEFT: movement.x = -SPEED_BULLET;
		movement.y = -SPEED_BULLET;
		sprite->setRotation(-135);
		break;
	case UP_RIGHT: movement.x = SPEED_BULLET;
		movement.y = -SPEED_BULLET;
		sprite->setRotation(-45);
		break;
	case DOWN_RIGHT: movement.x = SPEED_BULLET;
		movement.y = SPEED_BULLET;
		sprite->setRotation(45);
		break;
	case DOWN_LEFT: movement.x = -SPEED_BULLET;
		movement.y = SPEED_BULLET;
		sprite->setRotation(135);
		break;
	default:
		life = false; // ����� �������� ��� ��������� �������
					  // ����� ����� ��������� �������������� ���� �������
		break;
	}
	
	x = movement.x * deltaTime.asSeconds();
	y = movement.y * deltaTime.asSeconds();
	
	//----------------- �������� --------------------------
	// ���� ������ �� �����, �� ���������� ���� �������������
	if (sprite->getPosition().x < 0 - WIDTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().y < 0 - WIDTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().x >= SCRN_WIDTH  + WIDTH_BULLET) {
		life = false;
	}
	if (sprite->getPosition().y >= SCRN_HEIGTH + HEIGTH_BULLET) {
		life = false;
	}
	//------------------------------------------------------
	//std::cout << x << " " << y << endl;
	sprite->move(x, y);
}

void Player::AddBullet(RenderWindow & window) {
	
	if (playerState.isShoot) {
		posMouse = Mouse::getPosition(window);
		timeCreateBullet += clock.restart(); 
		if (timeCreateBullet.asSeconds() > 0.1) { // ����������� ��������� ���� �� �������
			//directionShoot = GetDirectionShoot(Mouse::getPosition(window), sprite->getPosition());
			directionShoot = RIGHT;
			Shoot addBullet(sprite->getPosition().x, sprite->getPosition().y, WIDTH_BULLET, HEIGTH_BULLET, directionShoot, "resourse/images/laser-blue.png");
			bullet->push_back(addBullet); // �������� ���� � ��������� �� � ������
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
	//----------------------------------------- ������� �������� ������� ----------------------------

	if (Keyboard::isKeyPressed(Keyboard::Left)) // ������ �������
		player.dirRotation = { -1, 0 };
	else if (Keyboard::isKeyPressed(Keyboard::Right)) // �� �������
		player.dirRotation = { 1, 0 };
	else if (Keyboard::isKeyPressed(Keyboard::Up)) // �o �������
		player.dirRotation = { 0, 1 };
	else if (Keyboard::isKeyPressed(Keyboard::Down)) // ������ �������
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
	player.x = movement.x * deltaTime.asSeconds();
	player.y = movement.y * deltaTime.asSeconds();
	
	
	//------------------------- ������� ��������� -----------------------------------
	/*player.rotation += player.dirRotation.x * ANGLE;
	player.rotation += player.dirRotation.y * ANGLE;*/
	
	/*player.sprite->setRotation(player.rotation);
	player.shape->setRotation(player.rotation);
	player.shape->setPosition(player.sprite->getPosition());

	player.vX = player.sprite->getPosition().x + WIDTH / 2; // ������������ �������
	player.vY = player.sprite->getPosition().y - HEIGTH / 4;*/
}
