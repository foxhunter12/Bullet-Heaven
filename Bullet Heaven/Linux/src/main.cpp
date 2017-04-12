#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <deque>
#include <ctime>
#include <string>
#include <fstream>

#include "Star.h"
#include "Player.h"
#include "ParticleEmitter.h"
#include "Enemy.h"
#include "Explosion.h"

using namespace std;

std::unique_ptr<Star> makeStar(int w, int h){ // Generates a random star :^)
    int tempX = rand() % w + 1;
    int tempY = 1;

    int startW = rand() % 4 + 1;
    int startH = startW;

    return std::unique_ptr<Star>(new Star(sf::Vector2f((float)tempX, (float)tempY), sf::Vector2f(startW, startH), (rand() % 360 + 0)));
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

    int starGenerateTimerBase = 15; // Couple of variables to control speed on which stars generate. ezpz
    int starGenerateTimer = starGenerateTimerBase;

    std::vector<std::unique_ptr<Star>> stars; // stars list obviously

    std::vector<std::unique_ptr<Explosion>> explosions; // List o' explosions for when enemies die.

    bool hasFocus = true;

    std::vector<std::unique_ptr<Enemy>> enemies;

    float tempSpeed = player.speed + 1;

    int enemyTimer = 110;

    int enemyTimerBase = enemyTimer;

    int score = 0;
    int highScore = 0;

    string scoreString = std::to_string(score);
    string highScoreString = std::to_string(highScore);

    sf::Font font;

    if(!font.loadFromFile("src/INVASION2000.TTF")){
	cout << "Error; font not found \"src/INVASION2000.TTF\"" << endl;
    }    

    sf::Text helpText("Press \"H\" for help", font, 25);
    helpText.setColor(sf::Color(71,198, 45));
    helpText.setPosition(player.pos.x - 100, player.pos.y + player.size.y + 25);

    int helpTextTimerBase = enemyTimer+(enemyTimer/2);
    int helpTextTimer = helpTextTimerBase;

    sf::Text controlsText("WASD - Move\nSpacebar - Shoot\nE - Shield\nR - Restart", font, 20);

    sf::Text restartText("Press \"R\" to restart.", font, 20);
    restartText.setColor(sf::Color::White);
    restartText.setPosition(player.pos.x - 100, player.pos.y + player.size.y + 25);

    sf::Text scoreText("Kills: " + scoreString, font, 20);

    scoreText.setColor(sf::Color::White);

    scoreText.setPosition(sf::Vector2f(5, 10));

    sf::Text highScoreText("HiScore: " + highScoreString, font, 15);

    highScoreText.setColor(sf::Color::White);

    highScoreText.setPosition(sf::Vector2f(5, 32));

    ofstream fout;
    ifstream fin;
    fin.open("src/LOG.SAV");
    if(!fin.is_open()){
	cout << "Error; file not found \"src/LOG.SAV\"" << endl;
    }

    fin >> highScore;
    fin.close();

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

	    for(unsigned int i = 0; i < explosions.size(); i++){
		explosions[i]->render(window);
	    }

	    for(unsigned int i = 0 ; i < enemies.size(); i++){
		enemies[i]->render(window);
	    }

	    player.render(window);

	    window.draw(scoreText);
	    window.draw(highScoreText);
	    if(helpTextTimer > 0 && player.alive) window.draw(helpText);
	    if(!player.alive) window.draw(restartText);

	    window.setMouseCursorVisible(false);
	}


	while(accumulator >= dt){ // UPDATING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    if(inGame){ //INGAME

		accumulator -= dt;

		if(!window.hasFocus() && hasFocus) // If the window isn't clicked on and active, then change that bool!
		    hasFocus = false;
		else if(window.hasFocus() && !hasFocus) // Vice versa!
		    hasFocus = true;

		scoreString = std::to_string(score);
		highScoreString = std::to_string(highScore);

		if(score >= highScore){
		    scoreText.setColor(sf::Color(198, 245, 117));
		    highScoreText.setColor(sf::Color(198, 245, 117));
		}
		else if(score < highScore){
		    scoreText.setColor(sf::Color::White);
		    highScoreText.setColor(sf::Color::White);
		}

		helpTextTimer--;

		scoreText.setString("Kills: " + scoreString);
		highScoreText.setString("HiScore: " + highScoreString);

		if(!player.alive){ //IT'S ALIVEEE!!
		    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			enemies.clear();
			player.bullets.clear();
			stars.clear();
			player.pos = sf::Vector2f((resX/2) - (player.size.x/2), (resY/2) - (player.size.y/2));
			player.alive = true;
			player.lives = 2;
			player.cR = 0;
			player.cG = 0;
			player.cB = 255;
			score = 0;
			helpTextTimer = helpTextTimerBase;
			scoreText.setCharacterSize(20);
			highScoreText.setCharacterSize(15);
			highScoreText.setPosition(5, 32);
			scoreText.setColor(sf::Color::White);
			highScoreText.setColor(sf::Color::White);
			player.shieldTimer = player.shieldTimerBase;
			player.shieldCooldown = 0;
			player.playerShape.setFillColor(sf::Color(player.cR, player.cG, player.cB));
			player.playerLifeAnimationTimer = player.playerLifeAnimationTimerBase;
		    }
		}

		starHandler(stars, starGenerateTimer, starGenerateTimerBase, resX, resY); // Updates stars
		for(unsigned int i = 0; i < stars.size(); i++){
		    stars[i]->pos.y += player.speed;
		    stars[i]->starShape.setPosition(stars[i]->pos);
		    if(stars[i]->pos.y >= resY)
			stars.erase(stars.begin() + i); // Erases stars if ^ (below screen)
		}

		player.update(view, resX, resY, hasFocus);

		for(unsigned int j = 0; j < explosions.size(); j++){
		    explosions[j]->update();
		    if(explosions[j]->shapes.size() <= 0 && explosions[j]->amountMade >= explosions[j]->amount){
			explosions.erase(explosions.begin() + j);
		    }
		}

		for(unsigned int i = 0; i < enemies.size(); i++){
		    enemies[i]->update(player.bullets, player.pos, player.alive, score);
		    if(!enemies[i]->alive){
			std::unique_ptr<Explosion> explosion = std::make_unique<Explosion>(enemies[i]->pos);

			if(!enemies[i]->exploded){
			    explosions.push_back(std::move(explosion));
			    enemies[i]->exploded = true;
			}

		    }

		    for(unsigned int o = 0; o < enemies[i]->bullets.size(); o++){ // Enemy bullets -> player collisions and handling
			if(player.shieldBool == false){
			    if(player.alive && enemies[i]->bullets[o]->shape.getGlobalBounds().intersects(player.playerShape.getGlobalBounds())){
				enemies[i]->bullets.erase(enemies[i]->bullets.begin() + o);
				if(player.lives <= 1){ 
				    if(score > highScore){
					fout.open("src/LOG.SAV");
					if(!fout.is_open()){
					    cout << "Error; file not found \"src/LOG.SAV\"" << endl;
					}
					highScore = score;
					fout << highScore;
					fout.close();
				    }
				    int tempSize = scoreText.getCharacterSize();
				    scoreText.setCharacterSize(50);
				    highScoreText.setCharacterSize(45);
				    highScoreText.move(0, scoreText.getCharacterSize() - tempSize);
				    scoreText.setColor(sf::Color(249, 154, 0));
				    highScoreText.setColor(sf::Color(249, 154, 0));

				    player.alive = false;
				}
				else if(player.lives == 2) player.lives --;
			    }
			}
			else{
			    if(player.alive && enemies[i]->bullets[o]->shape.getGlobalBounds().intersects(player.shield.shape.getGlobalBounds())){
				enemies[i]->bullets.erase(enemies[i]->bullets.begin() + o);
			    }
			}
		    }
		}

		if(player.lives == 1){
		    if(player.colorBool){
			player.cR += 5;
			if(player.cR >= 255){
			    player.colorBool = false;
			}
		    }
		    else{
			player.cR -= 5;
			if(player.cR <= 0){
			    player.colorBool = true;
			}
		    }
		    player.playerShape.setFillColor(sf::Color(player.cR, player.cG, player.cB));
		    if(player.playerLifeAnimationTimer > 0){
			player.playerLifeAnimationTimer--;
			if(player.playerLifeAnimationTimer == 25 || player.playerLifeAnimationTimer == 15){
			    player.canRender = false;
			}
			else if(player.playerLifeAnimationTimer == 20 || player.playerLifeAnimationTimer == 10){
			    player.canRender = true;
			}
		    }
		}

		if(enemyTimer <= 0){
		    int enemyChoice = rand() % 3 + 0;
		    if(enemyChoice == 1){
			enemies.push_back(std::unique_ptr<Enemy>(new Enemy (sf::Vector2f(15, 20), rand() % (int)tempSpeed + 1, sf::Color::Red, sf::Color::White, 1.f, E_DOWN, rand() % 75 + 20)));
			enemyTimer = enemyTimerBase;
		    }	
		    else if(enemyChoice == 2){
			enemies.push_back(std::unique_ptr<Enemy>(new Enemy(sf::Vector2f(20, 15), rand() % (int)tempSpeed + 1, sf::Color::Red, sf::Color::White, 1.f, E_RIGHT, rand() % 75 + 20)));
			enemyTimer = enemyTimerBase;
		    }		
		    else{
			enemies.push_back(std::unique_ptr<Enemy>(new Enemy(sf::Vector2f(20, 15), rand() % (int)tempSpeed + 1, sf::Color::Red, sf::Color::White, 1.f, E_LEFT, rand() % 75 + 20)));
			enemyTimer = enemyTimerBase;
		    }
		}
		else{
		    enemyTimer--;
		}

	    }
	}
	window.setFramerateLimit(60);

	window.display();
    }
    return 0;
}
