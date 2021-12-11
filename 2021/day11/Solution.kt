package day11

import java.io.File
import kotlin.math.max
import kotlin.math.min

class Solution(val file: File) {
    var grid = listOf(listOf<Int>())

    fun countTheNumberOfFlashesInTurns(turns: Int): Int {
        var flashes = 0
        grid = file.readText().trim().split('\n').map { line -> line.map { it.digitToInt() } }
        for (i in 0 until turns) {
            incrementGrid()
            flashes += processFlashes()
        }
        return flashes
    }

    fun getTurnWhenAllFlashSimultaneously(): Int {
        grid = file.readText().trim().split('\n').map { line -> line.map { it.digitToInt() } }
        var turn = 0
        var lastFlashes = 0
        while (lastFlashes != grid.flatten().size) {
            turn++
            incrementGrid()
            lastFlashes = processFlashes()
        }
        return turn
    }

    private fun incrementGrid() {
        grid = grid.map { line ->
            line.map { it + 1 }
        }
    }

    private fun processFlashes(): Int {
        val currentGrid = grid.map { it.toMutableList() }
        var flashes = 0
        while (currentGrid.flatten().any { it > 9 }) {
            currentGrid.forEachIndexed { x, line ->
                line.forEachIndexed { y, num ->
                    if (num > 9) {
                        currentGrid[x][y] = 0
                        flashes++
                        for (i in max(0, x-1) .. min(grid.size - 1, x + 1)) {
                            for (j in max(0, y-1) .. min(line.size -1, y + 1)) {
                                if (currentGrid[i][j] != 0 && (i != x || j != y)) {
                                    currentGrid[i][j]++
                                }
                            }
                        }
                    }
                }
            }
        }
        grid = currentGrid
        return flashes
    }
}