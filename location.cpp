#include "location.h"


void GymPlay(Person& person, sf::RenderWindow& window)
{
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	float scaleY = height / 512;
	float scaleX = width / 512;
	person.set_position(5*scaleX,270*scaleY);


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

	Collision exit(0, 287 * scaleY, 35 * scaleX, 35 * scaleX);
	Collision treadmills(260 * scaleX, 110 * scaleY, 180 * scaleX, 45 * scaleY);
	Collision wall(0, 110 * scaleY, 512 * scaleX, 27 * scaleY);
	Collision squat(440 * scaleX, 136 * scaleY, 70 * scaleX, 71 * scaleY);
	Collision soda(480 * scaleX, 217 * scaleY, 24 * scaleX, 50 * scaleY);
	Collision bench(365 * scaleX, 408 * scaleY, 111 * scaleX, 14 * scaleY);
	Collision bench2(413 * scaleX, 356 * scaleY, 21 * scaleX, 47 * scaleY);
	Collision wheel(265 * scaleX, 390 * scaleY, 70 * scaleX,  10 * scaleY);
	Collision bars(30 * scaleX, 425 * scaleY, 82 * scaleX, 18 * scaleY);
	Collision bars2(60 * scaleX, 390 * scaleY, 35 * scaleX, 30 * scaleY);

	std::vector<Collision> collisions { wall,treadmills, squat,soda, bench, bench2, wheel,bars, bars2};

	float time;
	sf::Clock clock, clockAnimPlay;
	sf::Music backgroundmusic;
	backgroundmusic.openFromFile("sound/gymplay_back.wav");

	backgroundmusic.setVolume(20);
	backgroundmusic.setLoop(true);
	backgroundmusic.play();

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		sf::Event event;

		//collision
		bool flag = true;
		for (int i = 0; i < collisions.size(); ++i) {

			if (collisions[i].collision(person))
			{
				flag = false;
				break;
			}
		}
		if(flag) {
			position = person.get_position();}
		//-----------------------------------------

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
				if( exit.collision(person) && event.key.code == sf::Keyboard::E)
				{
					background.setTexture(&AssetManager::GetTexture("image/black.png"));
					window.clear();
					window.draw(background);
					window.display();
					sf::sleep(sf::seconds(0.5));
					background.setTexture(&AssetManager::GetTexture("image/background2.png"));
					person.set_position(475 * scaleX, 145 * scaleY);
					person.set_scale(2, 2);
					backgroundmusic.stop();
					return;
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

		
		// коллизии 
		if (!flag)
		{
			person.set_position(position.x, position.y);
		}
		person.move(moveRec, width, height);
		//if (near_bed.collision(person)) { bed.change_color(sf::Color::Yellow); }
		//else { bed.change_color(sf::Color(0, 0, 0, 0)); }

		if (exit.collision(person)) { exit.change_color(sf::Color::Yellow); }
		else { exit.change_color(sf::Color(0, 0, 0, 0)); }

		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));

		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));


		window.clear();
		window.draw(background);
		window.draw(exit.get_rect());
		person.draw(window);
		window.draw(text);
		window.draw(day);
		person.draw_interface(window, scaleX, scaleY);
		window.display();
	}
}
