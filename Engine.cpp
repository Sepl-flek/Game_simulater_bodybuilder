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

	//������ ���
	sf::RectangleShape background(sf::Vector2f(width, heght));
	person.set_scale(5,5);
	person.set_position(1250, 700);

	background.setTexture(&AssetManager::GetTexture("image/menu.jpg"));

	sf::Text Titul;
	Titul.setFont(AssetManager::GetFont("font/mainmenu.otf"));

    
    setTextStyle(Titul, 770, 50, 120, sf::Color(235, 78, 78), "Bodybuilder Club");// ��������� �������� ������

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

	// ��������
	person.set_scale(2, 2);
	float scaleY = heght / 512;
	float scaleX = width / 512;

	// ��������
	Collision home(0, 0, 192 * scaleX, 183 * scaleY);
	Collision gym((512 - 32) * scaleX, 0, 32 * scaleX, 183 * scaleY);
	Collision olimpia(0, 0, 512 * scaleX , 150 * scaleY);
	Collision underground(449 * scaleX, 225 * scaleY, 63 * scaleX,35*scaleY);
	Collision home_scene_2(0, 510 * scaleY, scaleX * 191, 3 * scaleY);
	Collision gym_scene_2(480 * scaleX, 510 * scaleY, 32 * scaleX, 3 * scaleY);
	//������� ������
	Collision door_home(95 * scaleX, 166 * scaleY, 33 * scaleX, scaleY * 55);
	Collision door_gym(480 * scaleX,145 * scaleY,30 * scaleX,22 * scaleY);
	Collision near_door_gym(475 * scaleX, 145 * scaleY, 15 * scaleX, 22 * scaleY);	
	Collision door_work(480 * scaleX, 32 * scaleY, 30 * scaleX, 27 * scaleY);
	Collision near_door_work(475 * scaleX, 32 * scaleY, 15 * scaleX, 27 * scaleY);
	
	//������� ������� ������
	std::vector<Collision> collisions{ door_home,door_gym,door_work };
	std::vector<Collision> near_collisions{ door_home,near_door_gym,near_door_work };

	//��������������� �����
	sf::Vector2f position = person.get_position();
	float time;
	sf::Clock clock, clockAnimPlay;
	const float parametr = 2;
	int traffic = 0; // ��� ��������
	sf::Vector2f moveRec;// ������ � ��� ��� � ��� ������ ��������
	

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
			if (!(olimpia.collision(person) || underground.collision(person) || home_scene_2.collision(person) || gym_scene_2.collision(person)))
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
			case sf::Event::KeyPressed: // ������ ������
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
					HomePlay(window);
					
				}
				break;
				


			case sf::Event::KeyReleased: //������ �������� 
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
			if (olimpia.collision(person) || underground.collision(person) || home_scene_2.collision(person) || gym_scene_2.collision(person)) 
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

void Engine::HomePlay(sf::RenderWindow& window)
{
	
	sf::RectangleShape background(sf::Vector2f(width, heght));
	background.setTexture(&AssetManager::GetTexture("image/black.png"));
	window.clear();
	window.draw(background);
	window.display();
	sf::sleep(sf::seconds(0.5));
	background.setTexture(&AssetManager::GetTexture("image/home.png"));
	float time;
	sf::Clock clock, clockAnimPlay;
	
	person.set_scale(3, 3);

	std::vector<Food> foods;

	
	const float parametr = 2;
	int traffic = 0; // ��� ��������
	sf::Vector2f moveRec;// ������ � ��� ��� � ��� ������ ��������
	
	float scaleX = width / 512;
	float scaleY = heght / 512;
	person.set_position(32*scaleX, 223 *scaleY);
	Collision wall(0, 0, 23 * scaleX, heght);
	Collision piano(41 * scaleX, 2, 96 * scaleX, 48 * scaleY);
	Collision fridge(444 * scaleX, 0, 44 * scaleX, 22 * scaleY);
	Collision bed(41 * scaleX, 443 * scaleY, 95 * scaleX, 66 * scaleY);
	Collision table(230 * scaleX, 10 * scaleY, 97 * scaleX, 57 * scaleY);
	Collision arcade(463 * scaleX, 187 * scaleY, 49 * scaleX, 27 * scaleY);
	Collision wardrobe(445 * scaleX, 427 * scaleY, 65 * scaleX, 81 * scaleY);
	Collision near_bed(40 * scaleX, 422 * scaleY, 121 *scaleX, 88 *scaleY);
	Collision full_fridge(445 * scaleX, 2, 45 * scaleX, 57 * scaleY);

	Collision door(0, 240 * scaleY, 23 * scaleX, 22 * scaleY);
	Collision near_door(23 * scaleX, 240 * scaleY, 29 * scaleX, 26 * scaleY);
	sf::Vector2f position = person.get_position();;

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		sf::Event event;

		if(!(wall.collision(person) && piano.collision(person) 
			&& fridge.collision(person) && bed.collision(person) 
			&& table.collision(person) && arcade.collision(person) && wardrobe.collision(person))){ position = person.get_position(); }
		
		while (window.pollEvent(event))
		{

			if (event.key.code == sf::Keyboard::Escape) { window.close(); }


			switch (event.type)
			{
			case sf::Event::KeyPressed: // ������ ������
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
				if ((near_door.collision(person) && (event.key.code == sf::Keyboard::E))) 
				{
					background.setTexture(&AssetManager::GetTexture("image/black.png"));
					window.clear();
					window.draw(background);
					window.display();
					sf::sleep(sf::seconds(0.5));
					background.setTexture(&AssetManager::GetTexture("image/background2.png"));
					person.set_position(99 * scaleX, 185 * scaleY);
					person.set_scale(2, 2);
			
					return;
				}
				
				break;



			case sf::Event::KeyReleased: //������ �������� 
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

		if (near_door.collision(person))
		{
			door.change_color(sf::Color::Yellow);
		}
		else
		{
			door.change_color(sf::Color(0, 0, 0, 0));
		}

		person.move(moveRec, width, heght);
		// �������� 
		if (wall.collision(person) || piano.collision(person) 
			|| fridge.collision(person) || bed.collision(person) 
			|| table.collision(person) || arcade.collision(person) || wardrobe.collision(person))
		{
			person.set_position(position.x, position.y);
		}

		if (near_bed.collision(person)) { bed.change_color(sf::Color::Yellow); }
		else { bed.change_color(sf::Color(0, 0, 0, 0)); }

		if (full_fridge.collision(person)) { full_fridge.change_color(sf::Color::Yellow); }
		else { full_fridge.change_color(sf::Color(0, 0, 0, 0)); }


		window.clear();
		window.draw(background);
		window.draw(door.get_rect());
		window.draw(full_fridge.get_rect());
		window.draw(bed.get_rect());
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