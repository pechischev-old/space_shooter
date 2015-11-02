#include <SFML/Graphics.hpp>
#include "Config.h"

using namespace sf;

View view;

void ChangeView() {

	if (Keyboard::isKeyPressed(Keyboard::L)) {
		view.setSize(SCRN_HEIGTH * 2, SCRN_WIDTH * 2);  //масштабируем, уменьшение
	}

	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(SCRN_HEIGTH, SCRN_WIDTH);  //устанавливает размер камеры (наш исходный)
		view.setCenter(SCRN_HEIGTH / 2, SCRN_WIDTH / 2); // устанавливает камеру на центр окна, т.е. в исходную позицию
	}
}