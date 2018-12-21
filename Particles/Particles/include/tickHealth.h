//A class for measuring the tick health of a given program
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <Windows.h>

class TickHealth : public sf::Drawable
{
private:
    float fLatestTickLength;
    float fHighestTickLength;
    float fLatestSecond;
    int iLatestSecondCount;
	float fLastTime = 0;
    float fTenMSPT[10];

    sf::Text text1;

    sf::Text TPStext;  sf::Text TPSnum;
    sf::Text MSPTtext; sf::Text MSPTnum;
    sf::Text Longtext; sf::Text Longnum;

    float fCurrentMSPT;
    float fCurrent1MSPT;
    float fCurrent3MSPT;
    float fCurrent5MSPT;
    float fCurrent10MSPT;

    float fCurrentTPS;

public:
    TickHealth();
    void passFont(sf::Font& font);
    void update(float clockTime); //Takes the elapsed time in ms (only use once per game cycle/tick)
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};