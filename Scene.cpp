#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <string>

std::mutex mutex;

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

		while (window.isOpen() && !is_game_over)
    	{
    	    check_event();
    	}
	};

    void check_event(){
        sf::Event event;
        while (window.pollEvent(event))
        {
            // пользователь попытался закрыть окно: мы закрываем окно
            switch (event.type){
                case sf::Event::Closed:
                window.close();
                is_game_over = true;
                break;

                case sf::Event::KeyPressed:
                check_key(event);
            }
            // window.clear();
            window.display();
        }
    }

private:

    void check_key(sf::Event event){
        switch(event.key.code){
            case sf::Keyboard::Escape:
            window.close();
            is_game_over = true;
        }
    }

	sf::Window window;
    bool is_game_over;
};
