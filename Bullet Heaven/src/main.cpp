#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <deque>
#include <ctime>
#include <string>
#include <fstream>
#include <memory>

#include "Star.h"
#include "Player.h"
#include "ParticleEmitter.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Button.h"

using namespace std;

Star makeStar(int w, int h){ // Generates a random star :^)
    int tempX = rand() % w + 1;
    int tempY = 1;

    int startW = rand() % 4 + 1;
    int startH = startW;

    Star star(sf::Vector2f((float)tempX, (float)tempY), sf::Vector2f(startW, startH), (rand() % 360 + 0));
    return star;
}

void starHandler(std::vector<Star>& stars, int& sgt, int& sgtb, int w, int h){ // Handles all star events
    if(sgt > 0){
	sgt--;
    }
    else{
	stars.push_back(makeStar(w, h));
	sgt = sgtb;
    }

}

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight){

    float windowRatio = windowWidth / (float)windowHeight;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if(windowRatio < viewRatio)
	horizontalSpacing = false;

    if(horizontalSpacing){
	sizeX = viewRatio / windowRatio;
	posX = (1 - sizeX) / 2.f;
    }
    else{
	sizeY = windowRatio / viewRatio;
	posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}

int main(int argc, char* argv[]){

    int resX = 800;
    int resY = 600;

    srand(time(NULL)); //Obvious -- just sets the random seed [lolnotevenrandomkthxc/c++]

    bool inGame = false;
    bool inMenu = true;

    float dt = 1.f/40.f; // Modify this to change physics rate.
    float accumulator = 0.f;

    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(resX, resY), "Bullet Heaven"); //Basic window properties

    bool hasFocus = true;

    sf::View view;
    view.setSize(resX, resY);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    view = getLetterboxView(view, resX, resY);

    Player player(sf::Vector2f(0, 0), sf::Vector2f(20, 35), sf::Color::Blue);

    player.pos = sf::Vector2f((resX/2) - (player.size.x/2), (resY/2) - (player.size.y/2));

    int starGenerateTimerBase = 15; // Couple of variables to control speed on which stars generate. ezpz
    int starGenerateTimer = starGenerateTimerBase;

    sf::RectangleShape background;

    background.setFillColor(sf::Color::Transparent);
    background.setOutlineThickness(1);
    sf::Color backgroundColor = sf::Color(40, 190, 40);
    background.setOutlineColor(backgroundColor);
    background.setPosition(sf::Vector2f(1, 1));
    background.setSize(sf::Vector2f(resX-2, resY-2));

    std::vector<Star> stars; // stars list obviously

    std::vector<Explosion> explosions; // List o' explosions for when enemies die.

    std::vector<Enemy> enemies;

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
    controlsText.setPosition(player.pos.x - 100, player.pos.y + player.size.y + 50);

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

    bool helpOpen = false;

    int helpTimerBase = 10;
    int helpTimer = helpTimerBase;

    std::vector<Button> buttons;
    
    sf::Text titleText("Bullet Heaven", font, 60);
    
    titleText.setColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(resX/2 - 225, 20));

    Button playButton(sf::Vector2f(resX/2 - 100, resY/2), sf::Color(25, 25, 25), sf::Color(200, 200, 200), 5.f, sf::Vector2f(200, 50), "Start");
    Button quitButton(sf::Vector2f(resX/2 - 100, playButton.pos.y + playButton.size.y + 20), sf::Color(25, 25, 25), sf::Color(200, 50, 25), 5.f, sf::Vector2f(200, 50), "Quit");
    playButton.text.setFont(font);
    quitButton.text.setFont(font);

    playButton.selected = true;

    buttons.push_back(playButton);
    buttons.push_back(quitButton);

    sf::RectangleShape selectionShape1;
    sf::RectangleShape selectionShape2;

    selectionShape1.setFillColor(sf::Color::Transparent);
    selectionShape1.setOutlineColor(sf::Color::White);
    selectionShape1.setOutlineThickness(7.f);
    selectionShape1.setSize(sf::Vector2f(25, 25));
    selectionShape2.setFillColor(sf::Color::Transparent);
    selectionShape2.setOutlineColor(sf::Color::White);
    selectionShape2.setOutlineThickness(7.f);
    selectionShape2.setSize(sf::Vector2f(25, 25));

    selectionShape1.setPosition(playButton.pos.x - 42, playButton.pos.y + ((float)(25/2)));
    selectionShape2.setPosition(playButton.pos.x + playButton.size.x + 17, playButton.pos.y + ((float)(25/2)));

    sf::Text pauseText("Paused", font, 45);
    pauseText.setColor(sf::Color::White);
    pauseText.setPosition(sf::Vector2f(resX/2 - 85, 150));

    bool drawPauseText = false;

    while(window.isOpen()){ window.setView(view);

	sf::Event event;

	while(window.pollEvent(event)){
	    if(event.type == sf::Event::Closed)
		window.close();

	    if(event.type == sf::Event::Resized){
		view = getLetterboxView(view, event.size.width, event.size.height);
		//background.setSize(sf::Vector2f(view.getSize().x, view.getSize().y));
	    }

	    if(event.type == sf::Event::LostFocus)
		hasFocus = false;
	    else if(event.type == sf::Event::GainedFocus)
		hasFocus = true;
	}

	accumulator += clock.getElapsedTime().asSeconds();
	clock.restart();

	window.clear(); // RENDERING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if(inMenu){
	    for(unsigned int i = 0; i < stars.size(); i++){
		stars[i].render(stars, window);
	    }

	    for(unsigned int i = 0; i < buttons.size(); i++){
		buttons[i].render(window);
	    }
	    window.draw(titleText);
	    window.draw(selectionShape1);
	    window.draw(selectionShape2);

	    if(drawPauseText)
		window.draw(pauseText);

	}
	if(inGame){
	    window.draw(background);

	    for(unsigned int i = 0; i < stars.size(); i++){
		stars[i].render(stars, window);
	    }

	    for(unsigned int i = 0; i < explosions.size(); i++){
		explosions[i].render(window);
	    }

	    for(unsigned int i = 0 ; i < enemies.size(); i++){
		enemies[i].render(window);
	    }

	    player.render(window);

	    window.draw(scoreText);
	    window.draw(highScoreText);
	    if(helpTextTimer > 0 && player.alive) 
		window.draw(helpText);
	    if(!player.alive)
		window.draw(restartText);

	    if(helpOpen && player.alive && helpTextTimer <= (helpTextTimerBase/2))
		window.draw(controlsText);

	}

	window.setMouseCursorVisible(false);

	while(accumulator >= dt){ // UPDATING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    accumulator -= dt;
	    if(inMenu){
		for(unsigned int i = 0; i < buttons.size(); i++){
		    buttons[i].update();
		}
		if(playButton.isPressed()){
		    inGame = true;
		    inMenu = false;
		}
		if(quitButton.isPressed())
		   window.close(); 

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		    if(playButton.selected){
			selectionShape1.setPosition(quitButton.pos.x - 42, quitButton.pos.y + ((float)(25/2)));
			selectionShape2.setPosition(quitButton.pos.x + quitButton.size.x + 17, quitButton.pos.y + ((float)(25/2)));
			playButton.selected = false;
			quitButton.selected = true;
		    }
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		    if(quitButton.selected){
			selectionShape1.setPosition(playButton.pos.x - 42, playButton.pos.y + ((float)(25/2)));
			selectionShape2.setPosition(playButton.pos.x + playButton.size.x + 17, playButton.pos.y + ((float)(25/2)));
			quitButton.selected = false;
			playButton.selected = true;
		    }
		}

		starHandler(stars, starGenerateTimer, starGenerateTimerBase, resX, resY); // Updates stars
		for(unsigned int i = 0; i < stars.size(); i++){
		    stars[i].pos.y += player.speed;
		    stars[i].starShape.setPosition(stars[i].pos);
		    if(stars[i].pos.y >= resY)
			stars.erase(stars.begin() + i); // Erases stars if ^ (below screen)
		}

	    }
	    if(inGame){ //INGAME

		scoreString = std::to_string(score);
		highScoreString = std::to_string(highScore);

		backgroundColor.r++; // Random colors for the game's outline.
		backgroundColor.g+=2;
		backgroundColor.b+=3;
		background.setOutlineColor(backgroundColor);

		starHandler(stars, starGenerateTimer, starGenerateTimerBase, resX, resY); // Updates stars
		for(unsigned int i = 0; i < stars.size(); i++){
		    stars[i].pos.y += player.speed;
		    stars[i].starShape.setPosition(stars[i].pos);
		    if(stars[i].pos.y >= resY)
			stars.erase(stars.begin() + i); // Erases stars if ^ (below screen)
		}

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


		player.update(view, resX, resY, hasFocus);

		for(unsigned int j = 0; j < explosions.size(); j++){
		    explosions[j].update();
		    if(explosions[j].shapes.size() <= 0 && explosions[j].amountMade >= explosions[j].amount){
			explosions.erase(explosions.begin() + j);
		    }
		}

		for(unsigned int i = 0; i < enemies.size(); i++){
		    enemies[i].update(player.bullets, player.pos, player.alive, score);
		    if(!enemies[i].alive){
			Explosion explosion(enemies[i].pos);

			if(!enemies[i].exploded){
			    explosions.push_back(explosion);
			    enemies[i].exploded = true;
			}

			if(enemies[i].bullets.size() == 0){
			    enemies.erase(enemies.begin() + i);
			}

		    }

		    for(unsigned int o = 0; o < enemies[i].bullets.size(); o++){ // Enemy bullets . player collisions and handling
			if(player.shieldBool == false){
			    if(player.alive && enemies[i].bullets[o].shape.getGlobalBounds().intersects(player.playerShape.getGlobalBounds())){
				enemies[i].bullets.erase(enemies[i].bullets.begin() + o);
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
			    if(player.alive && enemies[i].bullets[o].shape.getGlobalBounds().intersects(player.shield.shape.getGlobalBounds())){
				enemies[i].bullets.erase(enemies[i].bullets.begin() + o);
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
			Enemy enemy(sf::Vector2f(15, 20), rand() % (int)tempSpeed + 1, sf::Color::Red, sf::Color::White, 1.f, E_DOWN, rand() % 75 + 20);
			enemies.push_back(enemy);
			enemyTimer = enemyTimerBase;
		    }	
		    else if(enemyChoice == 2){
			Enemy enemy(sf::Vector2f(20, 15), rand() % (int)tempSpeed + 1, sf::Color::Red, sf::Color::White, 1.f, E_RIGHT, rand() % 75 + 20);
			enemies.push_back(enemy);
			enemyTimer = enemyTimerBase;
		    }		
		    else{
			Enemy enemy(sf::Vector2f(20, 15), rand() % (int)tempSpeed + 1, sf::Color::Red, sf::Color::White, 1.f, E_LEFT, rand() % 75 + 20);
			enemies.push_back(enemy);
			enemyTimer = enemyTimerBase;
		    }
		}
		else{
		    enemyTimer--;
		}

		helpTimer--;

		if(window.getSize().x <= 800)
		    window.setSize(sf::Vector2u(800, 600));
		if(window.getSize().y <= 600)
		    window.setSize(sf::Vector2u(800, 600));

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
		    if(!helpOpen && helpTimer <= 0){
			helpOpen = true;
			helpTimer = helpTimerBase;
		    }
		    else if(helpOpen && helpTimer <= 0){
			helpOpen = false;
			helpTimer = helpTimerBase;
		    }
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		    drawPauseText = true;
		    inGame = false;
		    inMenu = true;
		}

	    }
	}
	window.setFramerateLimit(60);

	window.display();
    }
    return 0;
}
