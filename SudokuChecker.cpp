// SudokuChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void print_sudoku(int grid[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		std::cout << "[";
		for (int j = 0; j < 9; j++)
		{
			std::cout << grid[i][j];
			std::cout << " ";
		}
		std::cout << "]" << std::endl;
	}
}

bool is_value_allowed_in_position(int grid[9][9], int value, int pos)
{
	int line = pos / 9;
	int col = pos % 9;

	// check all columns in line
	for (int i = 0; i < 9; i++)
	{
		if (grid[line][i] == value)
			return false;
	}
	// check all lines in col
	for (int i = 0; i < 9; i++)
	{
		if (grid[i][col] == value)
			return false;
	}
	// check the 3X3 subgrid
	int subgrid_num = col / 3;
	subgrid_num = (subgrid_num) + ((line / 3) * 3);
	for (int i = ((subgrid_num / 3) * 3); i < ((subgrid_num / 3) * 3) +3; i++)
	{
		for (int j = ((subgrid_num % 3)*3); j < ((subgrid_num % 3)*3) + 3; j++)
		{
			if (grid[i][j] == value)
			{
				std::cout << "cannot use value " << value << " in position [" << i << "," << j << "]" << std::endl;
				print_sudoku(grid);
				return false;
			}
		}
	}

	return true;
}


int get_next_candidate_position(int grid[9][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (grid[i][j] == 0)
				return (i * 9) + j;
	return -1;
}


bool has_vacant_positions(int grid[9][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (grid[i][j] == 0)
				return true;
	return false;
}

bool is_sudoku_solvable(int grid[9][9])
{
	// If there is no vacant position, this means we filled all and the game has successfully ended!
	if (!has_vacant_positions(grid)) 
		return true;

	// finds a vacant position that we will try to fill with a number
	int next_candidate_pos = get_next_candidate_position(grid);

	// Let's try all numbers (1-9)
	for (int i = 1; i <= 9; i++)
	{
		// Try using "i" in the candidate position
		if (is_value_allowed_in_position(grid, i, next_candidate_pos))
		{
			grid[next_candidate_pos / 9][next_candidate_pos % 9] = i;

			// If solvable, yes! And we return true 
			if (is_sudoku_solvable(grid)) return true;

			// If "i" did not work, clear the position
			grid[next_candidate_pos / 9][next_candidate_pos % 9] = 0;
		}
	}

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int grid[9][9] = { 
		{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
		{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
		{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
		{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
		{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
		{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
		{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
		{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
		{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }
	};

	if (is_sudoku_solvable(grid))
		std::cout << "sudoku is solvable!!!" << std::endl;
	else
		std::cout << "sudoku cannot be solved..." << std::endl;
	
	print_sudoku(grid);

	getchar();

	return 0;
}

