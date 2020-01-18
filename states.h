#ifndef CELL_STATES_H
#define CELL_STATES_H
#include <memory>
#include <SFML/Graphics.hpp>
class Cell;
enum class Direction{Up, Down, Left, Right, None};

class CellState
{
	public:
		CellState(Direction d = Direction::None): dir_(d) {}
		virtual ~CellState() = default;

		virtual void changeDir(Direction d) { dir_ = d; }
		virtual Direction dir() { return Direction::None; }

		virtual void snake(std::shared_ptr<Cell>) {}
		virtual void food(std::shared_ptr<Cell>) {} 
		virtual void normal(std::shared_ptr<Cell>) {}
	protected:
		Direction dir_;
};

class Normal : public CellState
{
	public:
		virtual ~Normal() = default;
		virtual void snake(std::shared_ptr<Cell>) override;
		virtual void food(std::shared_ptr<Cell>) override;
};

class Snake : public CellState
{
	public:
		virtual ~Snake() = default;
		virtual void normal(std::shared_ptr<Cell>) override;
		Direction dir() override;
};

class Food : public CellState
{
	public:
		virtual ~Food() = default;
		virtual void normal(std::shared_ptr<Cell>) override;
		virtual void snake(std::shared_ptr<Cell>) override;
};
#endif //CELL_STATE_H
