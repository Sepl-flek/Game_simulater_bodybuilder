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
	sf::RectangleShape background(sf::Vector2f(width, height));
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
	sf::Text text;
	text.setFont(AssetManager::GetFont("font/mainmenu.otf")); // ������������� �����
	text.setCharacterSize(50); // ������ ������
	text.setFillColor(sf::Color::White); // ���� ������
	sf::Text day;
	day.setFont(AssetManager::GetFont("font/mainmenu.otf")); // ������������� �����
	day.setCharacterSize(50); // ������ ������
	day.setFillColor(sf::Color::White); // ���� ������
	
	backgroundmusic.openFromFile("sound/Gameplay.wav");

	backgroundmusic.setVolume(20);
	backgroundmusic.setLoop(true);
	backgroundmusic.play();
	
	person.update_sleep(100);
	person.update_hunger(30);
	
	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/background2.png"));
	bool is_scene_1 = true;

	sf::RectangleShape background2(sf::Vector2f(width, height));
	background2.setTexture(&AssetManager::GetTexture("image/background.png"));

	// ��������
	person.set_scale(2, 2);
	float scaleY = height / 512;
	float scaleX = width / 512;
	text.setPosition(10 * scaleX, 10 * scaleY);
	day.setPosition(70 * scaleX, 10 * scaleY);
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
				if (near_door_gym.collision(person) && event.key.code == sf::Keyboard::E)
				{
					backgroundmusic.pause();
					GymPlay(person, window);
					backgroundmusic.play();
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
			person.set_position(position.x, height - 110);
		}
		else if (!is_scene_1 && position.y >= height - 105)
		{
			is_scene_1 = true;
			person.set_position(position.x, 5);
		}
		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));
		// background 1
		if (is_scene_1)
		{
			if ((home.collision(person) || gym.collision(person))) { person.set_position(position.x, position.y); }

			for (int i = 0; i < collisions.size(); i++) {
				if (near_collisions[i].collision(person)) { collisions[i].change_color(sf::Color::Yellow); }
				else { collisions[i].change_color(sf::Color(0, 0, 0, 0)); }
			}


			person.move(moveRec, width, height);

			window.clear();
			window.draw(background);

			for (int i = 0; i < collisions.size(); i++) {
				window.draw(collisions[i].get_rect());
			}


			person.draw(window);
			person.draw_interface(window, scaleX, scaleY);
			window.draw(text);
			window.draw(day);
			window.display();
		}
		
		//background 2
		else
		{
			person.move(moveRec, width, height);
			if (olimpia.collision(person) || underground.collision(person) || home_scene_2.collision(person) || gym_scene_2.collision(person)) 
			{ 
				person.set_position(position.x, position.y); 
			}

			

			window.clear();
			window.draw(background2);

			person.draw(window);
			person.draw_interface(window, scaleX, scaleY);
			window.draw(text);
			window.draw(day);
			window.display();
		}
	}

}

void Engine::HomePlay(sf::RenderWindow& window)
{
	
	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/black.png"));
	window.clear();
	window.draw(background);
	window.display();
	sf::sleep(sf::seconds(0.5));
	background.setTexture(&AssetManager::GetTexture("image/home.png"));
	float time;
	sf::Clock clock, clockAnimPlay;
	
	
	person.set_scale(3, 3);

	const float parametr = 2;
	int traffic = 0; // ��� ��������
	sf::Vector2f moveRec;// ������ � ��� ��� � ��� ������ ��������
	
	float scaleX = width / 512;
	float scaleY = height / 512;

	sf::Text text;
	text.setFont(AssetManager::GetFont("font/mainmenu.otf")); // ������������� �����
	text.setCharacterSize(50); // ������ ������
	text.setFillColor(sf::Color::White); // ���� ������
	text.setPosition(10 * scaleX, 10 * scaleY);

	sf::Text day;
	day.setFont(AssetManager::GetFont("font/mainmenu.otf")); // ������������� �����
	day.setCharacterSize(50); // ������ ������
	day.setFillColor(sf::Color::White);
	day.setPosition(70 * scaleX, 10 * scaleY);

	person.set_position(32*scaleX, 223 *scaleY);
	Collision wall(0, 0, 23 * scaleX, height);
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
	sf::Vector2f position = person.get_position();

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
				if (full_fridge.collision(person) && (event.key.code == sf::Keyboard::E))
				{
					if (person.get_hunger())
					{
						FridgePlay(window);
					}
				}
				if (near_bed.collision(person) && event.key.code == sf::Keyboard::E)
				{
					if (person.get_lvl_sleep())
					{
						sf::RectangleShape background2(sf::Vector2f(width, height));
						background2.setTexture(&AssetManager::GetTexture("image/home_sleep.png"));
						sf::Sound sleep;
						sleep.setBuffer(AssetManager::GetSoundBuffer("sound/night.wav"));
						sleep.play();
						window.clear();
						window.draw(background2);
						window.display();
						backgroundmusic.pause();
						
						sf::sleep(sf::seconds(person.get_lvl_sleep() / 10));
						sleep.stop();
						backgroundmusic.play();
						
						person.update_sleep(-101);
						person.update_day();

					}
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

		person.move(moveRec, width, height);
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
		text.setString("Money: " + std::to_string(person.get_money()));
		day.setString("Day: " + std::to_string(person.get_day()));

		window.clear();
		window.draw(background);
		window.draw(door.get_rect());
		window.draw(full_fridge.get_rect());
		window.draw(bed.get_rect());
		person.draw(window);
		window.draw(text);
		window.draw(day);
		person.draw_interface(window, scaleX, scaleY);
		window.display();
	}
}

void Engine::FridgePlay(sf::RenderWindow& window)
{
	float scaleX = width / 512;
	float scaleY = height / 512;
	Food burger(84, 128, sf::Vector2f(102 * scaleX,132 * scaleY), "image/foods.png", 20, scaleY,scaleY,30);
	Food chiken(200, 125, sf::Vector2f(216 * scaleX,133 * scaleY), "image/foods.png", 20, scaleY, scaleY,25);
	Food chees(310, 126, sf::Vector2f(347 * scaleX,132 * scaleY), "image/foods.png", 20, scaleY, scaleY,15);
	Food fish(84, 230, sf::Vector2f(102 * scaleX,262 * scaleY), "image/foods.png", 20, scaleY, scaleY,13);
	Food ogrizok(197, 231, sf::Vector2f(216 * scaleX,262 * scaleY), "image/foods.png", 20, scaleY, scaleY,7);
	Food wine(312, 230, sf::Vector2f(347* scaleX,262*scaleY), "image/foods.png", 20, scaleY, scaleY,1);
	std::vector<std::vector<Food>> foods = { {burger,chiken,chees},{fish,ogrizok,wine} };
	int h = foods.size(),w = foods[0].size();
	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setTexture(&AssetManager::GetTexture("image/fridge.png"));

	int heght = 0, wedth = 0;
	sf::Sound sound_next;
	sound_next.setBuffer(AssetManager::GetSoundBuffer("sound/audiomenu2.wav"));
	sf::Sound enter;
	enter.setBuffer(AssetManager::GetSoundBuffer("sound/eating.wav"));


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape) { return; }
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Up) {
					sound_next.play();
					heght--;
					if (heght < 0)
					{
						foods[0][wedth].change_color(sf::Color(0, 0, 0, 0));
						heght = h - 1;
						foods[heght][wedth].change_color(sf::Color::Yellow);
					}
					else
					{
						foods[heght + 1][wedth].change_color(sf::Color(0, 0, 0, 0));
						foods[heght][wedth].change_color(sf::Color::Yellow);
					}
					break;
				}
				if (event.key.code == sf::Keyboard::Down) { 
					sound_next.play();
					heght++;
					if (heght < h)
					{
						foods[heght - 1][wedth].change_color(sf::Color(0, 0, 0, 0));
						foods[heght][wedth].change_color(sf::Color::Yellow);
					}
					else
					{
						foods[heght - 1][wedth].change_color(sf::Color(0, 0, 0, 0));
						heght = 0;
						foods[heght][wedth].change_color(sf::Color::Yellow);
					}
					break; 
				}
				if (event.key.code == sf::Keyboard::Right) {
					sound_next.play();
					wedth++;
					if (wedth < w)
					{
						foods[heght][wedth - 1].change_color(sf::Color(0, 0, 0, 0));
						foods[heght][wedth].change_color(sf::Color::Yellow);
					}
					else
					{
						foods[heght][wedth - 1].change_color(sf::Color(0, 0, 0, 0));
						wedth = 0;
						foods[heght][wedth].change_color(sf::Color::Yellow);
					}
					break;
				}
				if (event.key.code == sf::Keyboard::Left) {
					sound_next.play();
					wedth--;
					if (wedth < 0)
					{
						foods[heght][0].change_color(sf::Color(0, 0, 0, 0));
						wedth = w - 1;
						foods[heght][wedth].change_color(sf::Color::Yellow);
					}
					else
					{
						foods[heght][wedth + 1].change_color(sf::Color(0, 0, 0, 0));
						foods[heght][wedth].change_color(sf::Color::Yellow);
						
					}
					break;
				}
				if (event.key.code == sf::Keyboard::Return)
				{
					person.update_hunger(-foods[heght][wedth].get_satiety());
					person.update_money(foods[heght][wedth].get_coast());
					
					enter.play();
					while (enter.getStatus() == sf::Sound::Playing) {
						sf::sleep(sf::microseconds(100));
					}

					return;
				} break;
			default:break;
			}
		}

		window.clear();
		window.draw(background);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				foods[i][j].draw(window);
			}
		}
		
		foods[0][0].draw(window);
		window.display();
	}
	

}

void Engine::input()
{
	
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