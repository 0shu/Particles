#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Button : public sf::Drawable
{
private:
	sf::RectangleShape m_body;
	bool state = false;
	sf::Color m_pressedColor;
	sf::Color m_offColor;
	sf::Text m_text;
public:
	Button();
	void setup(sf::IntRect rect, std::string string);
	bool click(sf::Vector2i pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void passFont(sf::Font& font);
};