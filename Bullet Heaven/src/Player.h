#include <iostream>
#include <SFML/Graphics.hpp>


#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
	Player(sf::Vector2f npos, sf::Vector2f nsize, sf::Color nbaseColor);

	sf::Color baseColor;
	sf::Vector2f pos;
	sf::Vector2f size;
	
	sf::RectangleShape playerShape;

	void render(sf::RenderWindow& window);
	void update(sf::View& view, int rX, int rY);
	
	float speed;
	
	bool isGoingLeft();
	bool isGoingRight();
	bool isGoingUp();
	bool isGoingDown();
		
private:

};

#endif
