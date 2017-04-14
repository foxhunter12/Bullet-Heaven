#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Star.h"

using namespace std;


Star::Star(sf::Vector2f npos, sf::Vector2f nsize, int rot):
	pos(npos),
	size(nsize){
	
	starShape.setFillColor(sf::Color::White);
	starShape.setSize(size);
	starShape.setPosition(pos);
	starShape.setRotation(rot);
}

void Star::render(std::vector<std::unique_ptr<Star>>& stars, sf::RenderWindow& window){ // Does all star rendering needs
	window.draw(starShape);
}
