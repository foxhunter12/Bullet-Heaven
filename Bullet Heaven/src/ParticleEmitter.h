#include <iostream>
#include <SFML/Graphics.hpp>

#include "Particle.h"

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

enum particleEmitterType{ // Determines what direction the particles will fly.
	PET_UP = 0,
	PET_DOWN,
	PET_LEFT,
	PET_RIGHT
};

class ParticleEmitter{
public:
	ParticleEmitter();
	ParticleEmitter(sf::Vector2f npos, sf::Vector2f nbaseSpeed, sf::Vector2f nbaseSize, sf::Vector2f nremoveDistance, sf::Vector2f nspeedOffset, float nsizeVariation, float nbaseRotationSpeed, int nparticleCreateTimer, particleEmitterType ntype, sf::Color color);

	particleEmitterType type;

	sf::Vector2f pos;
	sf::Vector2f baseSpeed;
	sf::Vector2f baseSize;
	sf::Vector2f removeDistance;
	sf::Vector2f speedOffset;
	sf::Color color;
	std::vector<std::unique_ptr<Particle>> particles;
	float sizeVariation;
	float baseRotationSpeed;
	int particleCreateTimer;
	int particleCreateTimerBase;
	void render(sf::RenderWindow& window);
	void update(float speed);
	void createParticle();
	void init(sf::Vector2f npos, sf::Vector2f nbaseSpeed, sf::Vector2f nbaseSize, sf::Vector2f nremoveDistance, sf::Vector2f nspeedOffset, float nsizeVariation, float nbaseRotationSpeed, int nparticleCreateTimer, particleEmitterType ntype, sf::Color ncolor);
	bool canMakeParticles;

private:

};

#endif
