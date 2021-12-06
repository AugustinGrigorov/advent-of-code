package day11

enum class Block {
    EMPTY_SEAT,
    OCCUPIED_SEAT,
    FLOOR
}

enum class Rule {
    ADJACENT,
    LINE_OF_SIGHT
}

class Solution(input: String) {
    private val originalGrid = input.split("\n").map { row ->
        row.toCharArray().map {
            when (it) {
                'L' -> Block.EMPTY_SEAT
                '.' -> Block.FLOOR
                else -> throw Exception("Unsupported input")
            }
        }
    }


    fun getOccupiedAdjacentSeats(): Int {
        return countOccupiedSeats(
            updateGrid(originalGrid, listOf(
                { block, occupiedSeats ->
                    if (block == Block.EMPTY_SEAT && occupiedSeats == 0) {
                        Block.OCCUPIED_SEAT
                    } else block
                },
                { block, occupiedSeats ->
                    if (block == Block.OCCUPIED_SEAT && occupiedSeats >= 4) {
                        Block.EMPTY_SEAT
                    } else block
                }
            ), Rule.ADJACENT)
        )
    }

    fun getOccupiedSeatsInLineOfSight(): Int {
        return countOccupiedSeats(
            updateGrid(originalGrid, listOf(
                { block, occupiedSeats ->
                    if (block == Block.EMPTY_SEAT && occupiedSeats == 0) {
                        Block.OCCUPIED_SEAT
                    } else block
                },
                { block, occupiedSeats ->
                    if (block == Block.OCCUPIED_SEAT && occupiedSeats >= 5) {
                        Block.EMPTY_SEAT
                    } else block
                }
            ), Rule.LINE_OF_SIGHT)
        )
    }

    private fun updateGrid(
        grid: List<List<Block>>,
        operations: List<(Block, Int) -> Block>,
        rule: Rule
    ): List<List<Block>> {
        val updatedGrid = operations.fold(grid) { currentGrid, operation ->
            currentGrid.mapIndexed { rowIndex, row ->
                row.mapIndexed { colIndex, block ->
                    operation(
                        block,
                        when (rule) {
                            Rule.ADJACENT -> getNumberOfOccupiedAdjacentSeats(grid, rowIndex, colIndex)
                            Rule.LINE_OF_SIGHT -> getNumberOfOccupiedSeatsWithinLineOfSight(grid, rowIndex, colIndex)
                        }
                    )
                }
            }
        }

        if (updatedGrid == grid) return updatedGrid

        return updateGrid(updatedGrid, operations, rule)
    }

    private fun countOccupiedSeats(grid: List<List<Block>>): Int {
        return grid.fold(0) { acc, row ->
            acc + row.count {
                it == Block.OCCUPIED_SEAT
            }
        }
    }

    private fun getNumberOfOccupiedAdjacentSeats(grid: List<List<Block>>, row: Int, col: Int): Int {
        var occupied = 0
        for (r in maxOf(row - 1, 0)..minOf(row + 1, grid.size - 1)) {
            for (c in maxOf(col - 1, 0)..minOf(col + 1, grid[row].size - 1)) {
                if ((r != row || c != col) && grid[r][c] == Block.OCCUPIED_SEAT) occupied++
            }
        }
        return occupied
    }


    private fun getNumberOfOccupiedSeatsWithinLineOfSight(grid: List<List<Block>>, row: Int, col: Int): Int {
        var occupied = 0
        for (rowIncrement in -1..1) {
            for (colIncrement in -1..1) {
                if (rowIncrement != 0 || colIncrement != 0) {
                    var currentRow = row + rowIncrement
                    var currentCol = col + colIncrement
                    while (currentRow in grid.indices && currentCol in grid[currentRow].indices && grid[currentRow][currentCol] == Block.FLOOR) {
                        currentRow += rowIncrement
                        currentCol += colIncrement
                    }
                    if (currentRow in grid.indices && currentCol in grid[currentRow].indices && (currentRow != row || currentCol != col) && grid[currentRow][currentCol] == Block.OCCUPIED_SEAT) occupied++
                }
            }
        }
        return occupied
    }
}