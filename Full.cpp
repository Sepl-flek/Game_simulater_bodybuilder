#include "Full.h"

Full::Full(sf::String name, int x, int y)
{
	texture_object.loadFromFile(name);
	space_object.setTexture(texture_object);
	space_object.setTextureRect(sf::IntRect(0, 0, x, y));
	int scal = 1000 / x;
	space_object.setScale(0.1 * scal, 0.1 * scal);
	restart();
}

Full::~Full()
{
}

void Full::restart()
{
	new_born = true;
	float x = static_cast<float>(rand() % (width)+width);
	float y = static_cast<float>(rand() % (height - 113) + 130);

	space_object.setPosition(sf::Vector2f(x, y));
	PosBonus = space_object.getPosition();
}