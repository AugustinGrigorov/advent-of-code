#include "SolutionDay2.h"
#include <sstream>
#include <regex>

SolutionDay2::SolutionDay2(std::ifstream input)
{
  int redCubesBound = 12;
  int greenCubesBound = 13;
  int blueCubesBound = 14;

  for (std::string line; getline(input, line);)
  {
    if (!line.empty())
    {
      int gameId = 0;
      int minRedCubes = 0;
      int minGreenCubes = 0;
      int minBlueCubes = 0;

      std::istringstream is{line};
      std::string discard;
      
      is >> discard;
      is >> gameId;
      is >> discard;
      
      int nextCubeCount = 0;
      std::string nextCubeColor = {};
      bool gameFailed = false;

      while (is >> nextCubeCount && is >> nextCubeColor)
      {
        if (std::regex_search(nextCubeColor, std::regex("red")))
        {
          if (nextCubeCount > redCubesBound) {
            gameFailed = true;
          }
          if (nextCubeCount > minRedCubes) {
            minRedCubes = nextCubeCount;
          }
        }
        if (std::regex_search(nextCubeColor, std::regex("green")))
        {
          if (nextCubeCount > greenCubesBound) {
            gameFailed = true;
          }
          if (nextCubeCount > minGreenCubes) {
            minGreenCubes = nextCubeCount;
          }
        }
        if (std::regex_search(nextCubeColor, std::regex("blue")))
        {
          if (nextCubeCount > blueCubesBound) {
            gameFailed = true;
          }
          if (nextCubeCount > minBlueCubes) {
            minBlueCubes = nextCubeCount;
          }
        }
      }

      if (!gameFailed) {
        validGames += gameId;
      }
      
      cubePowers += minRedCubes * minBlueCubes * minGreenCubes;
    }
  }
}

int SolutionDay2::solve1() const
{
  return validGames;
}

int SolutionDay2::solve2() const
{
  return cubePowers;
}
