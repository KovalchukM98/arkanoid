#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <string>
#include "Board.cpp"
#include "Ball.cpp"

class Scene{
public:
	Scene(){
        is_game_over = true;
    };

	~Scene(){};

	void start(){
        is_game_over = false;
		window.create(sf::VideoMode(600, 800), "Arkanoid");
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(60);
        board = new Board();
        ball = new Ball();

        sf::Clock clock;
        float time;
		while (window.isOpen() && !is_game_over)
    	{
    	    check_event();
            ball->update();

            window.clear();
            time = clock.getElapsedTime().asMilliseconds();
            clock.restart();

            draw();
            window.display();
    	}
        delete board;
	};

private:

    void draw(){
        window.draw(board->rectangle);
        window.draw(ball->circle);
    }

    void check_event(){
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
                window.close();
                is_game_over = true;
                break;

                case sf::Event::KeyPressed:
                check_key(event);
                break;
            }
        }
    }

    void check_key(sf::Event event){
        switch(event.key.code){
            case sf::Keyboard::Escape:
            window.close();
            is_game_over = true;
            break;

            case sf::Keyboard::Left:
            board->update(0);
            break;

            case sf::Keyboard::Right:
            board->update(1);
            break;

            default:
            break;
        }
    }

	sf::RenderWindow window;
    Board *board;
    Ball *ball;
    bool is_game_over;
};
