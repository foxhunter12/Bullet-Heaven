#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Particle.h"

using namespace std;


Particle::Particle(sf::Vector2f npos, sf::Vector2f nspeed, sf::Vector2f nsize, sf::Color color, float nrotSpeed):
pos(npos),
speed(nspeed),
size(nsize),
rotSpeed(nrotSpeed){

	shape.setFillColor(color);
	shape.setSize(size);
	shape.setPosition(pos);

	travelledDistanceX = 0;
	travelledDistanceY = 0;

}
