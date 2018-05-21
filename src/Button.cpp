#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"

using namespace std;

Button::Button(sf::Vector2f npos, sf::Color ncolor, sf::Color noutlineColor, float noutlineThickness, sf::Vector2f nsize, string textString):
    pos(npos),
    size(nsize){
    
    shape.setPosition(pos);
    shape.setSize(size);
    shape.setFillColor(ncolor);
    shape.setOutlineColor(noutlineColor);
    shape.setOutlineThickness(noutlineThickness);

    text.setString(textString);
    text.setColor(noutlineColor);
    text.setCharacterSize((nsize.y/3)*2);
    text.setPosition(sf::Vector2f((pos.x + size.x/2) - text.getCharacterSize() - 10, pos.y));

    selected = false;
    
}

bool Button::isPressed(){
    if(selected && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    	return true; 
    return false;
}

void Button::update(){
    isPressed();
}

void Button::render(sf::RenderWindow& window){
    window.draw(shape);
    window.draw(text);
}


