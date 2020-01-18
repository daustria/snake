#include "cell.h"
#include "states.h"

Cell::Cell(int w, int h, int topLeftX, int topLeftY): 
	width(w), height(h), x(topLeftX), y(topLeftY), vertices(sf::Quads, 4)
{
	vertices[0].position = sf::Vector2f(x, y);
	vertices[1].position = sf::Vector2f(x + width, y);
	vertices[2].position = sf::Vector2f(x+width, y+height);
	vertices[3].position = sf::Vector2f(x, y+height);

	setColour(sf::Color::Black);
}

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const { target.draw(vertices); }

void Cell::setColour(sf::Color c)
{
	for(int i = 0; i < 4; ++i)
		vertices[i].color = c;
}

void Cell::setState(std::shared_ptr<CellState> newState) { state = newState; }

void Cell::snake(Direction d)
{
	state->snake(shared_from_this());
	state->changeDir(d);
}

void Cell::food() 
{
	state->food(shared_from_this());
}

void Cell::normal()
{
	state->normal(shared_from_this());
}

void Cell::changeDir(Direction d) { state->changeDir(d); }

Direction Cell::dir() { return state->dir(); }

std::ostream &operator<<(std::ostream &out, const Cell &c)
{
	out << "x : " << c.x << ", y : " << c.y;
	return out;
}
