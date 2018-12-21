#include "particle.h"

Particle::Particle()
{
	//Setting all the base values to be 0;
	m_position.x = 0; m_position.y = 0;
	m_velocity.x = 0; m_velocity.y = 0;
	m_acceleration.x = 0; m_acceleration.y = 0;
	m_body = sf::VertexArray(sf::Points, 1);
	m_mass = 200;
	m_drag = 0.001;
	//puts up a bounding box
	m_minBound = sf::Vector2f(200, 200);
	m_maxBound = sf::Vector2f(600, 600);
}

Particle::Particle(sf::Vector2f pos, float mass)
{
	//Setting all the base values to be 0;
	m_position = pos;
	m_velocity.x = 0; m_velocity.y = 0;
	m_acceleration.x = 0; m_acceleration.y = 0;
	m_body = sf::VertexArray(sf::Points, 1);
	m_body[0].color = sf::Color::White;
	m_mass = mass;
	m_drag = 0.001;
	m_minBound = sf::Vector2f(200, 200);
	m_maxBound = sf::Vector2f(600, 600);
}

//Sets the current position of the particle
void Particle::setPosition(sf::Vector2f pos)
{
	m_position.x = pos.x;
	m_position.y = pos.y;
}

//Gives the particle a specific mass
void Particle::setMass(float mass)
{
	m_mass = mass;
}

//Sets the color of the particle
void Particle::setColor(sf::Color col)
{
	m_body[0].color = col;
}

//Gives the particle a bounding box
void Particle::setBounds(sf::Vector2f bounds)
{
	m_minBound.x = bounds.x; m_minBound.y = bounds.x;
	m_maxBound.x = bounds.y; m_maxBound.y = bounds.y;
}

//Adds force to the particle on a given vector
void Particle::addForce(sf::Vector2f force)
{
	m_acceleration += force * m_mass;
}

//Gives the particle force towards a certain point (can simulate gravity to an object)
void Particle::addForceDirection(sf::Vector2i pos, float force)
{
	sf::Vector2f normaliser;
	normaliser.x += ((float)pos.x - m_position.x);
	normaliser.y += ((float)pos.y - m_position.y);

	normaliser /= std::sqrt((normaliser.x * normaliser.x) + (normaliser.y * normaliser.y));

	m_acceleration += (normaliser * m_mass * force);
}

//checks the object's bounds for escapees
void Particle::checkBounds()
{
	if (m_position.x > m_maxBound.x && m_velocity.x > 0) m_velocity.x *= 0 - 1;
	if (m_position.y > m_maxBound.y && m_velocity.y > 0) m_velocity.y *= 0 - 1;

	if (m_position.x < m_minBound.x && m_velocity.x < 0) m_velocity.x *= 0 - 1;
	if (m_position.y < m_minBound.y && m_velocity.y < 0) m_velocity.y *= 0 - 1;
}

//Updates the basic values for the pysics
void Particle::update(float elapsedTime)
{
	m_body[0].position = m_position;
	m_position += m_velocity * elapsedTime;
	m_velocity += m_acceleration * elapsedTime;
	m_velocity -= m_velocity * m_drag;
	m_acceleration = sf::Vector2f(0, 0);
}

//draws each particle
void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_body, states);
}

void Particle::freeze()
{
	m_acceleration = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
}

//returns the current position of the particle
sf::Vector2f Particle::getPosition() const
{
	return m_position;
}
