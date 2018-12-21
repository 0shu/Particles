#include "tickHealth.h"
#include <iostream>

TickHealth::TickHealth()
{
    fLatestTickLength = 0.0;
    fHighestTickLength = 0.0;
    iLatestSecondCount = 0;
	fLatestSecond = 0;

    fCurrentTPS = 0.0;
    fCurrent1MSPT = 0.0; //The MSPT(Milliseconds per Tick) for the last second
    fCurrent3MSPT = 0.0; //The MSPT for the last 3 seconds
    fCurrent5MSPT = 0.0; //The MSPT for the last 5 seconds
    fCurrent10MSPT = 0.0;//The MSPT for the last 10 seconds

    for (int i = 0; i < 10; i++)
    {
        fTenMSPT[i] = 0.0;
    }
    //SETUP TEXT OPTIONS HERE

    TPStext.setString("TPS:");
    TPStext.setCharacterSize(10);
    TPStext.setFillColor(sf::Color(100, 255, 90, 200));
    TPStext.setPosition(10, 10);
    //TPStext.setStyle(sf::Text::Bold);

    TPSnum.setCharacterSize(10);
    TPSnum.setFillColor(sf::Color(100, 255, 90, 200));
    TPSnum.setPosition(35, 10);
    //TPSnum.setStyle(sf::Text::Bold);

    MSPTtext.setString("MSPT:");
    MSPTtext.setCharacterSize(10);
    MSPTtext.setFillColor(sf::Color(100, 255, 90, 200));
    MSPTtext.setPosition(10, 20);
    //MSPTtext.setStyle(sf::Text::Bold);

    MSPTnum.setCharacterSize(10);
    MSPTnum.setFillColor(sf::Color(100, 255, 90, 200));
    MSPTnum.setPosition(40, 20);
    //MSPTnum.setStyle(sf::Text::Bold);

    Longtext.setString("Longest Tick:");
    Longtext.setCharacterSize(10);
    Longtext.setFillColor(sf::Color(100, 255, 90, 200));
    Longtext.setPosition(10, 30);
    //Longtext.setStyle(sf::Text::Bold);

    Longnum.setCharacterSize(10);
    Longnum.setFillColor(sf::Color(100, 255, 90, 200));
    Longnum.setPosition(77 , 30);
    //Longnum.setStyle(sf::Text::Bold);
}

void TickHealth::update(float clockTime)
{
    iLatestSecondCount++;
    fLatestTickLength = clockTime - fLastTime;

    //Checks if the latest tick was longer than the greatest length, if so makes it new greatest tick length.
    fHighestTickLength = (fHighestTickLength < fLatestTickLength && fTenMSPT[5] > 0.0) ? fLatestTickLength : fHighestTickLength; 

    fLatestSecond += fLatestTickLength; //adds the latest tick to the total for the last second
    if (fLatestSecond >= 250.0) //If 1000ms has passed then we know it's more than a second, values are recalculated every second
    {
        //This segment is for moving the previous values back a slot in the array
        for (int i = 9; i > 0; i--)
        {
            fTenMSPT[i] = fTenMSPT[i - 1];
        }
        fTenMSPT[0] = (fLatestSecond / (float)iLatestSecondCount);

        //reset the values so they can be counted again
        iLatestSecondCount = 0;
        fLatestSecond = 0;

        //Figuring out the MSPTs for certain timeframes by averaging values from the array
        fCurrent1MSPT = fTenMSPT[0];
        fCurrent3MSPT = (fTenMSPT[0] + fTenMSPT[1] + fTenMSPT[2]) / 3.0;
        fCurrent5MSPT = (fTenMSPT[0] + fTenMSPT[1] + fTenMSPT[2] + fTenMSPT[3] + fTenMSPT[4]) / 5.0;
        fCurrent10MSPT = (fTenMSPT[0] + fTenMSPT[1] + fTenMSPT[2] + fTenMSPT[3] + fTenMSPT[4] + fTenMSPT[5] + fTenMSPT[6] + fTenMSPT[7] + fTenMSPT[8] + fTenMSPT[9]) / 10.0;

        //Current TPS uses all the MSPT values so it's an average with more weight on the present but stick acknowledgement of previous values
        fCurrentTPS = 1000 / ((fCurrent1MSPT + fCurrent3MSPT + fCurrent5MSPT + fCurrent10MSPT) / 4); 

        //For displaying via "draw"
        TPSnum.setString(std::to_string(fCurrentTPS));
        MSPTnum.setString(std::to_string(fCurrent10MSPT));
        Longnum.setString(std::to_string((int)fHighestTickLength));
    }
	fLastTime = clockTime;
}

void TickHealth::passFont(sf::Font& font)
{
    TPStext.setFont(font); TPSnum.setFont(font);
    MSPTtext.setFont(font); MSPTnum.setFont(font);
    Longtext.setFont(font); Longnum.setFont(font);
}

void TickHealth::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text1, states);
    target.draw(TPStext, states);
    target.draw(TPSnum, states);
    target.draw(MSPTtext, states);
    target.draw(MSPTnum, states);
    target.draw(Longtext, states);
    target.draw(Longnum, states);
}