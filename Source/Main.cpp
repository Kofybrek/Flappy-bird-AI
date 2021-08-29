#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Headers/Pipes.hpp"
#include "Headers/Bird.hpp"
#include "Headers/DrawText.hpp"
#include "Headers/Global.hpp"
#include "Headers/Pipes.hpp"
#include "Headers/PipesManager.hpp"

int main()
{
	//People kept telling me that I should write fewer comments.
	//SO I WILL NOT WRITE COMMENTS AT ALL!!!
	//Jk, I'll just write comments for things that in my opinion need an explanation.

	unsigned short game_speed = 1;
	unsigned short generation = 0;
	unsigned short record_score = 0;

	std::array<Bird, POPULATION_SIZE> birds;

	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());

	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(2 * SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "Flappy Bird", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, 2 * SCREEN_WIDTH, SCREEN_HEIGHT)));

	sf::Sprite background_sprite;
	sf::Sprite ground_sprite;

	sf::Texture background_texture;
	background_texture.loadFromFile("Resources/Images/Background.png");

	sf::Texture ground_texture;
	ground_texture.loadFromFile("Resources/Images/Ground.png");

	PipesManager pipes_manager;

	//Since we're also gonna use rand(), we need to set a random seed.
	srand(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));

	for (Bird& bird : birds)
	{
		bird.generate_weights(random_engine);
	}

	background_sprite.setTexture(background_texture);

	ground_sprite.setPosition(0, GROUND_Y);
	ground_sprite.setTexture(ground_texture);

	previous_time = std::chrono::steady_clock::now();

	while (1 == window.isOpen())
	{
		//Someone said I should use chrono more often, and I did.
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();

						break;
					}
					case sf::Event::KeyPressed:
					{
						switch (event.key.code)
						{
							//Changing the speed by 1 was too slow, so I decided to multiply and divide by 2.

							case sf::Keyboard::Down:
							{
								if (1 < game_speed)
								{
									game_speed /= 2;
								}

								break;
							}
							case sf::Keyboard::Enter:
							{
								game_speed = 1;

								break;
							}
							case sf::Keyboard::Up:
							{
								game_speed *= 2;
							}
						}
					}
				}
			}

			for (unsigned short a = 0; a < game_speed; a++)
			{
				bool restart = 1;

				for (Bird& bird : birds)
				{
					if (0 == bird.get_dead())
					{
						restart = 0;

						break;
					}
				}

				if (0 == restart)
				{
					pipes_manager.update(random_engine);

					for (Bird& bird : birds)
					{
						bird.update(1, pipes_manager.get_pipes());
					}
				}
				else
				{
					//I was born in the wrong generation! (Ba dum tss)
					generation++;

					//std::sort will use the operator functions in the Bird class.
					std::sort(birds.begin(), birds.end(), std::greater());

					//We won't change the weights of the first 2 birds since they're the BEST!
					for (auto a = 2 + birds.begin(); a != birds.end(); a++)
					{
						a->crossover(random_engine, birds[0].get_weights(), birds[1].get_weights());
					}

					for (Bird& bird : birds)
					{
						bird.reset();
					}

					pipes_manager.reset();
				}
			}

			if (FRAME_DURATION > lag)
			{
				unsigned short max_score = std::max_element(birds.begin(), birds.end())->get_score();

				//We make rectangle.
				sf::RectangleShape gui_background(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
				//We make rectangle black.
				gui_background.setFillColor(sf::Color(0, 0, 0));
				//We put rectangle right.
				gui_background.setPosition(SCREEN_WIDTH, 0);
				//Like I said, I'm explaining ONLY the important things.

				if (record_score < max_score)
				{
					record_score = max_score;
				}

				window.clear();
				window.draw(background_sprite);

				pipes_manager.draw(window);

				for (Bird& bird : birds)
				{
					bird.draw(window);
				}

				window.draw(ground_sprite);

				draw_text(1, 1, 0, 0, BIRD_SIZE, std::to_string(max_score), window);

				window.draw(gui_background);

				draw_text(0, 1, 1, SCREEN_WIDTH, 0, "Generation\n" + std::to_string(generation) + "\n\nRecord\nscore\n" + std::to_string(record_score) + "\n\nGame speed\n" + std::to_string(game_speed), window);

				window.display();
			}
		}
	}
}