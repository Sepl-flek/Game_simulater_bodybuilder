#include "location.h"


void GymPlay(Person& person, sf::RenderWindow& window)
{
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	float scaleY = height / 512;
	float scaleX = width / 512;

	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/black.png"));
	window.clear();
	window.draw(background);
	window.display();
	sf::sleep(sf::seconds(0.5));
	background.setTexture(&AssetManager::GetTexture("image/gym.png"));

	sf::Text day;
	day.setFont(AssetManager::GetFont("font/mainmenu.otf")); // Устанавливаем шрифт
	day.setCharacterSize(50); // Размер шрифта
	day.setFillColor(sf::Color::White); // Цвет текста

	sf::Text text;
	text.setFont(AssetManager::GetFont("font/mainmenu.otf")); // Устанавливаем шрифт
	text.setCharacterSize(50); // Размер шрифта
	text.setFillColor(sf::Color::White); // Цвет текста

	text.setPosition(10 * scaleX, 10 * scaleY);
	day.setPosition(70 * scaleX, 10 * scaleY);
	person.set_scale(3, 3);

	sf::Vector2f position = person.get_position();

	const float parametr = 2;
	int traffic = 0;
	sf::Vector2f moveRec;

	float time;
	sf::Clock clock, clockAnimPlay;
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		sf::Event event;

		//if ( ) {// collsion
		//	position = person.get_position();}

		while (window.pollEvent(event))
		{

			if (event.key.code == sf::Keyboard::Escape) { window.close(); }


			switch (event.type)
			{
			case sf::Event::KeyPressed: // кнопка нажата
				if ((event.key.code == sf::Keyboard::S)) {
					moveRec.y = parametr * time;
					traffic = 2;

				}
				if ((event.key.code == sf::Keyboard::W)) {
					moveRec.y = -parametr * time;
					traffic = 1;
				}
				if ((event.key.code == sf::Keyboard::A)) {
					moveRec.x = -parametr * time;
					traffic = 2;

				}
				if ((event.key.code == sf::Keyboard::D)) {
					moveRec.x = parametr * time;
					traffic = 1;
				}
				

				break;

			case sf::Event::KeyReleased: //кнопка отпущена 
				if ((event.key.code == sf::Keyboard::S)) {
					moveRec.y = 0;
					traffic = 0;

				}
				if ((event.key.code == sf::Keyboard::W)) {
					moveRec.y = 0;
					traffic = 0;
				}
				if ((event.key.code == sf::Keyboard::A)) {
					moveRec.x = 0;
					traffic = 0;
				}
				if ((event.key.code == sf::Keyboard::D)) {
					moveRec.x = 0;
					traffic = 0;
				}
				break;

			default:
				break;

			}
		}
		if (clockAnimPlay.getElapsedTime() > sf::milliseconds(100)) {
			clockAnimPlay.restart();

			person.animation(traffic);

		}

		//if (near_door.collision(person))
		//{
		//	door.change_color(sf::Color::Yellow);
		//}
		//else
		//{
		//	door.change_color(sf::Color(0, 0, 0, 0));
		//}

		person.move(moveRec, width, height);
		//// коллизии 
		//if ()
		//{
		//	person.set_position(position.x, position.y);
		//}

		//if (near_bed.collision(person)) { bed.change_color(sf::Color::Yellow); }
		//else { bed.change_color(sf::Color(0, 0, 0, 0)); }

		//if (full_fridge.collision(person)) { full_fridge.change_color(sf::Color::Yellow); }
		//else { full_fridge.change_color(sf::Color(0, 0, 0, 0)); }
		//text.setString("Money: " + std::to_string(person.get_money()));
		//day.setString("Day: " + std::to_string(person.get_day()));

		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));

		window.clear();
		window.draw(background);
		
		person.draw(window);
		window.draw(text);
		window.draw(day);
		person.draw_interface(window, scaleX, scaleY);
		window.display();
	}
}
