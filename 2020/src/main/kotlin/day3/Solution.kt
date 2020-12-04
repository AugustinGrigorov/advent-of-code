package day3

class Solution {
    fun solve(input: String, trajectory: Array<Array<Int>>): Long {
        val slope = Slope(input)
        return trajectory.fold(1) { acc, it ->
            acc * slope.countTreesOnTrajectory(it[0], it[1])
        }
    }
}

private class Slope(input: String) {
    private val trees = hashMapOf<ArrayList<Int>, Boolean>()
    private var rows = 0
    private var columns = 0

    init {
        var row = 0
        var col = -1
        input.forEach {
            if (it == '\n') {
                row++
                if (columns == 0) columns = col + 1
                col = -1
            } else {
                col++
            }
            if (it == '#') {
                trees[arrayListOf(row, col)] = true
            }
        }
        rows = row + 1
    }

    fun hasTree(row: Int, col: Int): Boolean {
        val adjustedCoordinates = arrayListOf(row, col % columns)
        return trees.containsKey(adjustedCoordinates)
    }

    fun countTreesOnTrajectory(moveRows: Int, moveCols: Int): Int {
        var currentRow = 0
        var currentCol = 0
        var totalTrees = 0
        for (i in 0..rows) {
            currentRow += moveRows
            currentCol += moveCols
            if (hasTree(currentRow, currentCol)) totalTrees++
        }
        return totalTrees
    }
}