#include "Collision.h"

Collision::Collision(float x, float y, float width, float height):x(x),y(y),width(width),height(height)
{
	collisia = sf::FloatRect(x, y, width, height);
	rect = sf::RectangleShape( sf::Vector2f(width, height));
	rect.setOutlineThickness(5);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setPosition(x, y);
}

bool Collision::collision(Person &person)
{
	return person.get_global_bounds().intersects(collisia);
}

void Collision::change_color(const sf::Color &color)
{
	rect.setOutlineColor(color);
}

sf::RectangleShape Collision::get_rect()
{
	return rect;
}

