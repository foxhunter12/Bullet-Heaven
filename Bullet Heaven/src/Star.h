#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#ifndef STAR_H
#define STAR_H

class Star{
public:
	Star(sf::Vector2f nposition, sf::Vector2f nsize, int rot);
	void render(std::vector<std::unique_ptr<Star>>& stars, sf::RenderWindow& window);
	
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::RectangleShape starShape;
private:

};


#endif
