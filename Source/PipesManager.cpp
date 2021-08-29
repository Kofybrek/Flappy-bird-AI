#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Headers/Global.hpp"
#include "Headers/Pipes.hpp"
#include "Headers/PipesManager.hpp"

PipesManager::PipesManager() :
	y_distribution(PIPE_INDENT, GROUND_Y - GAP_SIZE - PIPE_INDENT),
	generator_timer(GENERATOR_TIMER_DURATION)
{
	
}

void PipesManager::draw(sf::RenderWindow& i_window)
{
	for (Pipes& a : pipes)
	{
		a.draw(i_window);
	}
}

void PipesManager::reset()
{
	generator_timer = GENERATOR_TIMER_DURATION;

	pipes.clear();
}

void PipesManager::update(std::mt19937_64& i_random_engine)
{
	if (0 == generator_timer)
	{
		generator_timer = GENERATOR_TIMER_DURATION;

		pipes.push_back(Pipes(SCREEN_WIDTH, y_distribution(i_random_engine)));
	}

	generator_timer--;

	for (Pipes& a : pipes)
	{
		a.update();
	}

	for (std::vector<Pipes>::iterator a = pipes.begin(); a != pipes.end(); a++)
	{
		//When the pipes go beyond the screen.
		if (1 == a->is_gone())
		{
			//We delete them.
			pipes.erase(a);

			break;
		}
	}
}

std::vector<Pipes> PipesManager::get_pipes()
{
	return pipes;
}