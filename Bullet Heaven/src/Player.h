#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleEmitter.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
	Player(sf::Vector2f npos, sf::Vector2f nsize, sf::Color nbaseColor);

	sf::Color baseColor;
	sf::Vector2f pos;
	sf::Vector2f size;
	
	sf::RectangleShape playerShape;

	sf::RectangleShape playerEngine;

	sf::RectangleShape playerGlass;
	
	sf::RectangleShape playerGun;
	
	sf::RectangleShape playerLWing;

	sf::RectangleShape playerRWing;

	void render(sf::RenderWindow& window);
	void update(sf::View& view, int rX, int rY);
	
	float speed;
	
	bool isGoingLeft();
	bool isGoingRight();
	bool isGoingUp();
	bool isGoingDown();

	ParticleEmitter pe;
private:

	float playerEngineXC;
	float playerEngineYC;
	float playerGlassXC;
	float playerGlassYC;
	float playerGunXC;
	float playerGunYC;
	float playerLWingXC;
	float playerLWingYC;
	float playerRWingXC;
	float playerRWingYC;

};

#endif
