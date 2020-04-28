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
        float timer;
        float delay = 0.3;
		while (window.isOpen() && !is_game_over)
    	{
            check_event();
            check_ball();
            time = clock.getElapsedTime().asMilliseconds();
            timer += time;
            clock.restart();
            if(timer > delay){
                timer = 0;
            }

            window.clear();

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

    void check_ball(){
        if( ball->get_Y() > 780){
            int b_pos = board->get_X();
            if( ball->get_X() >= b_pos && ball->get_X() <= b_pos+100){
                ball->board_touch();
            }
        }
        if(ball->lost()){
            is_game_over = true;
        }
        ball->update();
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
    // Blocks blocks;
    bool is_game_over;
};
