package day15

import java.io.File
import java.util.*

class Solution(file: File) {
    private val originalGrid: List<List<Int>>

    init {
        originalGrid = file.readText().trim().split("\n").map { line -> line.map { it.digitToInt() } }
    }

    fun findCostForRouteOnOriginalGrid(): Int = findLowestRiskPathInGrid(originalGrid)

    fun findCostForRouteOnExtendedGrid(): Int {
        val modifiedGrid = originalGrid.map { it.toMutableList() }
        modifiedGrid.mapIndexed { index, line ->
            repeat(4) {
                line += originalGrid[index].map { dangerLevel ->
                    val newDanger = (dangerLevel + it + 1) % 9
                    if (newDanger == 0) 9
                    else newDanger
                }
            }
        }
        val gridExtendedToTheRight = modifiedGrid.toMutableList()
        repeat(4) {
            gridExtendedToTheRight += modifiedGrid.map { line ->
                line.map { dangerLevel ->
                    val newDanger = (dangerLevel + it + 1) % 9
                    if (newDanger == 0) 9
                    else newDanger
                }.toMutableList()
            }.toMutableList()
        }
        return findLowestRiskPathInGrid(gridExtendedToTheRight)
    }

    private fun findLowestRiskPathInGrid(grid: List<List<Int>>): Int {
        val gridHeight = grid.size
        val gridWidth = grid[gridHeight - 1].size
        val destX = gridHeight - 1
        val destY = gridWidth - 1
        val openList = PriorityQueue<Point>()
        val bestDistanceToCoordinates = hashMapOf<Pair<Int, Int>, Int>()
        openList.add(Point(0, 0))

        while (!openList.isEmpty()) {
            val currentPoint: Point = openList.peek()
            if (currentPoint.x == destX && currentPoint.y == destY) {
                return currentPoint.distanceFromStart
            }
            openList.remove(currentPoint)

            currentPoint.getNeighbours(gridHeight, gridWidth).forEach { neighbour ->
                val distanceFromStart = currentPoint.distanceFromStart + grid[neighbour.x][neighbour.y]
                val score = distanceFromStart + (destX - neighbour.x) + (destY - neighbour.y)

                if (distanceFromStart < bestDistanceToCoordinates.getOrDefault(neighbour.coordinates, Int.MAX_VALUE)) {
                    bestDistanceToCoordinates[neighbour.coordinates] = distanceFromStart
                    neighbour.distanceFromStart = distanceFromStart
                    neighbour.score = score
                    if (!openList.contains(neighbour)) {
                        openList.add(neighbour)
                    }
                }
            }
        }
        return 0
    }

    data class Point(val x: Int, val y: Int) : Comparable<Point> {
        var distanceFromStart: Int = 0
        var score: Int = Int.MAX_VALUE

        override fun compareTo(other: Point): Int {
            return compareValues(this.score, other.score)
        }

        override fun equals(other: Any?): Boolean {
            val otherPoint = other as Point
            return this.x == otherPoint.x && this.y == otherPoint.y && this.distanceFromStart == otherPoint.distanceFromStart
        }

        val coordinates = Pair(x, y)

        fun getNeighbours(gridHeight: Int, gridWidth: Int): List<Point> {
            val neighbours = mutableListOf<Point>()
            val (x, y) = this
            if (x > 0) neighbours.add(Point(x - 1, y))
            if (y > 0) neighbours.add(Point(x, y - 1))
            if (x < gridHeight - 1) neighbours.add(Point(x + 1, y))
            if (y < gridWidth - 1) neighbours.add(Point(x, y + 1))
            return neighbours
        }
    }
}