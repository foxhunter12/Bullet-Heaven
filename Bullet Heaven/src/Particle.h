#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle{
public:
	Particle(sf::Vector2f npos, sf::Vector2f nspeed, sf::Vector2f nsize, sf::Color color, float nrotSpeed);

	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f size;
	sf::RectangleShape shape;

	float rotSpeed;

	int travelledDistanceX, travelledDistanceY;
	
private:

};

#endif
