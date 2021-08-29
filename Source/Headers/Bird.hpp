#pragma once

class Bird
{
	bool dead;

	float vertical_speed;
	float y;

	//Why is x short and y float?
	//Because gravity isn't horizontal.
	short x;

	unsigned fitness;

	unsigned short score;

	std::uniform_int_distribution<unsigned short> mutation_distribution;

	//This is the range in which the weights can be.
	std::uniform_real_distribution<float> node_distribution;

	//I didn't know how to use arrays here.
	std::vector<std::vector<std::vector<float>>> weights;
public:
	Bird();

	//I'm pretty sure some of you will hate me for naming this function like that.
	//"iT DoEsN'T MaKe aNy sEnSe!"
	//"iT MaKeS ThE CoDe hArD To uNdErStAnD!"
	//"wHy cAn't yOu bE NoRmAl?"
	bool do_ai_stuff(std::vector<Pipes> i_pipes);
	bool get_dead();
	bool operator>(Bird& i_bird);
	bool operator<(Bird& i_bird);

	//The difference between the bird and the gap.
	float get_gap_difference(std::vector<Pipes> i_pipes);
	float get_y();

	unsigned get_fitness();

	unsigned short get_score();

	void crossover(std::mt19937_64& i_random_engine, const std::vector<std::vector<std::vector<float>>>& i_bird_0_weights, const std::vector<std::vector<std::vector<float>>>& i_bird_1_weights);
	void draw(sf::RenderWindow& i_window);
	void generate_weights(std::mt19937_64& i_random_engine);
	void reset();
	//We'll use i_move to move the bird when it's dead and there are still birds alive.
	void update(bool i_move, std::vector<Pipes> i_pipes);

	std::vector<std::vector<std::vector<float>>> get_weights();
};