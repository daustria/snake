#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "states.h"
class Cell : public sf::Drawable, public std::enable_shared_from_this<Cell>
{

	friend class Grid;
	friend std::ostream &operator<<(std::ostream &, const Cell &);

	public:
		Cell(int w, int h, int topLeftX, int topLeftY);	
		virtual ~Cell() = default;
		void setColour(sf::Color);
		virtual void setState(std::shared_ptr<CellState> newState);

		void snake(Direction d = Direction::Right);
		void normal();
		void food();

		void changeDir(Direction d);
		Direction dir();

	private:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		const int width;
		const int height;
		const int x;
		const int y;

		std::shared_ptr<Cell> up;
		std::shared_ptr<Cell> down;
		std::shared_ptr<Cell> left;
		std::shared_ptr<Cell> right;

		sf::VertexArray vertices;
		std::shared_ptr<CellState> state;
};
std::ostream &operator<<(std::ostream &out, const Cell &c);
#endif //CELL_H
