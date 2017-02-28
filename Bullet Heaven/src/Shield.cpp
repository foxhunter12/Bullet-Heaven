#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shield.h"

using namespace std;

Shield::Shield(){
    pos = sf::Vector2f(0.f, 0.f);
    size = sf::Vector2f(45.0f, 55.0f);
    sizeBase = size;
    shape.setSize(size);
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setFillColor(sf::Color::Transparent);
    cR = 255;
    cG = 165;
    cB = 0;
    colorRBool = true;
    colorGBool = true;
    colorBBool = true;
    canChangeColor = true;

}

void Shield::update(){

    shape.setPosition(pos);
    shape.setSize(size);

    if(canChangeColor){
	if(colorBBool){ // All this bullshit deals with chaning the color of the shield randomly but very smoothly.
	    cB += 4;
	    if(cB >= 255){
		colorBBool = false;
	    }
	}
	else{
	    cB -= 4;
	    if(cB <= 0){
		colorBBool = true;
	    }
	}
	if(colorRBool){
	    cR -= 5;
	    if(cR <= 0){
		colorRBool = false;
	    }
	}
	else{
	    cR += 5;
	    if(cR >= 255){
		colorRBool = true;
	    }
	}
	if(colorGBool){
	    cG += 3;
	    if(cG >= 255){
		colorGBool = false;
	    }
	}
	else{
	    cG -= 3;
	    if(cG <= 0){
		colorGBool = true;
	    }
	}
	shape.setOutlineColor(sf::Color(cR, cG, cB));
    }

}

void Shield::render(sf::RenderWindow& window){
    window.draw(shape);
}
