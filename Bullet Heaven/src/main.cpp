#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <deque>
#include <ctime>

#include "Star.h"
#include "Player.h"
#include "ParticleEmitter.h"

using namespace std;

std::unique_ptr<Star> makeStar(int w, int h){ // Generates a random star :^)
	int tempX = rand() % w + 1;
	int tempY = 1;

	int startW = 3;
	int startH = startW;
	
	return std::unique_ptr<Star>(new Star(sf::Vector2f((float)tempX, (float)tempY), sf::Vector2f(startW, startH)));
}

void starHandler(std::vector<std::unique_ptr<Star>>& stars, int& sgt, int& sgtb, int w, int h){ // Handles all star events
	if(sgt > 0){
		sgt--;
	}
	else{
		stars.push_back(makeStar(w, h));
		sgt = sgtb;
	}

}

int main(){

	int resX = 800;
	int resY = 600;

	srand(time(NULL)); //Obvious -- just sets the random seed [lolnotevenrandomkthxc/c++]

	bool inGame = true;
	//bool inMenu = false;

	float dt = 1.f/40.f; // Modify this to change physics rate.
	float accumulator = 0.f;

	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(resX, resY), "Bullet Heaven", sf::Style::Close); //Basic window properties

	sf::View view;
	view.setSize(resX, resY);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

	Player player(sf::Vector2f(0, 0), sf::Vector2f(20, 35), sf::Color::Blue);

	player.pos = sf::Vector2f((resX/2) - (player.size.x/2), (resY/2) - (player.size.y/2));

	int starGenerateTimerBase = 10; // Couple of variables to control speed on which stars generate. ezpz
	int starGenerateTimer = starGenerateTimerBase;

	std::vector<std::unique_ptr<Star>> stars; // stars list obviously

	bool hasFocus = true;

	while(window.isOpen()){ window.setView(view);

		sf::Event event;

		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}

		accumulator += clock.getElapsedTime().asSeconds();
		clock.restart();

		window.clear(); // RENDERING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(inGame){
			for(unsigned int i = 0; i < stars.size(); i++){
				stars[i]->render(stars, window);

			}

			player.render(window);

			window.setMouseCursorVisible(false);
		}


		while(accumulator >= dt){ // UPDATING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if(inGame){ //INGAME

				accumulator -= dt;

				if(!window.hasFocus() && hasFocus)
					hasFocus = false;
				else if(window.hasFocus() && !hasFocus)
					hasFocus = true;
			
				starHandler(stars, starGenerateTimer, starGenerateTimerBase, resX, resY); // Updates stars
				for(unsigned int i = 0; i < stars.size(); i++){
					stars[i]->pos.y += player.speed;
					stars[i]->starShape.setPosition(stars[i]->pos);
					if(stars[i]->pos.y >= resY)
						stars.erase(stars.begin() + i); // Erases stars if ^ (below screen)
				}
				player.update(view, resX, resY, hasFocus);


			}
		}
		window.setFramerateLimit(60);

		window.display();
	}
	return 0;
}
