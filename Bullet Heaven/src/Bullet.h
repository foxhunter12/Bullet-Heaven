#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleEmitter.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet{
public:
	Bullet();

	sf::Vector2f pos;
	sf::Color color;
	sf::RectangleShape shape;
	ParticleEmitter particleEmitter;

private:
	
};

#endif
