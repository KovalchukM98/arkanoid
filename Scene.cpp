#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
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
        generate_field();

        // sf::SoundBuffer buffer;
        // sf::Sound music;
        // if (!music.openFromFile("training.wav")){
        //     return;
        // }
        // music.play();
		while (window.isOpen() && !is_game_over)
    	{
            check_event();
            check_ball();

            window.clear();
            draw();
            window.display();
    	}
        sf::Clock clock;
        float time;
        float timer;
        float delay = 1.0;
        while(timer > delay){
            time = clock.getElapsedTime().asSeconds();
            timer += time;
            clock.restart();
        }
        delete board;
        delete ball;
	};

private:

    void draw(){
        window.draw(board->get_rectangle());
        window.draw(ball->get_circle());
        draw_field();
    }

    void draw_field(){
        for(int i = 0 ; i < 600/60 ; i++){
            for(int j = 0 ; j < 600/40 ; j++){
                if(field[i][j] == true){
                    sf::RectangleShape rectangle;
                    rectangle.setPosition(i*60+15, j*40+15);
                    rectangle.setSize(sf::Vector2f(30, 10));
                    rectangle.setFillColor(sf::Color(250,0,0));
                    rectangle.setOutlineThickness(15.f);
                    rectangle.setOutlineColor(sf::Color(80,220,50));
                    window.draw(rectangle);
                }
            }
        }
    }

    void check_ball(){
        if( ball->get_Y() > 780){
            int b_pos = board->get_X();
            if( ball->get_X() >= b_pos && ball->get_X() <= b_pos+100){
                ball->Y_touch();
            }
        }
        if(ball->lost()){
            is_game_over = true;
        }
        search_collisions(ball->get_X(), ball->get_Y());
        ball->update();
    }

    void search_collisions(int X, int Y){
        if(Y >= 590)
            return;
        if(field[(X+10)/60][Y/40] == true){
            field[(X+10)/60][Y/40] = false;
            ball->X_touch();
        }
        if(field[(X-10)/60][Y/40] == true){
            field[(X-10)/60][Y/40] = false;
            ball->X_touch();
        }
        if(field[X/60][(Y+10)/40] == true){
            field[X/60][(Y+10)/40] = false;
            ball->Y_touch();
        }
        if(field[X/60][(Y-10)/40] == true){
            field[X/60][(Y-10)/40] = false;
            ball->Y_touch();
        }
    }

    void check_event(){
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){
                case sf::Event::Closed:
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

    void generate_field(){
        for(int i = 0 ; i < 600/60 ; i++){
            for(int j = 0 ; j < 600/40 ; j++)
                if(rand() % 2 == 1)
                    field[i][j] = true;
                else
                    field[i][j] = false;
        }
    }

	sf::RenderWindow window;
    Board *board;
    Ball *ball;
    bool field[600/60][600/40];
    bool is_game_over;
};
