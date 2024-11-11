#include "Workgame.h"

void workgame(sf::RenderWindow& window,Person &person)
{

        srand(time(NULL));
        float width = sf::VideoMode::getDesktopMode().width;
        float height = sf::VideoMode::getDesktopMode().height;

        float scaleX = width / 1280;
        float scaleY = height / 720;
        // �������������� ������
        sf::Texture textureInfoPanel;
        textureInfoPanel.loadFromFile("pictures/Panel.png");
        sf::RectangleShape gameInfoPanel(sf::Vector2f(width, 113));
        gameInfoPanel.setTexture(&textureInfoPanel);
        gameInfoPanel.setPosition(sf::Vector2f(0, 0));

        // ���������
        sf::Texture textureSpace;
        textureSpace.loadFromFile("pictures/newkos1.jpg");

        sf::RectangleShape gameSpace(sf::Vector2f(width, height));
        gameSpace.setTexture(&textureSpace);

        sf::RectangleShape gameSpace2(sf::Vector2f(width, height));
        gameSpace2.setTexture(&textureSpace);
        gameSpace2.setPosition(sf::Vector2f(width, 0));


        bool mus = false; 
        sf::Music game_music;
        if (!game_music.openFromFile("sound/mgame.ogg")) return ;   
        game_music.setLoop(true);
        
        sf::Sound falsound, soundbonM, soundbonB, soundvic;
        sf::SoundBuffer fal, bufM, bufB, vic;
        fal.loadFromFile("sound/faled1.wav");
        falsound.setBuffer(fal);
        bufM.loadFromFile("sound/bonusm.wav"); 
        soundbonM.setBuffer(bufM);
        bufB.loadFromFile("sound/bonusB.wav"); 
        soundbonB.setBuffer(bufB);
        vic.loadFromFile("sound/victoria.wav"); 
        soundvic.setBuffer(vic);

        //топливо

        int pusk = 0;
        double tmpfull = 0;
        int full = 1000;
        sf::Text text_full, plusfull, text_pause, end_game;

        text_full.setFont(AssetManager::GetFont("font/mainmenu.otf"));
        text_full.setFillColor(sf::Color::Green);
        text_full.setCharacterSize(30 * scaleX);
        text_full.setPosition(1070 * scaleX, 0 * scaleY);

        plusfull.setFont(AssetManager::GetFont("font/mainmenu.otf"));
        plusfull.setFillColor(sf::Color::Green);
        plusfull.setCharacterSize(25);

        end_game.setFont(AssetManager::GetFont("font/mainmenu.otf"));
        end_game.setFillColor(sf::Color::Red);
        end_game.setCharacterSize(100);
        end_game.setString(L"КОНЕЦ ИГРЫ");
        end_game.setPosition(300 * scaleX, 333 * scaleY);

        bool game_over = false;
        sf::Vector2f pos;
        sf::Clock clock, clockAnimPlay, clockMeteor, clockAnimText;
        float time, timeShip, timeBackground, timeMete;
        //.........................................

        // ����������� �������
        sf::Vector2f moveRec; // ������������ ������
        int traffic = 0;
        sf::Texture textureShip;

        FrameAnime FramePlanim;
        FramePlanim.Frame = 700;
        textureShip.loadFromFile("pictures/playeranim1.png");

        sf::Sprite ship;
        ship.setTexture(textureShip);
        ship.setTextureRect(sf::IntRect(0, FramePlanim.Frame, 90, 90));
        ship.scale(1, 1);
        ship.setPosition(sf::Vector2f(80, 380));
        //.........................................


        // ����� ������������ �������
        sf::RectangleShape Earth(sf::Vector2f(500 * scaleX, scaleY * 500));
        Earth.setTexture(&AssetManager::GetTexture("image/earth.png"));
        Earth.setPosition(1100 * scaleX, 150 * scaleY);


        FrameAnime distruction_anim;
        distruction_anim.Frame = 5;
        distruction_anim.Frame1 = 15;
        sf::Texture text_deest;
        text_deest.loadFromFile("pictures/bum.png");
        sf::Sprite destruction;
        destruction.setTexture(text_deest);
        destruction.setTextureRect(sf::IntRect(5, 15, 95, 80));
        destruction.scale(1, 1);
        sf::CircleShape Rcircle(5 * scaleX);
        Rcircle.setFillColor(sf::Color::Red);
        Rcircle.setOutlineThickness(2.f);
        Rcircle.setOutlineColor(sf::Color(255, 150, 0));
        Rcircle.setPosition(495 * scaleX, 33);

        //���������
        Meteor meteors[20];

        int nmeteor = 20;
       
        Full canister("image/galon.png", 1000, 1000);


        const float speed = 0.6;

        while (window.isOpen())
        {
            sf::Event event;
            // time
            time = clock.getElapsedTime().asMicroseconds();
            time /= 6000;
            timeShip = time * 3;
            timeBackground = time;
            timeMete = time * 2;
            //.........................................

            clock.restart();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                // ���������� ��������
                switch (event.type)
                {
                case sf::Event::KeyPressed:

                    if (event.key.code == sf::Keyboard::M)
                    {
                        mus = !mus; if (mus) game_music.play(); else game_music.stop();
                    }

                    if ((event.key.code == sf::Keyboard::S)) {
                        if (full != 0) {
                            moveRec.y = speed * timeShip;
                            traffic = 2;
                            full--;
                        }
                    }
                    if ((event.key.code == sf::Keyboard::W)) {
                        if (full != 0)
                        {
                            moveRec.y = -speed * timeShip;
                            traffic = 1;
                            full--;
                        }
                    }
                    if ((event.key.code == sf::Keyboard::A)) {
                        if (full != 0)
                        {
                            moveRec.x = -speed * timeShip;
                            full--;
                        }

                    }
                    if ((event.key.code == sf::Keyboard::D)) {
                        if (full != 0)
                        {
                            moveRec.x = speed * timeShip;
                            full--;
                        }
                    }
                    break;

                case sf::Event::KeyReleased:
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
                    }
                    if ((event.key.code == sf::Keyboard::D)) {
                        moveRec.x = 0;
                    }
                    break;

                default:
                    break;
                }

            }

            if (Rcircle.getPosition().x <= (850 * scaleX))
            {
                if (game_over) {
                    if (clockMeteor.getElapsedTime() > sf::milliseconds(80)) {

                        clockMeteor.restart();
                        distruction_anim.Frame += distruction_anim.Step;
                        if (distruction_anim.Frame > 405) {
                            distruction_anim.Frame1 += distruction_anim.Step1;
                            distruction_anim.Frame = 5;
                        }
                        if (distruction_anim.Frame1 > 415) {
                            person.update_money(-(100 + rand() % 30));
                            person.update_sleep(20 + rand() % 30);
                            return;
                            game_over = false;
                            ship.setPosition(sf::Vector2f(80, 380));
                            for (int i = 0; i < nmeteor; ++i) {
                                meteors[i].restart();

                            }
                            canister.restart();
                            distruction_anim.Frame = 5;
                            distruction_anim.Frame1 = 15;
                            full = 1000;
                        }
                        else {
                            destruction.setTextureRect(sf::IntRect(distruction_anim.Frame, distruction_anim.Frame1, 95, 80));
                        }
                    }
                }

                else {



                    if (clockAnimPlay.getElapsedTime() > sf::milliseconds(100)) {
                        clockAnimPlay.restart();

                        playerAnim(ship, FramePlanim, traffic);

                    }

                    if (clockMeteor.getElapsedTime() > sf::milliseconds(80)) {
                        clockMeteor.restart();
                        for (int i = 0; i < nmeteor; ++i) {
                            meteors[i].animation();

                        }
                        Rcircle.move(1, 0);

                    }

                    if (clockAnimText.getElapsedTime() > sf::milliseconds(80)) {
                        clockAnimText.restart();
                        if (pusk > 0)
                        {
                            pusk--;
                            plusfull.move(0, -1);
                        }


                    }



                    // ���������� �������
                    gameSpace.move(-0.2 * timeBackground, 0);
                    pos = gameSpace.getPosition();
                    if (pos.x < -width) {
                        gameSpace.setPosition(width, pos.y);
                    }

                    gameSpace2.move(-0.2 * timeBackground, 0);
                    pos = gameSpace2.getPosition();
                    if (pos.x < -width) {
                        gameSpace2.setPosition(width, pos.y);
                    }
                    //...........................................

                    //�������� �������
                    PlayerMove(ship, moveRec, width, height);

                    for (int i = 0; i < nmeteor; ++i) {
                        if (meteors[i].new_born) Correct(canister, i, meteors, nmeteor);

                        meteors[i].move(timeMete);

                        if (meteors[i].collision(ship.getGlobalBounds())) {
                            falsound.play();
                            game_over = true;
                            destruction.setPosition(ship.getPosition().x, ship.getPosition().y);
                            break;
                        }

                    }
                    if (canister.new_born) CorrectFull(canister, meteors, nmeteor);
                    canister.move(timeMete);
                    if (canister.collision(ship.getGlobalBounds()))
                    {
                        if (tmpfull > 1000)
                        {
                            soundbonB.play();

                        }
                        else
                        {
                            soundbonM.play();
                        }
                        tmpfull = 100 + rand() % 900;
                        full += tmpfull;
                        plusfull.setString(IntToStr(tmpfull));
                        plusfull.setPosition(canister.getPosBonus().x, canister.getPosBonus().y);
                        pusk = 20;
                        canister.restart();
                    }

                    if (full >= 1000) text_full.setFillColor(sf::Color::Green);
                    else if (full >= 500) text_full.setFillColor(sf::Color::Yellow);
                    else text_full.setFillColor(sf::Color::Red);

                    text_full.setString(IntToStr(full));
                }


                window.clear();
                window.draw(gameSpace);
                window.draw(gameSpace2);
                window.draw(gameInfoPanel);
                window.draw(Rcircle);

                if (game_over) {
                    window.draw(destruction);
                }
                else {
                    window.draw(ship);
                }
                for (int i = 0; i < nmeteor; ++i) {
                    meteors[i].draw(window);
                }
                canister.draw(window);
                window.draw(text_full);
                if (pusk > 0) window.draw(plusfull);
                window.display();
                if (Rcircle.getPosition().x > (850 * scaleX)) { game_music.stop(); soundvic.play(); }

            }
            else
            {

                window.clear();               
                
                window.draw(gameSpace2);
                window.draw(gameSpace);
                
                window.draw(gameInfoPanel);  
                window.draw(Rcircle);
                window.draw(text_full);
                window.draw(Earth);
                window.draw(end_game);
                window.display();            
                if (clockAnimText.getElapsedTime() > sf::seconds(3))
                {
                    person.update_money(-(200 + rand() % 50));
                    person.update_sleep(10 + rand() % 10);
                    return;
                }
                    
            }
        }

       
}
