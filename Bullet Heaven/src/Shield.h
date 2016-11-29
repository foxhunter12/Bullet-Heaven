#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef SHIELD_H
#define SHIELD_H

class Shield{

	public:

		Shield(sf::Vector2f npos, sf::Color shieldColor, float outlineThickness, sf::Vector2f nsize, int nshieldTimer);

		sf::Vector2f pos;

		void update();
		void render(sf::RenderWindow& window);

		sf::RectangleShape shape;

		sf::Vector2f size;

		int shieldTimer;
		int shieldTimerBase;

	private:

};

#endif
