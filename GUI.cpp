#include "GUI.h"

static const float RATIO_HEALTH = 287.f;
static const float HEIGHT_BAR = 15.f;
static const int INDENT = 5;

void S_GUI::InitGUI(TextureGame & textureGame) {
	
	decreaseSprite.setTexture(textureGame.decreaseTexture);
	InitSpriteGUI(decreaseSprite, textureGame.decreaseTexture);

	increaseSprite.setTexture(textureGame.increaseTexture);
	InitSpriteGUI(increaseSprite, textureGame.increaseTexture);

	invulnerabilitySprite.setTexture(textureGame.invulnerabilityTexture);
	InitSpriteGUI(invulnerabilitySprite, textureGame.invulnerabilityTexture);

	tripleShotSprite.setTexture(textureGame.tripleShotTexture);
	InitSpriteGUI(tripleShotSprite, textureGame.tripleShotTexture);

	doubleShotSprite.setTexture(textureGame.doubleShotTexture);
	InitSpriteGUI(doubleShotSprite, textureGame.doubleShotTexture);

	healthBar.setTexture(textureGame.healthBarTexture);
	InitSpriteGUI(healthBar, textureGame.healthBarTexture);
	healthBar.setOrigin(0, 0);

	bar.setFillColor(Color::Black);
}

void InitSpriteGUI(Sprite & sprite, Texture & texture) {
	Vector2u sizeBonus = texture.getSize();
	sprite.setTextureRect(IntRect(0, 0, int(sizeBonus.x), int(sizeBonus.y)));
	sprite.setOrigin(float(sizeBonus.x / 2.f), float(sizeBonus.y / 2.f));
	sprite.setScale(1.5f, 1.5f);
}

void UpdateState(Sprite & sprite, RenderWindow & window, Text & textTime) {
	Vector2f sizeBonus = Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
	Vector2u sizeWindow = window.getSize();
	Vector2f sizeText = Vector2f(textTime.getLocalBounds().width, textTime.getLocalBounds().height);
	sprite.setPosition(sizeWindow.x - sizeBonus.x - INDENT, sizeWindow.y - sizeBonus.y - INDENT);
	textTime.setPosition(sizeWindow.x - sizeText.x - 2 * sizeBonus.x - INDENT, sizeWindow.y - sizeText.y / 2.f - sizeBonus.y  - INDENT);
}

void UpdateStateBar(Sprite & sprite, RenderWindow & window) {
	Vector2f sizeBar = Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
	Vector2u sizeWindow = window.getSize();
	sprite.setPosition(INDENT * 2, sizeWindow.y - sizeBar.y - INDENT * 4.f);
}

void S_GUI::UpdateGUI(TextWithInfo & textGame, float timeUseBonus, PlayerState & state, RenderWindow & window) {
	
	if (state.isDecrease) {
		UpdateState(decreaseSprite, window, textGame.textTimeUseBonus);
		String timeStr = to_string(TIME_USE_DECREASE_IN_SECONDS - int(timeUseBonus));
		textGame.textTimeUseBonus.setString(timeStr);
	}
	else  if (state.isIncreaseDamage) {
		UpdateState(increaseSprite, window, textGame.textTimeUseBonus);
		String timeStr = to_string(TIME_USE_INCREASE_IN_SECONDS - int(timeUseBonus));
		textGame.textTimeUseBonus.setString(timeStr);
	}
	else  if (state.isInvulnerability) {
		UpdateState(invulnerabilitySprite, window, textGame.textTimeUseBonus);
		String timeStr = to_string(TIME_USE_INVULNERABILITY_IN_SECONDS - int(timeUseBonus));
		textGame.textTimeUseBonus.setString(timeStr);
	}
	else  if (state.isTripleShot) {
		UpdateState(tripleShotSprite, window, textGame.textTimeUseBonus);
		String timeStr = to_string(TIME_USE_TRIPLE_SHOT_IN_SECONDS - int(timeUseBonus));
		textGame.textTimeUseBonus.setString(timeStr);
	}
	else  if (state.isDoubleShot) {
		UpdateState(doubleShotSprite, window, textGame.textTimeUseBonus);
		String timeStr = to_string(TIME_USE_DOUBLE_SHOT_IN_SECONDS - int(timeUseBonus));
		textGame.textTimeUseBonus.setString(timeStr);
	}

	UpdateStateBar(healthBar, window);
}

void UpdateHealthBar(RectangleShape & bar, float health, FloatRect & healthBar, Sprite & sprite) {
	if (health > 0) {
		if (health <= MAX_HEALTH) {
			Vector2f sizeSprite = Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
			bar.setPosition(sprite.getPosition().x + sizeSprite.x * 3 - 8.f, sprite.getPosition().y + sizeSprite.y - 3);
			bar.setSize(Vector2f(-float((MAX_HEALTH - health) * RATIO_HEALTH / MAX_HEALTH), HEIGHT_BAR));
		}
	}
}

void S_GUI::DrawGUI(TextWithInfo & textGame, PlayerState & state, RenderWindow & window) {
	if (state.isDecrease)	{
		window.draw(decreaseSprite);
		window.draw(textGame.textTimeUseBonus);
	}
	else  if (state.isIncreaseDamage) {
		window.draw(increaseSprite);
		window.draw(textGame.textTimeUseBonus);
	}
	else  if (state.isInvulnerability) {
		window.draw(invulnerabilitySprite);
		window.draw(textGame.textTimeUseBonus);
	}
	else  if (state.isDoubleShot) {
		window.draw(doubleShotSprite);
		window.draw(textGame.textTimeUseBonus);
	}
	else  if (state.isTripleShot) {
		window.draw(tripleShotSprite);
		window.draw(textGame.textTimeUseBonus);
	}
	window.draw(healthBar);
	window.draw(bar);
}