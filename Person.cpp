#include "Person.h"

Person::Person(float scale)
{
	
	person.setTexture(AssetManager::GetTexture("image/pperson2.png"));
	person.setTextureRect(sf::IntRect(xsp[0], ysp, widthsp[0], heightsp));
	person.setPosition(1000, 1000);
	person.setScale(scale, scale);
	
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;

	energy.setTexture(AssetManager::GetTexture("image/energy.png"));
	energy.setPosition(1000, 1000);
	energy.setScale(sf::Vector2f(0.1, 0.1));
	energy.setPosition(sf::Vector2f(width - 380, 45));

	meat.setTexture(AssetManager::GetTexture("image/meat.png"));
	meat.setScale(0.1, 0.1);
	meat.setPosition(sf::Vector2f(width - 170, 35));
	
	rect_hunger.setOutlineThickness(5);
	rect_hunger.setFillColor(sf::Color(0, 0, 0, 0));
	rect_hunger.setOutlineColor(sf::Color::Red);
	rect_hunger.setPosition(sf::Vector2f(width - 230,40));
	full_rect_hunger.setFillColor(sf::Color::Red);
	full_rect_hunger.setPosition(sf::Vector2f(width - 230, 40));

	rect_lvl_sleep.setOutlineThickness(5);
	rect_lvl_sleep.setFillColor(sf::Color(0, 0, 0, 0));
	rect_lvl_sleep.setOutlineColor(sf::Color::Blue);
	rect_lvl_sleep.setPosition(sf::Vector2f(width - 460 ,40));
	full_rect_lvl_sleep.setFillColor(sf::Color::Blue);
	full_rect_lvl_sleep.setPosition(sf::Vector2f(width - 460, 40));
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

void Person::draw_interface(sf::RenderWindow& window, float scaleX, float scaleY)
{
	window.draw(rect_hunger);
	window.draw(full_rect_hunger);
	window.draw(rect_lvl_sleep);
	window.draw(full_rect_lvl_sleep);
	window.draw(energy);
	window.draw(meat);
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

void Person::update_hunger(int procant)
{

	hunger += procant;
	if (hunger > 100) {hunger = 100;}
	if (hunger < 0) { hunger = 0; }
	
	full_rect_hunger.setSize(sf::Vector2f(200 - hunger * 2,50));
}

void Person::update_sleep(int procant)
{
	lvl_sleep += procant;
	if (lvl_sleep > 100) lvl_sleep = 100;
	if (lvl_sleep < 0) lvl_sleep = 0;
	full_rect_lvl_sleep.setSize(sf::Vector2f(200 - lvl_sleep * 2, 50));
}

void Person::update_money(int coast)
{
	money -= coast;
}

void Person::update_day()
{
	day++;
}

int Person::get_hunger()
{
	return hunger;
}

int Person::get_money()
{
	return money;
}

int Person::get_lvl_sleep()
{
	return lvl_sleep;
}

int Person::get_day()
{
	return day;
}

