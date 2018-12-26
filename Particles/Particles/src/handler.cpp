#include "handler.h"

Handler::Handler()
{
	m_bClicked = false;
	m_bGravity = false;
	m_bInteraction = false;
	m_bBounds = false;
	m_viewSize = sf::Vector2f(800, 800);

	//We go through and set up each number
	for (int i = 0; i < g_uiPartNum; i++)
	{
		m_parti[i].setPosition(sf::Vector2f(50 + rand() % ((int)m_viewSize.x - 100), 50 + rand() % ((int)m_viewSize.y - 100)));
		m_parti[i].setMass(2);
		m_parti[i].setColor(sf::Color(rand() % 20, rand() % 20,  rand() % 55, 255));
		m_parti[i].setBounds(m_viewSize, 50);
	}

	buttons[0].setup(sf::IntRect(100, 10, 75, 35), "Bounds");
	buttons[1].setup(sf::IntRect(200, 10, 75, 35), "Gravity");
	buttons[2].setup(sf::IntRect(300, 10, 75, 35), "Swarm");
	buttons[3].setup(sf::IntRect(400, 10, 75, 35), "Reset");

}

void Handler::simpleUpdate(float clockTime)
{
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
	for (int i = 0; i < g_uiPartNum; i++)
	{
		target.draw(m_parti[i], states);
	}
	for (int i = 0; i < 4; i++)
	{
		target.draw(buttons[i], states);
	}
}

void Handler::reset()
{
	for (int i = 0; i < g_uiPartNum; i++)
	{
		m_parti[i].freeze();
		m_parti[i].setPosition(sf::Vector2f(50 + rand() % ((int)m_viewSize.x -100), 50 + rand() % ((int)m_viewSize.y - 100)));
		m_parti[i].setMass(1);
		m_parti[i].setBounds(m_viewSize, 50);
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
		m_parti[i].setBounds(m_viewSize, 50);
	}
}