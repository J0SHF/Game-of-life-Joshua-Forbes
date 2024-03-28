#include <stdio.h>
#include "raylib.h"
#include "class.h"
#include <iostream>



int main() {
	Color red = { 255, 0, 0, 255 };
	Color grey = { 29, 29, 29, 255 };
	const int Cell_Size = 4;

	const  int WINDOW_WIDTH = 1000;
	const  int WINDOW_HEIGHT = 750;
	int Frame = 10;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Josh Game Of Life");
	SetTargetFPS(Frame);
	Simulation simulation{ WINDOW_WIDTH, WINDOW_HEIGHT, Cell_Size };


	while (WindowShouldClose() == false)
	{
		simulation.Update();
		BeginDrawing();
		ClearBackground(grey);
		simulation.Draw();
		EndDrawing();
	}
	CloseWindow();


}
void Simulation::Draw()
{
	grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
	grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
	int liveNeighbors = 0;
	std::vector<std::pair<int, int>> neighborOffsets =
	{
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1},
		{-1,-1},
		{-1, 1},
		{1, -1},
		{1, 1}
	};
	for (const auto& offset : neighborOffsets)
	{
		int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
		int neighborColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
		liveNeighbors += grid.GetValue(neighborRow, neighborColumn);
	}
	return liveNeighbors;

}

void Simulation::Update()
{
	for (int row = 0; row < grid.GetColumns(); row++)
	{
		for (int column = 0; column < grid.GetColumns(); column++)
		{
			int liveNeighbors = CountLiveNeighbors(row, column);
			int cellValue = grid.GetValue(row, column);

			if (cellValue == 1)
			{
				if (liveNeighbors > 3 || liveNeighbors < 2)
				{
					tempGrid.SetValue(row, column, 0);
				}
				else
				{
					tempGrid.SetValue(row, column, 1);
				}
			}
			else
			{
				if (liveNeighbors == 3)
				{
					tempGrid.SetValue(row, column, 1);
				}
				else
				{
					tempGrid.SetValue(row, column, 0);
				}
			}

		}
	}
	grid = tempGrid;
}
void Grid::Draw()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			Color color = cells[row][column] ? Color{ RED } : Color{ 55, 55, 55, 255 };
			DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
		}
	}

}

void Grid::SetValue(int row, int column, int value) {
	if (IsWithinBounds(row, column))
	{
		cells[row][column] = value;
	}
}

int Grid::GetValue(int row, int column)
{
	if (IsWithinBounds(row, column))
	{
		return cells[row][column];
	}
	return 0;
}

bool Grid::IsWithinBounds(int row, int column) {
	if (row >= 0 && row < rows && column >= 0 && column < columns)
	{
		return true;
	}
	return false;
}

void Grid::FillRandom()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			int randomValue = GetRandomValue(0, 4);
			cells[row][column] = (randomValue == 4) ? 1 : 0;
		}
	}
}