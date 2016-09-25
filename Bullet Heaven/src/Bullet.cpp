#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

using namespace std;

Bullet::Bullet(sf::Vector2f npos, sf::Vector2f size,sf::Vector2f nspeed, sf::Color ncolor):
pos(npos),
speed(nspeed),
color(ncolor){
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setFillColor(color);
}

void Bullet::update(){
	pos.x += speed.x;
	pos.y += speed.y;
	shape.setPosition(pos);
}

void Bullet::render(sf::RenderWindow& window){
	window.draw(shape);
}
