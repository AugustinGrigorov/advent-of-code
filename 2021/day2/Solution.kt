package day2

import java.io.File

class Solution (private val file: File) {
    fun calculateHorizontalByDepth (): Int {
        var depth = 0
        var horizontal = 0
        file.forEachLine {
            val (direction, amount) = it.split(" ")
            val amountValue = amount.toInt()
            when (direction) {
                "forward" -> horizontal += amountValue
                "down" -> depth += amountValue
                "up" -> depth -= amountValue
            }
        }
        return depth * horizontal
    }

    fun calculateHorizontalByDepthWithAim (): Int {
        var depth = 0
        var horizontal = 0
        var aim = 0
        file.forEachLine {
            val (direction, amount) = it.split(" ")
            val amountValue = amount.toInt()
            when (direction) {
                "forward" -> {
                    horizontal += amountValue
                    depth += aim * amountValue
                }
                "down" -> aim += amountValue
                "up" -> aim -= amountValue
            }
        }
        return depth * horizontal
    }
}