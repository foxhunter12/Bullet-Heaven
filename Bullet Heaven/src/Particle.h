#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle{
public:
	Particle(sf::Vector2f npos, sf::Vector2f nspeed, sf::Vector2f nsize, sf::Color color);

	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f size;
	sf::RectangleShape shape;

	int travelledDistanceX, travelledDistanceY;
	
private:

};

#endif
