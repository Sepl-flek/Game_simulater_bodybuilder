#include "Collision.h"

Collision::Collision(float x, float y, float width, float height):x(x),y(y),width(width),height(height)
{
	rect = sf::FloatRect(x, y, width, height);
}

bool Collision::collision(Person person)
{
	return person.get_global_bounds().intersects(rect);
}

bool Collision::collisionX(float person_x)
{
	return person_x == (x + width);
}

bool Collision::collisionY(float person_y)
{
	return person_y == (y + height);
}
