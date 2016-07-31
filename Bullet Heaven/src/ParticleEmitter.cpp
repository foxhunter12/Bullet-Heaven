#include <iostream>
#include <SFML/Graphics.hpp>

#include "ParticleEmitter.h"
#include "Particle.h"

using namespace std;

ParticleEmitter::ParticleEmitter(){}

ParticleEmitter::ParticleEmitter(sf::Vector2f npos, sf::Vector2f nbaseSpeed, sf::Vector2f nbaseSize, sf::Vector2f nremoveDistance, sf::Vector2f nspeedOffset, float nsizeVariation, float nbaseRotationSpeed, int nparticleCreateTimer, particleEmitterType ntype, sf::Color color):
pos(npos),
baseSpeed(nbaseSpeed),
baseSize(nbaseSize),
removeDistance(nremoveDistance),
speedOffset(nspeedOffset),
sizeVariation(nsizeVariation),
baseRotationSpeed(nbaseRotationSpeed),
particleCreateTimer(nparticleCreateTimer),
type(ntype),
color(color){
	particleCreateTimerBase = particleCreateTimer;

	srand(time(NULL)); //Obvious -- just sets the random seed [lolnotevenrandomkthxc/c++]

}

void ParticleEmitter::init(sf::Vector2f npos, sf::Vector2f nbaseSpeed, sf::Vector2f nbaseSize, sf::Vector2f nremoveDistance, sf::Vector2f nspeedOffset, float nsizeVariation, float nbaseRotationSpeed, int nparticleCreateTimer, particleEmitterType ntype, sf::Color ncolor){
	pos = npos;
	baseSpeed = nbaseSpeed;
	baseSize = nbaseSize;
	removeDistance = nremoveDistance;
	speedOffset = nspeedOffset;
	sizeVariation = nsizeVariation;
	baseRotationSpeed = nbaseRotationSpeed;
	particleCreateTimer = nparticleCreateTimer;
	type = ntype;
	color = ncolor;
	particleCreateTimerBase = particleCreateTimer;

	srand(time(NULL)); //Obvious -- just sets the random seed [lolnotevenrandomkthxc/c++]

}	

void ParticleEmitter::render(sf::RenderWindow& window){
	for(unsigned int i = 0; i < particles.size(); i++){
		window.draw(particles[i]->shape); // Basic rendering
	}
}

void ParticleEmitter::update(float speed){
	if(baseSpeed.x != speed || baseSpeed.y != speed){
		baseSpeed.x = speed;
		baseSpeed.y = speed;
	}
	for(unsigned int i = 0; i < particles.size(); i++){
		particles[i]->travelledDistanceX++;
		particles[i]->travelledDistanceY++;
		particles[i]->pos.x += particles[i]->speed.x;
	   	particles[i]->pos.y += particles[i]->speed.y;	
		particles[i]->shape.setPosition(particles[i]->pos);
		particles[i]->shape.rotate(baseRotationSpeed);
		if(particles[i]->travelledDistanceX >= removeDistance.x || particles[i]->travelledDistanceY >= removeDistance.y){
			particles.erase(particles.begin() + i);
		}
	}
	if(particleCreateTimer <= 0){
		particleCreateTimer = particleCreateTimerBase;
		createParticle();
	}
	else{
		particleCreateTimer--;
	}
}


void ParticleEmitter::createParticle(){

	sf::Vector2f tempSpeed;
	sf::Vector2f tempSize;

	float speedVar = 10.f;
	float sizeVar = sizeVariation;

	switch(type){
		case(PET_UP): tempSpeed = sf::Vector2f(0, baseSpeed.y * -1); break; // baseSpeed will be written as positive int's always
		case(PET_DOWN): tempSpeed = sf::Vector2f(0, baseSpeed.y); break;
		case(PET_LEFT): tempSpeed = sf::Vector2f(baseSpeed.x * -1, 0); break;
		case(PET_RIGHT): tempSpeed = sf::Vector2f(baseSpeed.x, 0); break;
	}

	int tempSpeedX1 = rand() % (int)speedVar + 0; // Random speed
	int tempSpeedY1 = rand() % (int)speedVar + 0;
	int tempSpeedXN = rand() % 3 + 1; // find if its gonna be negative or not
	int tempSpeedYN = rand() % 3 + 1;

	float tempSpeedX2 = (float)tempSpeedX1 / 10.f; // final speeds divided by ten to get the actual speed variation
	float tempSpeedY2 = (float)tempSpeedY1 / 10.f;

	if(tempSpeedXN == 1) // do the negatives
		tempSpeedX2 *= -1;
	if(tempSpeedYN == 1)
		tempSpeedY2 *= -1;

	int tempSizeX1 = rand() % (int)sizeVar + 0; // same for size
	int tempSizeY1 = rand() % (int)sizeVar + 0;
	int tempSizeXN = rand() % 3 + 1;
	int tempSizeYN = rand() % 3 + 1;

	float tempSizeX2 = (float)tempSizeX1 / 10.f;
	float tempSizeY2 = (float)tempSizeY1 / 10.f;

	if(tempSizeXN == 1)
		tempSizeX2 *= -1;
	if(tempSizeYN == 1)
		tempSizeY2 *= -1;

	tempSpeed = sf::Vector2f(tempSpeedX2, tempSpeedY2); // apply to a final variable
	tempSize = sf::Vector2f(tempSizeX2, tempSizeY2);

	sf::Vector2f finalSpeed = sf::Vector2f(baseSpeed.x += tempSpeedX2, baseSpeed.y += tempSpeedY2); // apply the variation
	sf::Vector2f finalSize = sf::Vector2f(baseSize.x += tempSizeX2, baseSize.y += tempSizeY2); // apply it

	switch(type){
		case(PET_UP): finalSpeed.x *= 0; finalSpeed.x += tempSpeedX2; break;
		case(PET_DOWN): finalSpeed.x *= 0; finalSpeed.x += tempSpeedX2; break;
		case(PET_LEFT): finalSpeed.y *= 0; finalSpeed.y += tempSpeedY2; break;
		case(PET_RIGHT): finalSpeed.y *= 0; finalSpeed.y += tempSpeedY2; break;
	}

	particles.push_back(std::unique_ptr<Particle>(new Particle(pos, finalSpeed, finalSize, color))); // create the particle
}
