#include <vector>
#include "game.h"

sf::Time Game::timePerFrame = sf::seconds(5.0f/60.0f);

Game::Game():mWindow(sf::VideoMode(640, 480), "LoremIpsum")
{

}

void Game::run() 
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while(mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while(timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update();
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{

		switch(event.type)
		{
			case sf::Event::KeyPressed:
				grid.processInput(event.key.code);
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}
void Game::update() 
{
	grid.update();
}

void Game::render() 
{
	mWindow.draw(grid);
	mWindow.display();
}
