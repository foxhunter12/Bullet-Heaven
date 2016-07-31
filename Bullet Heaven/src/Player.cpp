#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ParticleEmitter.h"

using namespace std;

Player::Player(sf::Vector2f npos, sf::Vector2f nsize, sf::Color nbaseColor):
	pos(npos),
	size(nsize),
	baseColor(nbaseColor){
	
	playerShape.setFillColor(baseColor);
	playerShape.setSize(size);
	playerShape.setPosition(pos);

	playerEngineXC = 3.f; // Constants for the divisions I use for placing the ship's parts, to keep it the same any time I change the size
	playerEngineYC = 6.f;	

	playerEngine.setFillColor(sf::Color(100, 100, 100)); // Obv.
	playerEngine.setSize(sf::Vector2f(playerShape.getSize().x/playerEngineXC,playerShape.getSize().y/playerEngineYC)); // sets size!
	playerEngine.setPosition(sf::Vector2f(pos.x+((playerShape.getSize().x/2)-(playerEngine.getSize().x/2)), pos.y+playerShape.getSize().y));

	playerGlassXC = 3.5f; // Rest of the stuff is the same
	playerGlassYC = 2.8f;

	playerGlass.setFillColor(sf::Color::Cyan);
	playerGlass.setSize(sf::Vector2f(playerShape.getSize().x/playerGlassXC,playerShape.getSize().y/playerGlassYC));
	playerGlass.setPosition(sf::Vector2f(pos.x+((playerShape.getSize().x/2)-(playerGlass.getSize().x/2)), pos.y+playerGlassYC));

	playerGunXC = 7.f; 
	playerGunYC = 5.6f;	

	playerGun.setFillColor(sf::Color(200, 200, 200)); // Obv.
	playerGun.setSize(sf::Vector2f(playerShape.getSize().x/playerGunXC,playerShape.getSize().y/playerGunYC)); // sets size!
	playerGun.setPosition(sf::Vector2f(pos.x+((playerShape.getSize().x/2)-(playerGun.getSize().x/2)), pos.y-playerGun.getSize().y));

	playerLWingXC = 2.f; 
	playerLWingYC = 2.f;
	playerLWing.setRotation(15);

	playerLWing.setFillColor(baseColor);
	playerLWing.setSize(sf::Vector2f(playerShape.getSize().x/playerLWingXC,playerShape.getSize().y/playerLWingYC));
	playerLWing.setPosition(sf::Vector2f(pos.x-playerLWing.getSize().x+5, pos.y+playerLWing.getSize().y-playerLWingYC));

	playerRWingXC = 2.f;
	playerRWingYC = 2.f;
	playerRWing.setRotation(-15);

	playerRWing.setFillColor(baseColor);
	playerRWing.setSize(sf::Vector2f(playerShape.getSize().x/playerRWingXC,playerShape.getSize().y/playerRWingYC));
	playerRWing.setPosition(sf::Vector2f(pos.x+playerShape.getSize().x-5, pos.y+playerRWing.getSize().y-playerRWingYC+2));

	speed = 2.5f; // Basically gamespeed
    
    pe1.init(sf::Vector2f(playerEngine.getPosition().x + (playerEngine.getSize().x/2) - pe1.baseSize.x, playerEngine.getPosition().y + playerEngine.getSize().y), sf::Vector2f(speed, speed), sf::Vector2f(3.f, 3.f), sf::Vector2f(20, 20), sf::Vector2f(.5f, .5f), 1.f, 15.f, 1, PET_DOWN, sf::Color(200, 200, 25)); // Create an particle emitter, with color orange.

    pe2.init(sf::Vector2f(playerEngine.getPosition().x + (playerEngine.getSize().x/2) - pe2.baseSize.y, playerEngine.getPosition().y + playerEngine.getSize().y), sf::Vector2f(speed, speed), sf::Vector2f(3.f, 3.f), sf::Vector2f(10, 10), sf::Vector2f(.5f, .5f), 1.f, 15.f, 1, PET_DOWN, sf::Color(255, 25, 25)); // Create an particle emitter, with color red.

}

   void Player::render(sf::RenderWindow& window){
    pe2.render(window);
    pe1.render(window);
	window.draw(playerShape);
	window.draw(playerGlass);
	window.draw(playerEngine);
	window.draw(playerGun);
	window.draw(playerLWing);
	window.draw(playerRWing);
}

void Player::update(sf::View& view, int rX, int rY){
	playerShape.setPosition(pos); // All the position setting.
	playerEngine.setPosition(sf::Vector2f(pos.x+((playerShape.getSize().x/2)-(playerEngine.getSize().x/2)), pos.y+playerShape.getSize().y));
	playerGlass.setPosition(sf::Vector2f(pos.x+((playerShape.getSize().x/2)-(playerGlass.getSize().x/2)), pos.y+playerGlassYC));
	playerGun.setPosition(sf::Vector2f(pos.x+((playerShape.getSize().x/2)-(playerGun.getSize().x/2)), pos.y-playerGun.getSize().y));
	playerLWing.setPosition(sf::Vector2f(pos.x-playerLWing.getSize().x+5, pos.y+playerLWing.getSize().y-playerLWingYC));
	playerRWing.setPosition(sf::Vector2f(pos.x+playerShape.getSize().x-5, pos.y+playerRWing.getSize().y-playerRWingYC+2));
	if(playerShape.getSize().x != size.x || playerShape.getSize().y != size.y){ // If the ship changes size, change
		playerShape.setSize(size);
		playerEngine.setSize(sf::Vector2f(playerShape.getSize().x/playerEngineXC,playerShape.getSize().y/playerEngineYC));
		playerGlass.setSize(sf::Vector2f(playerShape.getSize().x/playerGlassXC,playerShape.getSize().y/playerGlassYC));
		playerGun.setSize(sf::Vector2f(playerShape.getSize().x/playerGunXC,playerShape.getSize().y/playerGunYC)); // sets size!
		playerLWing.setSize(sf::Vector2f(playerShape.getSize().x/playerLWingXC,playerShape.getSize().y/playerLWingYC));
		playerRWing.setSize(sf::Vector2f(playerShape.getSize().x/playerRWingXC,playerShape.getSize().y/playerRWingYC));
	}
	if(isGoingLeft()){ // Basic movement
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

	if(pos.x <= 0) // Make sure you don't leave the map :O
		pos.x += speed;
	if(pos.x + size.x >= rX)
		pos.x -= speed;
	if(pos.y <= 0)
		pos.y += speed;
	if(pos.y + size.y >= rY)
		pos.y -= speed;
	
    pe1.pos = sf::Vector2f(playerEngine.getPosition().x + (playerEngine.getSize().x/2) - pe1.baseSize.x, playerEngine.getPosition().y + playerEngine.getSize().y);
    pe2.pos = sf::Vector2f(playerEngine.getPosition().x + (playerEngine.getSize().x/2) - pe2.baseSize.y, playerEngine.getPosition().y + playerEngine.getSize().y);

    pe1.update(speed);
    pe2.update(speed);

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
