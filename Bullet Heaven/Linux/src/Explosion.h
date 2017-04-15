#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion{
public:
    Explosion(sf::Vector2f npos);

    sf::Vector2f pos;
    sf::CircleShape baseShape;

    std::vector<sf::CircleShape> shapes;

    void render(sf::RenderWindow& window);
    void update();

    int amount, amountMade;

private:
    sf::Color color1, color2, color3;
    int radiusMax, radius, spawnTimer, spawnTimerBase, growthTimer, growthTimerBase;

};

#endif 
