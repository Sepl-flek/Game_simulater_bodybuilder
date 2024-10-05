#include "Person.h"

Person::Person(float scale)
{
	
	person.setTexture(AssetManager::GetTexture("image/pperson.png"));
	person.setTextureRect(sf::IntRect(xsp[0], ysp, width[0], height));
	person.setPosition(1000, 1000);
	person.setScale(scale, scale);
}

void Person::PlayerMove(sf::Sprite& person, sf::Vector2f& moveRec)
{
}

void Person::move(float& time)
{
}

void Person::set_position(float x, float y)
{
	person.setPosition(x, y);
}

void Person::set_scale(float x, float y)
{
	person.setScale(x, y);
}

void Person::draw(sf::RenderWindow& window)
{
	window.draw(person);
}

void Person::animation()
{

}
