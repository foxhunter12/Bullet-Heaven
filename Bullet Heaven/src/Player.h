#include <iostream>
#include <SFML/Graphics.hpp>
#include "ParticleEmitter.h"
#include "Bullet.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player{
		public:
				Player(sf::Vector2f npos, sf::Vector2f nsize, sf::Color nbaseColor);

				sf::Color baseColor;
				sf::Vector2f pos;
				sf::Vector2f size;

				sf::RectangleShape playerShape;

				sf::RectangleShape playerEngine;

				sf::RectangleShape playerGlass;

				sf::RectangleShape playerGun;

				void render(sf::RenderWindow& window);
				void update(sf::View& view, int rX, int rY, bool hasFocus);

				float speed;

				bool isGoingLeft();
				bool isGoingRight();
				bool isGoingUp();
				bool isGoingDown();
				bool isSpacebar();

				ParticleEmitter pe1;
				ParticleEmitter pe2;

				bool drawEngineParticles;

				std::vector<std::unique_ptr<Bullet>> bullets;

				bool alive;

		private:

				int bulletTimer;
				int bulletTimerBase;

				float playerEngineXC;
				float playerEngineYC;
				float playerGlassXC;
				float playerGlassYC;
				float playerGunXC;
				float playerGunYC;

};

#endif
