#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Board{
public:
	Board(){
		X = 300;
		rectangle.setSize(sf::Vector2f(100, 10));
		rectangle.setPosition(X, 790);
	}

	~Board(){}

	void update(int flag){
		if(flag == 0 && X > 0){
			X -= 7;
			rectangle.move(-7,0);
		} else if( X < 500){
			X += 7;
			rectangle.move(7,0);
		}
	}

	sf::RectangleShape rectangle;
	int X;
};