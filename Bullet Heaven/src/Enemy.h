#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "ParticleEmitter.h"

#ifndef ENEMY_H
#define ENEMY_H

enum enemyType{ // Which direction the enemy moves to.

	E_DOWN = 0,
	E_LEFT,
	E_RIGHT,
	E_STATIONARY

};

class Enemy{
public:
	Enemy(sf::Vector2f npos, sf::Vector2f nsize, float nspeed, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, enemyType ntype, int nmovementTimer);
	Enemy(sf::Vector2f nsize, float nspeed, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, enemyType ntype, int nmovementTimer);
	Enemy();
	
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::RectangleShape shape;
	std::vector<std::unique_ptr<Bullet>> bullets;
	float speed;
	sf::Color color;
	sf::Color outlineColor;
	float outlineThickness;
	bool alive;
	
	enemyType type;

	void render(sf::RenderWindow& window);
	void update();
	void init(sf::Vector2f npos, sf::Vector2f nsize, float nspeed, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, enemyType ntype, int nmovementTimer);

	int movementTimer;
	int movementTimerBase;

	ParticleEmitter pe1;

private:

	void downMovement();
	void leftMovement();
	void rightMovement();

};

#endif
