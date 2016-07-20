#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;

Player::Player(sf::Vector2f npos, sf::Vector2f nsize, sf::Color nbaseColor):
	pos(npos),
	size(nsize),
	baseColor(nbaseColor){
	
	playerShape.setFillColor(baseColor);
	playerShape.setSize(size);
	playerShape.setPosition(pos);
	
	speed = 1.5f;
}

void Player::render(sf::RenderWindow& window){
	window.draw(playerShape);
}

void Player::update(sf::View& view){
	pos.y -= speed;
	playerShape.setPosition(pos);
	view.setCenter(pos.x + (size.x/2), pos.y + (size.y/2));
	if(playerShape.getSize().x != size.x || playerShape.getSize().y != size.y)
		playerShape.setSize(size);
	playerShape.setFillColor(baseColor);
}
