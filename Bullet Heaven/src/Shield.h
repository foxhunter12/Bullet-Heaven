#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef SHIELD_H
#define SHIELD_H

class Shield{

    public:

	Shield();

	sf::Vector2f pos;

	void update();
	void render(sf::RenderWindow& window);

	sf::RectangleShape shape;

	sf::Vector2f size;
    
	int cR, cG, cB;

    private:

	bool colorBBool;
	bool colorRBool;
	bool colorGBool;

};

#endif
