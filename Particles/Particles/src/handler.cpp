#include "handler.h"

Handler::Handler(sf::Vector2f window)
{
	//Firstly we ensure the viewsize is correct
	m_viewSize = window;

	//We set the variables that determine the particles
	m_fMass = 1;
	m_fBorder = 50;
	m_baseColor = sf::Color(0, 0, 200, 255);
	m_variationColor = sf::Color(20, 200, 55, 1);

	//We go through and set up each number
	reset();

	//We set the logic states for the buttons
	m_bClicked = false;
	m_bGravity = false;
	m_bInteraction = false;
	m_bBounds = false;

	//Finally we set up the buttons so they all work correctly
	buttons[0].setup(sf::IntRect(100, 10, 75, 35), "Bounds");
	buttons[1].setup(sf::IntRect(200, 10, 75, 35), "Gravity");
	buttons[2].setup(sf::IntRect(300, 10, 75, 35), "Swarm");
	buttons[3].setup(sf::IntRect(400, 10, 75, 35), "Reset");

}

void Handler::simpleUpdate(float clockTime)
{
	//Does a simple update to move the particle positions
	float elapsedTime = clockTime - m_fLastTime;
	for (int i = 0; i < g_uiPartNum; i++)
	{
		m_parti[i].update(elapsedTime);
		if (m_bBounds) m_parti[i].checkBounds();
	}
	m_fLastTime = clockTime;
}

void Handler::complexUpdate(sf::Vector2i pos)
{
	//Does a complex update which figures out the new physics positions
	avg = sf::Vector2i(0, 0);
	for (int i = 0; i < g_uiPartNum; i++)
	{
		//First we do the simple changes due to gravity and click force
		if (m_bClicked) m_parti[i].addForceDirection(pos, 100);
		if (m_bGravity) m_parti[i].addForce(sf::Vector2f(0, 75));

		//Then we have the more complex steps if interaction is enabled
		if (m_bInteraction && i > 3)
		{
			//making individual particles follow each other for more fuzziness
			m_parti[i].addForceDirection(sf::Vector2i(m_parti[i - 1].getPosition().x, m_parti[i - 1].getPosition().y), 10);
			m_parti[i].addForceDirection(sf::Vector2i(m_parti[i - 2].getPosition().x, m_parti[i - 2].getPosition().y), 10);
			m_parti[i].addForceDirection(sf::Vector2i(m_parti[i - 3].getPosition().x, m_parti[i - 3].getPosition().y), 10);
		}
		//this avg is for storing the average position
		avg.x += m_parti[i].getPosition().x;
		avg.y += m_parti[i].getPosition().y;
	}

	avg.x /= g_uiPartNum;
	avg.y /= g_uiPartNum;

	//then if interaction is enabled we send the particles towards the average position (centre of the swarm)
	if (m_bInteraction)
	{
		for (int i = 0; i < g_uiPartNum; i++)
		{
			m_parti[i].addForceDirection(avg, 20);
		}
		avg = sf::Vector2i(0, 0);
	}
}

void Handler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//First we draw all the particles
	for (int i = 0; i < g_uiPartNum; i++)
	{
		target.draw(m_parti[i], states);
	}
	//Then we draw all the buttons
	for (int i = 0; i < 4; i++)
	{
		target.draw(buttons[i], states);
	}
}

void Handler::reset()
{
	//First we create any temporary variables
	sf::Vector2f position;
	sf::Color tempColor;


	for (int i = 0; i < g_uiPartNum; i++)
	{
		//First we freeze stop the particle from moving
		m_parti[i].freeze();

		//Next we set up the position as a random place on the screen within the border.
		position.x = m_fBorder + rand() % ((int)(m_viewSize.x - (2 * m_fBorder)));
		position.y = m_fBorder + rand() % ((int)(m_viewSize.y - (2 * m_fBorder)));
		m_parti[i].setPosition(position);

		//Then we set the mass to whatever assigned value it should be
		m_parti[i].setMass(m_fMass);

		//Then we set the color to it's value
		tempColor.r = m_baseColor.r + rand() % m_variationColor.r;
		tempColor.g = m_baseColor.g + rand() % m_variationColor.g;
		tempColor.b = m_baseColor.b + rand() % m_variationColor.b;
		tempColor.a = m_baseColor.a + rand() % m_variationColor.a;
		m_parti[i].setColor(tempColor);

		//Then we give it the correct border size;
		m_parti[i].setBounds(m_viewSize, m_fBorder);
	}
}

void Handler::click(sf::Vector2i pos, bool down)
{
	//first we divide up presses and down presses
	if (down)
	{
		//we check if any of the buttons have been pressed
		if (buttons[0].click(pos))
		{
			if (m_bBounds) m_bBounds = false;
			else           m_bBounds = true;
		}
		else if (buttons[1].click(pos))
		{
			if (m_bGravity) m_bGravity = false;
			else            m_bGravity = true;
		}
		else if (buttons[2].click(pos))
		{
			if (m_bInteraction) m_bInteraction = false;
			else                m_bInteraction = true;
		}
		else if (buttons[3].click(pos))
		{
			buttons[3].click(pos); //to reset the color back to default
			reset();
		}
		//if none of the buttons have been pressed we just send the particles to the mouse via attraction
		else m_bClicked = true;
	}
	else m_bClicked = false;
}

void Handler::passFont(sf::Font& font)
{
	for (int i = 0; i < 4; i++)
	{
		buttons[i].passFont(font);
	}
}

void Handler::setSize(sf::Vector2f size)
{
	m_viewSize = size;
	for (int i = 0; i < g_uiPartNum; i++)
	{
		m_parti[i].setBounds(m_viewSize, m_fBorder);
	}
}

void Handler::setBorder(float border)
{
	m_fBorder = border;
	for (int i = 0; i < g_uiPartNum; i++)
	{
		m_parti[i].setBounds(m_viewSize, m_fBorder);
	}
}

void Handler::setColors(sf::Color base, sf::Color variation)
{
	m_baseColor = base;
	m_variationColor = variation;
	sf::Color tempColor;

	for (int i = 0; i < g_uiPartNum; i++)
	{
		tempColor.r = m_baseColor.r + rand() % m_variationColor.r;
		tempColor.g = m_baseColor.g + rand() % m_variationColor.g;
		tempColor.b = m_baseColor.b + rand() % m_variationColor.b;
		tempColor.a = m_baseColor.a + rand() % m_variationColor.a;
		m_parti[i].setColor(tempColor);
	}

}