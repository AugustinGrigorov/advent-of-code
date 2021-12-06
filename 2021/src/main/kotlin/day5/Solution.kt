package day5

import java.io.File

class Solution(private val file: File) {

    fun getDangerAreasForStraightLines(): Int {
        val grid = hashMapOf<String, Int>()
        file.forEachLine {
            val points = parsePoints(it)
            plotLine(grid, points[0], points[1], false)
        }
        return getAllDangerAreasOnGrid(grid)
    }

    fun getDangerAreasForAllLines(): Int {
        val grid = hashMapOf<String, Int>()
        file.forEachLine {
            val points = parsePoints(it)
            plotLine(grid, points[0], points[1], true)
        }
        return getAllDangerAreasOnGrid(grid)
    }

    private fun parsePoints(line: String): List<List<Int>> {
        return line.split(" -> ").map { point -> point.split(",").map { coordinate -> coordinate.toInt() } }
    }

    private fun getAllDangerAreasOnGrid(grid: HashMap<String, Int>): Int {
        return grid.values.filter { it > 1 }.size
    }

    private fun plotLine(grid: HashMap<String, Int>, start: List<Int>, end: List<Int>, diagonal: Boolean) {
        if (!diagonal && start[0] != end[0] && start[1] != end[1]) return

        val xIncrement = getIncrement(start[0], end[0])
        val yIncrement = getIncrement(start[1], end[1])

        val current = start.toMutableList()

        grid["${current[0]},${current[1]}"] = grid.getOrDefault("${current[0]},${current[1]}", 0) + 1
        while (current != end) {
            current[0] += xIncrement
            current[1] += yIncrement
            grid["${current[0]},${current[1]}"] = grid.getOrDefault("${current[0]},${current[1]}", 0) + 1
        }

    }

    private fun getIncrement(start: Int, end: Int): Int {
        return if (start == end) {
            0
        } else if (start < end) {
            1
        } else {
            -1
        }
    }
}