#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
public:
	Enemy();
	Enemy(sf::Vector2f npos, sf::Vector2f nsize, float nspeed, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness);
	
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::RectangleShape shape;
	std::vector<std::unique_ptr<Bullet>> bullets;
	float speed;
	sf::Color color;
	sf::Color outlineColor;
	float outlineThickness;

private:


};

#endif
