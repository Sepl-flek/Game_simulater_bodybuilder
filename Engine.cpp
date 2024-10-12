#include "Engine.h"
#include <iostream>




void Engine::setTextStyle(sf::Text& text, float x, float y, float size, const sf::Color& color,const std::string& content)
{
	text.setPosition(x, y);
	text.setString(content);
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void Engine::GameMenu()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),  L"BodyBuilder",sf::Style::Fullscreen );
	window.requestFocus();
	window.setActive(true);
	window.setMouseCursorVisible(false);

	std::vector<sf::String> name_menu = { L"Play","Load Game","Exit"};
	game::GameMenu mymenu(window, 1250, 600, 100, 250, name_menu);
	
	mymenu.setColorTextMenu(sf::Color(235, 78, 78), sf::Color::Yellow);
	mymenu.AlignMenu(2);

	//Задний фон
	sf::RectangleShape background(sf::Vector2f(width, heght));
	person.set_scale(5,5);
	person.set_position(1250, 700);

	background.setTexture(&AssetManager::GetTexture("image/menu.jpg"));

	sf::Text Titul;
	Titul.setFont(AssetManager::GetFont("font/mainmenu.otf"));

    
    setTextStyle(Titul, 770, 50, 120, sf::Color(235, 78, 78), "Bodybuilder Club");// параметры главного текста

	sf::Sound sound_next;
	sound_next.setBuffer(AssetManager::GetSoundBuffer("sound/audiomenu2.wav"));
	sf::Sound enter;
	enter.setBuffer(AssetManager::GetSoundBuffer("sound/audiomenu5.wav"));
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Up) { sound_next.play(); mymenu.MoveUp();
				break; }
				if (event.key.code == sf::Keyboard::Down) { sound_next.play(); mymenu.MoveDown(); break; }
                if (event.key.code == sf::Keyboard::Return)
                {
					enter.play();
					while (enter.getStatus() == sf::Sound::Playing) {
						sf::sleep(sf::microseconds(100));
					}
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:  window.close(); return; break;
              
					case 1: exit(0); break;

					case 2: exit(0); break;
                    default:break;
                    }
                } break;
            default:break;
            }
        }
        

        window.clear();
        window.draw(background);
        window.draw(Titul);
		person.draw(window);
        mymenu.draw();
        window.display();
    }

}

void Engine::GamePlay()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"BodyBuilder",sf::Style::Fullscreen);
	window.requestFocus();
	window.setActive(true);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);

	sf::RectangleShape background(sf::Vector2f(width, heght));
	background.setTexture(&AssetManager::GetTexture("image/background2.png"));
	bool is_scene_1 = true;

	sf::RectangleShape background2(sf::Vector2f(width, heght));
	background2.setTexture(&AssetManager::GetTexture("image/background.png"));

	// масштабы
	person.set_scale(2, 2);
	float scaleY = heght / 512;
	float scaleX = width / 512;

	// коллизии
	Collision home(0, 0, 192 * scaleX, 183 * scaleY);
	Collision gym((512 - 32) * scaleX, 0, 32 * scaleX, 183 * scaleY);
	Collision olimpia(0, 0, 512 * scaleX , 150 * scaleY);
	Collision underground(449 * scaleX, 225 * scaleY, 63 * scaleX,35*scaleY);

	//колизия дверей
	Collision door_home(95 * scaleX, 166 * scaleY, 33 * scaleX, scaleY * 55);
	Collision door_gym(480 * scaleX,145 * scaleY,30 * scaleX,22 * scaleY);
	Collision near_door_gym(475 * scaleX, 145 * scaleY, 15 * scaleX, 22 * scaleY);	
	Collision door_work(480 * scaleX, 32 * scaleY, 30 * scaleX, 27 * scaleY);
	Collision near_door_work(475 * scaleX, 32 * scaleY, 15 * scaleX, 27 * scaleY);
	
	//векторы колизий дверей
	std::vector<Collision> collisions{ door_home,door_gym,door_work };
	std::vector<Collision> near_collisions{ door_home,near_door_gym,near_door_work };

	//вспомогательная фигня
	sf::Vector2f position = person.get_position();
	float time;
	sf::Clock clock, clockAnimPlay;
	const float parametr = 0.5;
	int traffic = 0; // вид анимации
	sf::Vector2f moveRec;// запись о том где у нас сейчас персонаж
	

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		if (is_scene_1) {
			if (!(home.collision(person) || gym.collision(person))) {
				position = person.get_position();
			}
		}
		else
		{
			if (!(olimpia.collision(person) || underground.collision(person)))
			{
				position = person.get_position();
			}
		}
		

		sf::Event event;
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
				if (door_home.collision(person) && event.key.code == sf::Keyboard::E)
				{
					HomePlay(window, AssetManager::GetTexture("image/background2.png"));
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
		
		if (is_scene_1 && position.y <= 5)
		{
			is_scene_1 = false;
			person.set_position(position.x, heght - 110);
		}
		else if (!is_scene_1 && position.y >= heght - 105)
		{
			is_scene_1 = true;
			person.set_position(position.x, 5);
		}
		// background 1
		if (is_scene_1)
		{
			if ((home.collision(person) || gym.collision(person))) { person.set_position(position.x, position.y); }

			for (int i = 0; i < collisions.size(); i++) {
				if (near_collisions[i].collision(person)) { collisions[i].change_color(sf::Color::Yellow); }
				else { collisions[i].change_color(sf::Color(0, 0, 0, 0)); }
			}


			person.move(moveRec, width, heght);

			window.clear();
			window.draw(background);

			for (int i = 0; i < collisions.size(); i++) {
				window.draw(collisions[i].get_rect());
			}


			person.draw(window);
			person.draw_interface(window, scaleX, scaleY);
			window.display();
		}
		
		//background 2
		else
		{
			person.move(moveRec, width, heght);
			if (olimpia.collision(person) || underground.collision(person)) 
			{ 
				person.set_position(position.x, position.y); 
			}

			

			window.clear();
			window.draw(background2);

			person.draw(window);
			person.draw_interface(window, scaleX, scaleY);
			window.display();
		}
	}

}

void Engine::HomePlay(sf::RenderWindow& window, sf::Texture& background_t)
{
	sf::RectangleShape background(sf::Vector2f(width, heght));
	background.setTexture(&AssetManager::GetTexture("image/home.png"));
	float time;
	sf::Clock clock, clockAnimPlay;
	
	const float parametr = 0.5;
	int traffic = 0; // вид анимации
	sf::Vector2f moveRec;// запись о том где у нас сейчас персонаж
	
	float scaleX = width / 512;
	float scaleY = heght / 512;


	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		sf::Event event;
		
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
		person.move(moveRec, width, heght);


		window.clear();
		window.draw(background);
		person.draw(window);
		person.draw_interface(window, scaleX, scaleY);
		window.display();
	}
}




void Engine::input()
{
	/*
	sf::Event event_play;
	while (window->pollEvent(event_play))
	{
		if (event_play.key.code == sf::Keyboard::Escape) { window->close(); }
	}*/
}

void Engine::update(sf::Time const& deltaTime)
{
}

void Engine::draw()
{
	
}

Engine::Engine()
{
	

}

void Engine::run()
{
	GameMenu();
	GamePlay();
	sf::Clock clock;
	
	
	/*while (window->isOpen())
	{
		sf::Time dt = clock.restart();

		input();

		update(dt);

		draw();
	}*/
}



