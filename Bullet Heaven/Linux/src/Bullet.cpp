#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <memory.h>

using namespace std;

Bullet::Bullet(sf::Vector2f npos, sf::Vector2f size, sf::Vector2f nspeed, sf::Color ncolor):
		pos(npos),
		speed(nspeed),
		color(ncolor),
		deleteThis(false){
				shape.setPosition(pos);
				shape.setSize(size);
				shape.setFillColor(color);
		}

Bullet::Bullet(sf::Vector2f npos, sf::Vector2f size, sf::Vector2f nspeed, sf::Color ncolor, sf::Color noutlineColor):
		pos(npos),
		speed(nspeed),
		color(ncolor),
		deleteThis(false){
				shape.setPosition(pos);
				shape.setSize(size);
				shape.setFillColor(color);
				shape.setOutlineColor(noutlineColor);
				shape.setOutlineThickness(1.5f);
		}

void Bullet::update(){
		pos.x += speed.x;
		pos.y += speed.y;
		shape.setPosition(pos);
		if(pos.x + shape.getSize().x < 0 || pos.x >= 800 || pos.y + shape.getSize().y < 0 || pos.y >= 600){
				deleteThis = true;
		}
}

void Bullet::render(sf::RenderWindow& window){
		window.draw(shape);
}
