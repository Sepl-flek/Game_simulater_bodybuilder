#include "Meteor.h"

Meteor::Meteor()
{
	texture_object.loadFromFile("pictures/asteroid.png");
	space_object.setTexture(texture_object);
	space_object.setTextureRect(sf::IntRect(262, 325, 55, 50));

	restart();
}

Meteor::~Meteor()
{
}

void Meteor::move(float& time)
{
	space_object.move(static_cast<float>(-0.5 * time), 0);
	if (space_object.getPosition().x < -60) {
		restart();
	}
}

void Meteor::draw(sf::RenderWindow& window)
{
	window.draw(space_object);
}

void Meteor::animation()
{
	if (st > 0) {
		space_object.setTextureRect(sf::IntRect(xsp[ix], ysp[iy], 50, 45));
		ix += st;
		ix = ix % 5;
		iy += 1;
		iy %= 6;
	}
}

bool Meteor::collision(sf::FloatRect object)
{

	return space_object.getGlobalBounds().intersects(object);
}

void Meteor::restart()
{
	float scale = static_cast<float>((rand() % 13 + 5) / 10);
	float x = static_cast<float>(rand() % 1280 + 1280);
	float y = static_cast<float>(rand() % 540 + 130);

	space_object.setPosition(sf::Vector2f(x, y));

	space_object.setScale(scale, scale);

	ix = rand() % 4;
	iy = rand() % 5;
	st = rand() % 2;
}

sf::FloatRect Meteor::get_meteor_bounds()
{
	return space_object.getGlobalBounds();
}