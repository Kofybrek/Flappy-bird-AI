#pragma once

class Pipes
{
	//Are the pipes going up or down?
	bool direction;

	short x;

	//I didn't wanna use float numbers, so I decided to move the pipes after a certain number of frames.
	unsigned char y_movement_timer;

	unsigned short y;
public:
	Pipes(short i_x, unsigned short i_y);

	bool get_direction();
	bool is_gone();

	short get_x();

	unsigned short get_y();

	void draw(sf::RenderWindow& i_window);
	void update();
};