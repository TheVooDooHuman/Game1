#include <SFML\Graphics.hpp>

;

using namespace sf;

sf::View view;

int speed = 5;

View getPlayerCoordinateForView(float x, float y)
{
	float tempX = x;float tempY = y;

	if (x < 320) tempX = 320;
	if (y < 240) tempY = 240;
	if (y > 560) tempY = 560;

	view.setCenter(tempX, tempY);
	return view;
}
