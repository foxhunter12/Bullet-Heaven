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
	
	speed = 2.5f;
}

void Player::render(sf::RenderWindow& window){
	window.draw(playerShape);
}

void Player::update(sf::View& view, int rX, int rY){
	playerShape.setPosition(pos);
	if(playerShape.getSize().x != size.x || playerShape.getSize().y != size.y)
		playerShape.setSize(size);
	playerShape.setFillColor(baseColor);
	if(isGoingLeft()){
		pos.x -= speed;
	}
	else if(isGoingRight()){
		pos.x += speed;
	}
	if(isGoingUp()){
		pos.y -= speed;
	}
	else if(isGoingDown()){
		pos.y += speed;
	}

	if(pos.x <= 0)
		pos.x += speed;
	if(pos.x + size.x >= rX)
		pos.x -= speed;
	if(pos.y <= 0)
		pos.y += speed;
	if(pos.y + size.y >= rY)
		pos.y -= speed;
}

bool Player::isGoingLeft(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		return true;
	}
	else{
		return false;
	}
}

bool Player::isGoingRight(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		return true;
	}
	else{
		return false;
	}
}

bool Player::isGoingUp(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		return true;
	}
	else{
		return false;
	}
}

bool Player::isGoingDown(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		return true;
	}
	else{
		return false;
	}
}
