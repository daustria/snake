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

		virtual bool isSnake(std::shared_ptr<Cell>) { return false; }
		virtual bool isFood(std::shared_ptr<Cell>) { return false; }
		virtual bool isNormal(std::shared_ptr<Cell>) { return false; }
	protected:
		Direction dir_;
};

class Normal : public CellState
{
	public:
		virtual ~Normal() = default;
		virtual void snake(std::shared_ptr<Cell>) override;
		virtual void food(std::shared_ptr<Cell>) override;
		virtual bool isNormal(std::shared_ptr<Cell>) override { return true; }
};

class Snake : public CellState
{
	public:
		virtual ~Snake() = default;
		virtual void normal(std::shared_ptr<Cell>) override;
		Direction dir() override;
		virtual bool isSnake(std::shared_ptr<Cell>) { return true; }
};

class Food : public CellState
{
	public:
		virtual ~Food() = default;
		virtual void normal(std::shared_ptr<Cell>) override;
		virtual void snake(std::shared_ptr<Cell>) override;
		virtual bool isFood(std::shared_ptr<Cell>) { return true; }
};
#endif //CELL_STATE_H
