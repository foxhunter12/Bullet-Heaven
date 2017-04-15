#include <iostream>
#include <SFML/Graphics.hpp>
#include "Explosion.h"
#include <memory>

using namespace std;

Explosion::Explosion(sf::Vector2f npos):
    pos(npos){

    color1 = sf::Color::Red;
    color2 = sf::Color(255, 99, 71);
    color3 = sf::Color(255, 165, 0);

    radius = 1;
    baseShape.setRadius(radius);
    baseShape.setPosition(pos);
    baseShape.setFillColor(color1);
    baseShape.setOutlineColor(color2);
    baseShape.setOutlineThickness(.7f);

    radiusMax = 6;
    amount = 10;
    amountMade = 0;
    spawnTimerBase = 3;
    spawnTimer = spawnTimerBase;

    growthTimerBase = 6;
    growthTimer = growthTimerBase;

}

void Explosion::render(sf::RenderWindow& window){
    for(unsigned int i = 0; i < shapes.size(); i++){
	window.draw(shapes[i]);
    }
}

void Explosion::update(){
    spawnTimer--;
    growthTimer--;
    if(spawnTimer <= 0 && amountMade <= amount){ // To stagger the explosions, makes it look nicer.
		int tempX = rand()%15 + 0; // Random offset
		int tempY = rand()%15 + 0; // Random offset, in retrospect, I should of named these 'offsetx' and 'offsety', oh well
		baseShape.setPosition(sf::Vector2f(pos.x + tempX, pos.y + tempY));
		shapes.push_back(baseShape);
		spawnTimer = spawnTimerBase;
		amountMade++;
    }

    if(growthTimer <= 0){
		for(unsigned int i = 0; i < shapes.size(); i++){
			if(shapes[i].getRadius() < radiusMax){
				if(i % 2 == 0) shapes[i].setFillColor(color1); // Really lame and work-aroundy way to get random colors because
				else shapes[i].setFillColor(color3); /////////// I'm too lazy to do real random :)
				shapes[i].setRadius(shapes[i].getRadius() + 1); // Increase radius
				growthTimer = growthTimerBase;
			}
			auto it = std::remove_if(shapes.begin(), shapes.end(), [this](const sf::CircleShape& c){
			return c.getRadius() >= radiusMax;
			});
			shapes.erase(it, shapes.end());
		}
    }
}
