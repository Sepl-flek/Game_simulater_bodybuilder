#include "Person.h"

Person::Person(float scale)
{
	
	person.setTexture(AssetManager::GetTexture("image/pperson2.png"));
	person.setTextureRect(sf::IntRect(xsp[0], ysp, widthsp[0], heightsp));
	person.setPosition(1000, 1000);
	person.setScale(scale, scale);
}



//передвижение
void Person::move(sf::Vector2f move_rec, float wedth, float height)
{
	person.move(move_rec);
	sf::Vector2f pos = person.getPosition();
	if (pos.x > (wedth - 100)) person.setPosition(wedth - 100, pos.y);
	if (pos.x < 10) person.setPosition(10, pos.y);
	if (pos.y > (height - 100)) person.setPosition(pos.x, (height - 100));
	if (pos.y < 0) person.setPosition(pos.x, 0);

	if (pos.x > (wedth - 100) && pos.y > (height - 100)) person.setPosition(wedth - 100, height - 100);
	if (pos.x > (wedth - 100) && pos.y < 0) person.setPosition(wedth - 100, 0);
	if (pos.x < 10 && pos.y > (height - 100)) person.setPosition(10,height - 100);
	if (pos.x < 10 && pos.y < 0) person.setPosition(10, 0);

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
	int in_animation = 2;
	if (trafic == 1) {
		if (step_animation <= 1)
		{
			person.setTextureRect(sf::IntRect(xsp[in_animation], ysp, widthsp[in_animation], heightsp));
			step_animation = 2;
		}
		if (12 > step_animation >= 1)
		{
			step_animation += 1;
			person.setTextureRect(sf::IntRect(xsp[step_animation], ysp, widthsp[step_animation], heightsp));
		}
		else 
		{
			step_animation = 4;
			person.setTextureRect(sf::IntRect(xsp[step_animation], ysp, widthsp[step_animation], heightsp));
		}
		
	}
	else if (trafic == 0) {
		step_animation = 0;
		person.setTextureRect(sf::IntRect(xsp[step_animation], ysp, widthsp[step_animation], heightsp));
	}
	else if (trafic == 2)
	{
		if (step_animation <= 1)
		{
			step_animation = 2;
			person.setTextureRect(sf::IntRect(xspl[step_animation - 2], yspl, widthsp[step_animation], heightsp));
			
		}
		if (12 > step_animation >= 1)
		{
			step_animation += 1;
			person.setTextureRect(sf::IntRect(xspl[step_animation - 2], yspl, widthsp[step_animation], heightsp));
		}
		else
		{
			step_animation = 4;
			person.setTextureRect(sf::IntRect(xspl[step_animation - 2], yspl, widthsp[step_animation], heightsp));
		}
	}
}

sf::Vector2f Person::get_position()
{
	return person.getPosition();
}

sf::FloatRect Person::get_global_bounds() const
{
	return person.getGlobalBounds();
}
