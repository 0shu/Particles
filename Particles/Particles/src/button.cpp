#include "button.h"

Button::Button()
{
	m_pressedColor = sf::Color(100, 255, 90, 200);
	m_offColor = sf::Color(150, 150, 150, 200);
	m_body.setFillColor(m_offColor);
}

void Button::setup(sf::IntRect rect, std::string string)
{
	m_body.setPosition(rect.left, rect.top);
	m_body.setSize(sf::Vector2f(rect.width, rect.height));
	m_text.setString(string);
	m_text.setCharacterSize(17);
	m_text.setStyle(sf::Text::Bold);
	m_text.setPosition(rect.left + 5, rect.top + 5);
}

bool Button::click(sf::Vector2i pos)
{
	std::cout << "click being tested" << std::endl;
	if (m_body.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))
	{
		if (state)
		{
			m_body.setFillColor(m_offColor);
			state = false;
		}
		else
		{
			m_body.setFillColor(m_pressedColor);
			state = true;
		}
		std::cout << "click registered in box" << std::endl;
		return true;
	}
	else return false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_body, states);
	target.draw(m_text, states);
}

void Button::passFont(sf::Font& font)
{
	m_text.setFont(font);
}