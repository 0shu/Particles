#pragma once
#include "particle.h"
#include "button.h"

const unsigned int g_uiPartNum = 10000;

class Handler : public sf::Drawable
{
private:
	float m_fGravityForce;
	float m_fClickForce;
	float m_fInteractionForce;
	float m_fLastTime = 0;
	Button buttons[4];
	sf::Vector2f m_viewSize;

	Particle m_parti[g_uiPartNum];
	bool m_bClicked;
	bool m_bGravity;
	bool m_bInteraction;
	bool m_bBounds;
	sf::Vector2i avg;
public:
	Handler();
	void simpleUpdate(float clockTime);
	void complexUpdate(sf::Vector2i pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void reset();
	void click(sf::Vector2i pos, bool down);
	void passFont(sf::Font& font);
	void setSize(sf::Vector2f size);
};