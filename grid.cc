#include <iostream>
#include "grid.h"

Grid::Grid(): tileWidth(32), tileHeight(24), width(20), height(20), size(400)
{
	cells.reserve(size);
	populateCells();
	setupNeighbours();
	spawnSnake();
	spawnFood();
}

void Grid::populateCells()
{
	for(int i = 0; i < size; ++i)
	{
		int row = i/height;
		int col = i%width;

		int x = col*tileWidth;
		int y = row*tileHeight;

		auto cp = std::make_shared<Cell>(tileWidth, tileHeight, x, y);
		auto defaultState = std::make_shared<Normal>();
		cp->setState(defaultState);
		cells.push_back(cp);
	}
}

void Grid::setupNeighbours()
{
	for(int i = 0; i < size; ++i)
	{
		if(i - width >= 0)
			cells[i]->up = cells[i-width];
		if(i + width < size)
			cells[i]->down = cells[i+width];
		if((i-1)/height == i/height && i-1 > 0) 
			cells[i]->left = cells[i-1];
		if((i+1)/height == i/height)
			cells[i]->right = cells[i+1];
	}
}

void Grid::spawnSnake()
{
	snakeIndices.push_back(106);
	snakeIndices.push_back(105);
	snakeIndices.push_back(104);
	snakeIndices.push_back(103);
	snakeIndices.push_back(102);

	cells[106]->snake();
	cells[105]->snake();
	cells[104]->snake();
	cells[103]->snake();
	cells[102]->snake();
}

void Grid::spawnFood()
{
	int index = -1;
	while(1)
	{
		bool onSnakeCell = false;
		index = rand() % size;
		for(const auto &it : snakeIndices)
			if (index == it) {
				onSnakeCell = true;
				break;
			}
		if(!onSnakeCell)
			break;
	}

	foodIndex = index;
	cells[foodIndex]->food();
}

Direction inverseDirection(Direction d)
{
	Direction inverse = Direction::None;

	switch(d)
	{
		case Direction::Up:
			inverse = Direction::Down;
			break;
		case Direction::Down:
			inverse = Direction::Up;
			break;
		case Direction::Left:
			inverse = Direction::Right;
			break;
		case Direction::Right:
			inverse = Direction::Left;
			break;
		case Direction::None:
			inverse = Direction::None;
			break;
	}
	return inverse;
}

void Grid::addSegment()
{
	int len = snakeIndices.size();
	int tailIndex = snakeIndices[len-1];
	auto tail = cells[tailIndex];

	Direction oldTailDirection = tail->dir();
	Direction inverse = inverseDirection(oldTailDirection);

	int newTailIndex = getCellIndex(tail->x, tail->y, inverse);
	cells[newTailIndex]->snake(oldTailDirection);
	snakeIndices.push_back(newTailIndex);

}

void Grid::processInput(sf::Keyboard::Key key)
{
	auto head = cells[snakeIndices[0]];

	if (key == sf::Keyboard::W && head->dir() != Direction::Down) { 
		head->changeDir(Direction::Up);
	} else if (key == sf::Keyboard::S && head->dir() != Direction::Up) {
		head->changeDir(Direction::Down);
	} else if (key == sf::Keyboard::A && head->dir() != Direction::Right) {
		head->state->changeDir(Direction::Left);
	} else if (key == sf::Keyboard::D && head->dir() != Direction::Left) {
		head->changeDir(Direction::Right);
	}
}

void Grid::update()
{
	moveSnake();
}

int Grid::getCellIndex(int x, int y, Direction d) const
{
	int row = y/tileHeight;
	int col = x/tileWidth;
	int index = row*width + col;
	int retVal = -1;
	
	switch(d)
	{
		case Direction::None:
			retVal = index;
			break;
		case Direction::Up:
			retVal = index - width;
			break;
		case Direction::Down:
			retVal = index + width;
			break;
		case Direction::Left:
			retVal = index - 1;
			break;
		case Direction::Right:
			retVal = index + 1;
			break;
	}
	return retVal;
}

void Grid::moveSnake()
{
	Direction lastDir = cells[snakeIndices[0]]->dir();
	bool grow = false;

	for (auto &i : snakeIndices)
	{
		auto snakeCell = cells[i];
		int otherIndex = getCellIndex(snakeCell->x, snakeCell->y, snakeCell->dir());
		auto otherCell = cells[otherIndex];

		if(otherIndex == foodIndex) {
			grow = true;
			spawnFood();
		}

		otherCell->snake(lastDir);
		lastDir = snakeCell->dir();
		snakeCell->normal();
		i = otherIndex;
	}

	if(grow)
		addSegment();
}


void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
	for (auto &it : cells)
		(*it).draw(target, states);
}
