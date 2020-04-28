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
			X -= 10;
			rectangle.move(-10,0);
		} else if( X < 500){
			X += 10;
			rectangle.move(10,0);
		}
	}

	int get_X(){
		return X;
	}

	sf::RectangleShape get_rectangle(){
		return rectangle;
	}

private:
	sf::RectangleShape rectangle;
	int X;
};