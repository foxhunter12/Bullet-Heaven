#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef BUTTON_H
#define BUTTON_H

class Button{

public:

    Button(sf::Vector2f npos, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, sf::Vector2f nsize, std::string textString);

    sf::RectangleShape shape;
    sf::Vector2f pos;
    bool selected;
    sf::Text text;
    sf::Vector2f size;

    void update();

    void render(sf::RenderWindow& window);
    
    bool isPressed();

private:

};

#endif
