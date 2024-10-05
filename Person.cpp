#include "Person.h"

Person::Person(float scale)
{
	
	person.setTexture(AssetManager::GetTexture("image/pperson.png"));
	person.setTextureRect(sf::IntRect(xsp[0], ysp, widthsp[0], heightsp));
	person.setPosition(1000, 1000);
	person.setScale(scale, scale);
}



//передвижение
void Person::move(sf::Vector2f move_rec, float wedth, float height)
{
	person.move(move_rec);
	sf::Vector2f pos = person.getPosition();
	if (pos.x > wedth) person.setPosition(wedth, pos.y);
	if (pos.x < 50) person.setPosition(50, pos.y);
	if (pos.y > (height - 100)) person.setPosition(pos.x, (height - 100));
	if (pos.y < 0) person.setPosition(pos.x, 0);

	if (pos.x > wedth && pos.y > (height - 100)) person.setPosition(wedth, height - 100);
	if (pos.x > wedth && pos.y < 0) person.setPosition(wedth, 0);
	if (pos.x < 50 && pos.y > height) person.setPosition(50, height);
	if (pos.x < 50 && pos.y < 0) person.setPosition(50, 0);

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

void Person::animation(int trafic)
{

}
