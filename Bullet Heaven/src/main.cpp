#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <deque>
#include <ctime>

using namespace std;

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

	while(window.isOpen()){

		window.setView(view);

		sf::Event event;

		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::Resized)
				view = getLetterboxView(view, event.size.width, event.size.height);
		}

		accumulator += clock.getElapsedTime().asSeconds();
		clock.restart();

		while(accumulator >= dt){ // UPDATING
			if(inGame){ //INGAME

				accumulator -= dt;


			}
		}


		window.clear(); // RENDERING
		if(inGame){
			window.setMouseCursorVisible(false);
		}

		window.setFramerateLimit(60);

		window.display();
	}
	return 0;
}
