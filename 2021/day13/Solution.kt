package day13

import java.io.File
import java.lang.Exception

class Solution(file: File) {
    private val pointCoordinates: List<List<Int>>
    private val foldingPoints: List<List<String>>

    init {
        val (points, foldInstructions) = file.readText().trim().split("\n\n")
        pointCoordinates = points.split("\n").map { it.split(",").map(String::toInt) }
        foldingPoints = foldInstructions.split("\n").map { it.replace("fold along ", "").split("=") }
    }

    fun executeFirstInstructionAndGetVisibleDots(): Int {
        val (dimension, location) = foldingPoints[0]
        return fold(dimension, location.toInt(), pointCoordinates).size
    }

    fun executeInstructionsAndGetResult(): String {
        var currentPointCoordinates = pointCoordinates
        foldingPoints.forEach {
            val (dimension, location) = it
            currentPointCoordinates = fold(dimension, location.toInt(), currentPointCoordinates)
        }
        var result = ""
        for (y in 0..currentPointCoordinates.maxOf { it[1] }) {
            for (x in 0..currentPointCoordinates.maxOf { it[0] }) {
                result += if (currentPointCoordinates.contains(listOf(x, y))) "#"
                else " "
            }
            result += "\n"
        }
        return result
    }

    private fun fold(dimension: String, location: Int, currentPointCoordinates: List<List<Int>>): List<List<Int>> {
        return when (dimension) {
            "y" -> {
                currentPointCoordinates.map {
                    if (it[1] < location) it
                    else listOf(it[0], location * 2 - it[1])
                }.distinct()
            }
            "x" -> {
                currentPointCoordinates.map {
                    if (it[0] < location) it
                    else listOf(location * 2 - it[0], it[1])
                }.distinct()
            }
            else -> throw Exception("Unrecognised axis for splitting")
        }
    }
}