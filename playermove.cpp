#include "playermove.h"

void PlayerMove(sf::Sprite& ship, sf::Vector2f& moveRec,float max_x, float max_y)
{
    ship.move(moveRec);
    sf::Vector2f pos = ship.getPosition();
    if (pos.x > (max_x - 60)) ship.setPosition((max_x - 60), pos.y);
    if (pos.x < 50) ship.setPosition(50, pos.y);
    if (pos.y > (max_y - 113)) ship.setPosition(pos.x, (max_y - 113));
    if (pos.y < 110) ship.setPosition(pos.x, 110);

    if (pos.x > (max_x - 60) && pos.y > (max_y - 113)) ship.setPosition((max_x - 60), (max_y - 113));
    if (pos.x > (max_x - 60) && pos.y < 110) ship.setPosition((max_x - 60), 110);
    if (pos.x < 50 && pos.y >(max_y - 113)) ship.setPosition(50, (max_y - 113));
    if (pos.x < 50 && pos.y < 110) ship.setPosition(50, 110);

}

void playerAnim(sf::Sprite& ship, FrameAnime& FramePlanim, int traffic)
{
    FramePlanim.Frame += FramePlanim.Step;
    ship.setTextureRect(sf::IntRect(0, FramePlanim.Frame, 90, 90));
    if (traffic) if (FramePlanim.Frame > 0) FramePlanim.Step = -100;  else FramePlanim.Step = 0;
    else {
        if (FramePlanim.Frame == 800) FramePlanim.Step = 0;
        if (FramePlanim.Frame <= 700) FramePlanim.Step = 100;
    }
}

void Correct(Full& canister, int i, Meteor* meteor, int nmeteor)
{
    for (int i1 = 0; i1 < nmeteor; i1++)
    {
        if (i1 != i) {
            if (meteor[i1].collision(meteor[i].get_meteor_bounds()))
            {
                meteor[i].restart();  Correct(canister, i, meteor, nmeteor); break;
            }
        }
    }

    if (canister.collision(meteor[i].get_meteor_bounds())) { meteor[i].restart(); Correct(canister, i, meteor, nmeteor); }
}

void CorrectFull(Full& canister, Meteor* meteor, int nmeteor)
{
    for (int i1 = 0; i1 < nmeteor; i1++)
    {
        if (meteor[i1].collision(canister.get_meteor_bounds()))
        {
            canister.restart(); CorrectFull(canister, meteor, nmeteor); break;
        }
    }
}

std::string IntToStr(int number)
{
    std::ostringstream TextString;
    TextString << number;		
    return TextString.str();
}
