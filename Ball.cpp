#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Ball{
public:
	Ball(){
		X_dir = -3;
		Y_dir = -3;
		X = 300;
		Y = 720;
		circle.setRadius(10.f);
		circle.setPosition(X, Y);
		is_losed = false;
	}

	~Ball(){}

	void update(){
		if(X + X_dir > 590){
			X_dir *= -1;
		}
		if(X + X_dir < 10){
			X_dir *= -1;
		}
		if(Y + Y_dir > 800){
			is_losed = true;
		}
		if(Y + Y_dir < 10){
			Y_dir *= -1;
		}
		X += X_dir;
		Y += Y_dir;
		circle.move(X_dir, Y_dir);
	}

	bool lost(){
		return is_losed;
	}

	int get_X(){
		return X;
	}

	int get_Y(){
		return Y;
	}

	void Y_touch(){
		Y_dir *= -1;
	}

	void X_touch(){
		X_dir *= -1;
	}

	sf::CircleShape get_circle(){
		return circle;
	}
	
private:
	sf::CircleShape circle;
	int X;
	int Y;
	int X_dir;
	int Y_dir;
	bool is_losed;
};