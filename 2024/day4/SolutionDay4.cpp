#include "SolutionDay4.h"
#include <iostream>
#include <vector>

std::string solution = "XMAS";

int checkForMatchesPartOne(int const row, int const col, const std::vector<std::vector<char>>& grid) {
  int matches = 0;
  for (int currRow = row - 1; currRow <= row + 1; currRow++) {
    if (currRow < 0 || currRow > grid.size() - 1) {
      continue;
    }
    for (int currCol = col - 1; currCol <= col + 1; currCol++) {
      if (currCol < 0 || currCol > grid[currRow].size() - 1) {
        continue;
      }
      if (currRow == row && currCol == col) {
        continue;
      }
      int const rowDiff = currRow - row;
      int const colDiff = currCol - col;
      bool fullMatch = true;
      for (int i = 1; i < solution.size(); i++) {
        int const nextRow = row + rowDiff * i;
        int const nextCol = col + colDiff * i;
        if (nextRow < 0 || nextRow > grid.size() - 1 || nextCol < 0 || nextCol > grid[nextRow].size() - 1) {
          fullMatch = false;
          break;
        }
        if (grid[nextRow][nextCol] != solution[i]) {
          fullMatch = false;
          break;
        }
      }
      if (fullMatch) {
        matches++;
      }
    }
  }
  return matches;
}

char correspondingChar(char c) {
  if (c == 'M') {
    return 'S';
  }
  if (c == 'S') {
    return 'M';
  }
  return -1;
}

int checkForMatchesPartTwo(int const row, int const col, const std::vector<std::vector<char>>& grid) {
  if (row == 0 || col == 0 || row == grid.size() - 1 || col == grid[0].size() - 1) {
    return 0;
  }
  if (
    correspondingChar(grid[row-1][col-1]) == grid[row+1][col+1] &&
    correspondingChar(grid[row-1][col+1]) == grid[row+1][col-1]
    ) {
    return 1;
  }
  return 0;
}

SolutionDay4::SolutionDay4(std::ifstream input)
{
    int lineNum = 0;
    std::vector<std::vector<char>> puzzleGrid = {};
    for (std::string line; getline(input, line);)
    {
        std::vector<char> row = {};
        if (!line.empty())
        {
          for (char c : line) {
            row.push_back(c);
          }
        }
        puzzleGrid.push_back(row);
        lineNum++;
    }

    for (int row = 0; row < puzzleGrid.size(); row++) {
      for (int col = 0; col < puzzleGrid[row].size(); col++) {
        if (puzzleGrid[row][col] == 'X') {
          partOneSol += checkForMatchesPartOne(row, col, puzzleGrid);
        }
      }
    }

    for (int row = 0; row < puzzleGrid.size(); row++) {
      for (int col = 0; col < puzzleGrid[row].size(); col++) {
        if (puzzleGrid[row][col] == 'A') {
          partTwoSol += checkForMatchesPartTwo(row, col, puzzleGrid);
        }
      }
    }
}

int SolutionDay4::solve1() const
{
    return partOneSol;
}

int SolutionDay4::solve2() const
{
    return partTwoSol;
}
