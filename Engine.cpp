#include "Engine.h"





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


	std::vector<sf::String> name_menu = { L"Play","Exit" };
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
	background.setTexture(&AssetManager::GetTexture("image/background5.png"));

	sf::RectangleShape background2(sf::Vector2f(width, heght));
	background2.setTexture(&AssetManager::GetTexture("image/background2.png"));
	background2.setPosition(0, -heght);

	person.set_scale(2, 2);
	float scaleY = heght / 512; 
	float scaleX = width / 512;
	Collision home(0, 0, 192 * scaleX, 183 * scaleY);
	Collision gym((512 - 32)*scaleX, 0, 32 * scaleX, 183 * scaleY);
	
	sf::Vector2f position = person.get_position();

	float time;
	sf::Clock clock, clockAnimPlay;
	const float parametr = 0.5;
	int traffic = 0; // вид анимации
	sf::Vector2f moveRec;// запись о том где у нас сейчас корабль
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 3000;
		clock.restart();
		if (!(home.collision(person) || gym.collision(person))) {
			position = person.get_position();
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
		

		if ((home.collision(person) || gym.collision(person)))
		{
			person.set_position(position.x, position.y);
		}

		
		person.move(moveRec, width, heght);
		window.clear();
		window.draw(background);
		person.draw(window);
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



