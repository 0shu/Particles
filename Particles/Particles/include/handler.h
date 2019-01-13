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
	float m_fBorder = 50;
	sf::Color m_baseColor;
	sf::Color m_variationColor;
	float m_fMass = 1;

	Particle m_parti[g_uiPartNum];
	bool m_bClicked;
	bool m_bGravity;
	bool m_bInteraction;
	bool m_bBounds;
	sf::Vector2i avg;
public:
	Handler(sf::Vector2f window);
	void simpleUpdate(float clockTime);
	void complexUpdate(sf::Vector2i pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void reset();
	void click(sf::Vector2i pos, bool down);
	void passFont(sf::Font& font);
	void setSize(sf::Vector2f size);
	void setBorder(float border);
	void setColors(sf::Color base, sf::Color variation);
};