#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shield.h"

using namespace std;


Shield::Shield(sf::Vector2f npos, sf::Color shieldColor, float outlineThickness, sf::Vector2f nsize, int nshieldTimer):
	pos(npos),
	size(nsize),
	shieldTimer(nshieldTimer){

		shape.setSize(size);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(shieldColor);
		shape.setFillColor(sf::Color::Transparent);

	}

void Shield::update(){

}

void Shield::render(sf::RenderWindow& window){
	window.draw(shape);
}
