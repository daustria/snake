#include "states.h"
#include "cell.h"

void Snake::normal(std::shared_ptr<Cell> cp)
{
	cp->setColour(sf::Color::Black);
	auto normalState = std::make_shared<Normal>();
	std::shared_ptr<CellState> newState = normalState;
	cp->setState(newState);
}

Direction Snake::dir() { return dir_; }

void Normal::snake(std::shared_ptr<Cell> cp)
{
	cp->setColour(sf::Color::Blue);
	auto snakeState = std::make_shared<Snake>();
	std::shared_ptr<CellState> newState = snakeState;
	cp->setState(newState);
}

void Normal::food(std::shared_ptr<Cell> cp)
{
	cp->setColour(sf::Color::Red);
	auto foodState = std::make_shared<Food>();
	std::shared_ptr<CellState> newState = foodState;
	cp->setState(newState);
}

void Food::normal(std::shared_ptr<Cell> cp)
{
	cp->setColour(sf::Color::Black);
	auto normalState = std::make_shared<Normal>();
	std::shared_ptr<CellState> newState = normalState;
	cp->setState(newState);
}

void Food::snake(std::shared_ptr<Cell> cp)
{
	cp->setColour(sf::Color::Blue);
	auto snakeState = std::make_shared<Snake>();
	std::shared_ptr<CellState> newState = snakeState;
	cp->setState(newState);
}
