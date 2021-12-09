package day9

import java.io.File

class Solution (file: File) {
    private val grid: List<List<Int>>
    private val visitedPoints = HashMap<Pair<Int, Int>, Boolean>()

    init {
        grid = file.readText().trim().split("\n").map { line ->
            line.map { Character.getNumericValue(it) }
        }
    }

    fun findRiskLevel (): Int {
        var riskLevel = 0
        grid.forEachIndexed { x, line ->
            line.forEachIndexed { y, candidate ->
                if (getAdjacentPoints(x,y).all { candidate < grid[it.first][it.second] }) riskLevel += candidate + 1
            }
        }
        return riskLevel
    }

    fun findProductOfThreeBiggestBasins () : Long {
        visitedPoints.clear()
        val basinSizes = mutableListOf<Long>()
        grid.forEachIndexed { x, line ->
            line.forEachIndexed { y, candidate ->
                if (candidate !=9 && visitedPoints[Pair(x,y)] != true) basinSizes.add(getSizeOfBasin(x,y).toLong())
            }
        }
        return basinSizes.sortedDescending().take(3).reduce { acc, i -> acc * i }
    }

    private fun getSizeOfBasin (x: Int, y: Int): Int {
        if (visitedPoints[Pair(x, y)] == true || grid[x][y] == 9) return 0
        visitedPoints[Pair(x, y)] = true
        return 1 + getAdjacentPoints(x, y).sumOf { getSizeOfBasin(it.first, it.second) }
    }

    private fun getAdjacentPoints (x: Int, y: Int) : List<Pair<Int, Int>> {
        val adjacentPoints = mutableListOf<Pair<Int, Int>>()
        if (x-1 > -1) adjacentPoints.add(Pair(x-1, y))
        if (x+1 < grid.size) adjacentPoints.add(Pair(x+1, y))
        if (y-1 > -1) adjacentPoints.add(Pair(x, y-1))
        if (y+1 < grid[x].size) adjacentPoints.add(Pair(x, y+1))
        return adjacentPoints.toList()
    }
}