#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class Particle : public sf::Drawable
{
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	sf::VertexArray m_body;
	float m_mass;
	float m_drag;
	sf::Vector2f m_minBound;
	sf::Vector2f m_maxBound;

public:
	Particle();
	Particle(sf::Vector2f pos, float mass);
	void update(float elapsedTime);
	void checkBounds();
	void addForce(sf::Vector2f force);
	void addForceDirection(sf::Vector2i pos, float force);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f pos);
	void setMass(float mass);
	void setColor(sf::Color col);
	void setBounds(sf::Vector2f bounds);
	void freeze();
	sf::Vector2f getPosition() const;
};