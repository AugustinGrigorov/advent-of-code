package day12

import kotlin.math.abs

class Solution(input: String) {
    private val directions = arrayOf("N", "E", "S", "W")
    private var currentDirectionIndex = 1
    private val shipCoordinates = arrayOf(0L, 0L)
    private var waypointCoordinates = arrayOf(-1L, 10L)
    private val instructions = input.split("\n").map {
        val direction = it.substring(0, 1)
        val amount = it.substring(1).toLong()
        Pair(direction, amount)
    }

    fun getManhattanDistanceWithoutWaypoint(): Long {
        reset()
        instructions.forEach { instruction ->
            val direction = instruction.first
            val amount = instruction.second
            when (direction) {
                "L" -> currentDirectionIndex -= amount.toInt() / 90
                "R" -> currentDirectionIndex += amount.toInt() / 90
                "F" -> moveInDirection(shipCoordinates, (currentDirectionIndex % directions.size).let {
                    if (it < 0) directions[directions.size + it] else directions[it]
                }, amount)
                else -> moveInDirection(shipCoordinates, direction, amount)
            }
        }
        return abs(shipCoordinates[0]) + abs(shipCoordinates[1])
    }

    fun getManhattanDistanceWithWaypoint(): Long {
        reset()
        instructions.forEach { instruction ->
            val direction = instruction.first
            val amount = instruction.second
            when (direction) {
                "L" -> repeat(amount.toInt() / 90) {
                    waypointCoordinates = arrayOf(-waypointCoordinates[1], waypointCoordinates[0])
                }
                "R" -> repeat(amount.toInt() / 90) {
                    waypointCoordinates = arrayOf(waypointCoordinates[1], -waypointCoordinates[0])
                }
                "F" -> repeat(2) { shipCoordinates[it] += waypointCoordinates[it] * amount }
                else -> moveInDirection(waypointCoordinates, direction, amount)
            }
        }
        return abs(shipCoordinates[0]) + abs(shipCoordinates[1])
    }

    private fun moveInDirection(coordinates: Array<Long>, direction: String, distance: Long) {
        when (direction) {
            "N" -> coordinates[0] -= distance
            "S" -> coordinates[0] += distance
            "E" -> coordinates[1] += distance
            "W" -> coordinates[1] -= distance
            else -> throw Exception("Unsupported direction $direction")
        }
    }

    private fun reset() {
        currentDirectionIndex = 1
        shipCoordinates[0] = 0L
        shipCoordinates[1] = 0L
        waypointCoordinates[0] = -1
        waypointCoordinates[1] = 10
    }
}