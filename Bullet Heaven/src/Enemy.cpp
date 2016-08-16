#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "ParticleEmitter.h"

using namespace std;

Enemy::Enemy(sf::Vector2f npos, sf::Vector2f nsize, float nspeed, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, enemyType ntype, int nmovementTimer):
pos(npos),
size(nsize),
speed(nspeed),
color(ncolor),
outlineColor(noutlineColor),
outlineThickness(noutlineThickness),
type(ntype),
movementTimerBase(nmovementTimer),
alive(true){

	shape.setPosition(pos);
	shape.setSize(size);
	shape.setFillColor(color);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(outlineThickness);

	if(type == E_DOWN){
    	pe1.init(sf::Vector2f(pos.x + (size.x/2), pos.y + (size.y/2)), sf::Vector2f(speed, speed), sf::Vector2f(2.75f, 2.75f), sf::Vector2f(20, 20), sf::Vector2f(1.f, 1.f), 30.0f, 15.f, 1, PET_UP, sf::Color(100, 100, 25)); // Create an particle emitter, with color orange.
	}
	if(type == E_LEFT){
    	pe1.init(sf::Vector2f(pos.x + (size.x/2), pos.y + (size.y/2)), sf::Vector2f(speed, speed), sf::Vector2f(2.75f, 2.75f), sf::Vector2f(20, 20), sf::Vector2f(1.f, 1.f), 30.0f, 15.f, 1, PET_RIGHT, sf::Color(100, 100, 25)); // Create an particle emitter, with color orange.
	}
	if(type == E_RIGHT){
    	pe1.init(sf::Vector2f(pos.x + (size.x/2), pos.y + (size.y/2)), sf::Vector2f(speed, speed), sf::Vector2f(2.75f, 2.75f), sf::Vector2f(20, 20), sf::Vector2f(1.f, 1.f), 30.0f, 15.f, 1, PET_LEFT, sf::Color(100, 100, 25)); // Create an particle emitter, with color orange.
	}
}

Enemy::Enemy(sf::Vector2f nsize, float nspeed, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, enemyType ntype, int nmovementTimer):
size(nsize),
speed(nspeed),
color(ncolor),
outlineColor(noutlineColor),
outlineThickness(noutlineThickness),
type(ntype),
movementTimerBase(nmovementTimer),
alive(true){

	int tempW = 800 - size.x;
	int tempH = 560;
	if(type == E_DOWN)
		pos = sf::Vector2f(sf::Vector2f(rand() % tempW + 0, 0)); // World w: 800, h: 600(changed to 200 to make it more reasonable for play); If you are defining an enemy without a custom needed position.
	else if(type == E_RIGHT)
		pos = sf::Vector2f(sf::Vector2f(0, rand() % tempH + 0));
	else if(type == E_LEFT)
		pos = sf::Vector2f(sf::Vector2f(tempW, rand() % tempH + 0));
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setFillColor(color);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(outlineThickness);
	if(type == E_DOWN){
    	pe1.init(sf::Vector2f(pos.x + (size.x/2), pos.y + (size.y/2)), sf::Vector2f(speed, speed), sf::Vector2f(2.75f, 2.75f), sf::Vector2f(15, 15), sf::Vector2f(1.f, 1.f), 30.0f, 15.f, 1, PET_UP, sf::Color(200, 200, 25)); // Create an particle emitter, with color orange.
	}
	if(type == E_LEFT){
    	pe1.init(sf::Vector2f(pos.x + (size.x/2), pos.y + (size.y/2)), sf::Vector2f(speed, speed), sf::Vector2f(2.75f, 2.75f), sf::Vector2f(15, 15), sf::Vector2f(1.f, 1.f), 30.0f, 15.f, 1, PET_RIGHT, sf::Color(200, 200, 25)); // Create an particle emitter, with color orange.
	}
	if(type == E_RIGHT){
    	pe1.init(sf::Vector2f(pos.x + (size.x/2), pos.y + (size.y/2)), sf::Vector2f(speed, speed), sf::Vector2f(2.75f, 2.75f), sf::Vector2f(15, 15), sf::Vector2f(1.f, 1.f), 30.0f, 15.f, 1, PET_LEFT, sf::Color(200, 200, 25)); // Create an particle emitter, with color orange.
	}
}

Enemy::Enemy(): // Default const.
alive(true){

	int tempW = 800 - size.x;
	int tempH = 560;
	type = E_DOWN;
	if(type == E_DOWN)
		pos = sf::Vector2f(sf::Vector2f(rand() % tempW + 0, 0)); // World w: 800, h: 600(changed to 200 to make it more reasonable for play); If you are defining an enemy without a custom needed position.
	else if(type == E_RIGHT)
		pos = sf::Vector2f(sf::Vector2f(0, rand() % tempH + 0));
	else if(type == E_LEFT)
		pos = sf::Vector2f(sf::Vector2f(tempW, rand() % tempH + 0));
	shape.setPosition(pos);
	size = sf::Vector2f(10, 10);
	speed = 1.f;
	color = sf::Color::Red;
	outlineColor = sf::Color::White;
	outlineThickness = 1.5f;

	shape.setPosition(pos);
	shape.setSize(size);
	shape.setFillColor(color);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(outlineThickness);
}

void Enemy::init(sf::Vector2f npos, sf::Vector2f nsize, float nspeed, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, enemyType ntype, int nmovementTimer){ // For default contructor/new params.

	int tempW = 800 - size.x;
	int tempH = 560;
	type = ntype;
	if(movementTimer < movementTimerBase){
		if(type == E_DOWN)
			pos = sf::Vector2f(sf::Vector2f(rand() % tempW + 0, 0)); // World w: 800, h: 600(changed to 200 to make it more reasonable for play); If you are defining an enemy without a custom needed position.
		else if(type == E_RIGHT)
			pos = sf::Vector2f(sf::Vector2f(0, rand() % tempH + 0));
		else if(type == E_LEFT)
			pos = sf::Vector2f(sf::Vector2f(size.x, rand() % tempH + 0));
	}
	shape.setPosition(pos);
	size = nsize;
	speed = nspeed;
	color = ncolor;
	outlineColor = noutlineColor;
	outlineThickness = noutlineThickness;
	movementTimerBase = nmovementTimer;

}

void Enemy::render(sf::RenderWindow& window){
	if(alive){ // Le alive checkssss
		if(movementTimer >= movementTimerBase){
			pe1.canMakeParticles = false;
		}
        pe1.render(window);
		window.draw(shape);
	}
}

void Enemy::update(){
	if(alive){
		shape.setPosition(pos);

		if(movementTimer < movementTimerBase){
   			pe1.pos = sf::Vector2f(pos.x + (size.x/2), pos.y + (size.y/2));
		}
        pe1.update(speed);
		
		if(type == E_DOWN){ // Check which method to run
			if(pos.y <= 300){ // Catch the random enemy that moves too far randomly because I'm too dumb to fix this
				downMovement();
			}
			else
				movementTimer = movementTimerBase;
		}
		else if(type == E_LEFT){ // 2
			if(pos.x >= 450){
				leftMovement();
			}
			else
				movementTimer = movementTimerBase;
		}
		else if(type == E_RIGHT){ // 3
			if(pos.x <= 400){
				rightMovement();
			}
			else
				movementTimer = movementTimerBase;
		}
	}
}

void Enemy::downMovement(){ // Here are the movement methods for the enemies
	if(movementTimer < movementTimerBase){
		pos.y += speed;
		movementTimer++;
	}
	
}

void Enemy::leftMovement(){
	if(movementTimer < movementTimerBase){
		pos.x -= speed;
		movementTimer++;
	}
}

void Enemy::rightMovement(){
	if(movementTimer < movementTimerBase){
		pos.x += speed;
		movementTimer++;
	}
}
