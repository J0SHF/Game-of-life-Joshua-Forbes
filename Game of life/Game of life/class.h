#pragma once
#include <vector>
class Grid
{
public:
	Grid(int width, int height, int cellSize)
		: rows(height / cellSize), columns(width / cellSize), cellSize(cellSize), cells(rows, std::vector<int>(columns, 0)) {};
	void Draw();
	void SetValue(int row, int column, int value);
	int GetValue(int row, int column);
	bool IsWithinBounds(int row, int column);
	int GetRows() { return rows; }
	int GetColumns() { return columns; }
	void FillRandom();
private:
	int rows;
	int columns;
	int cellSize;
	std::vector<std::vector<int>> cells;
};

class Simulation
{
public:
	Simulation(int width, int height, int cellSize)
		: grid(width, height, cellSize), tempGrid(width, height, cellSize) {
		grid.FillRandom();
	};
	void Draw();
	void SetCellValue(int row, int column, int value);
	int CountLiveNeighbors(int row, int column);
	void Update();
private:
	Grid grid;
	Grid tempGrid;
};