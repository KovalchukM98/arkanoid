#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball{
public:
	Ball(){
		X = 300;
		Y = 720;
		circle.setRadius(10.f);
		circle.setPosition(X, Y);
	}

	~Ball(){}

	void update(){
		// circle.setPosition(X, Y);
	}

	sf::CircleShape circle;
	int X;
	int Y;
	// int X_dir = 
};