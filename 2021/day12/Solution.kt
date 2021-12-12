package day12

import java.io.File
import java.util.*

class Solution(file: File) {
    private val adjacentNodes = hashMapOf<String, MutableList<String>>()

    init {
        file.forEachLine { line ->
            val (node1, node2) = line.trim().split("-")
            adjacentNodes[node1] = adjacentNodes.getOrDefault(node1, mutableListOf()).let { it.add(node2); it }
            adjacentNodes[node2] = adjacentNodes.getOrDefault(node2, mutableListOf()).let { it.add(node1); it }
        }
    }

    fun getAllPathCount(visitOneSmallCaveTwice: Boolean): Int {
        return countPathsFrom("start", listOf(), visitOneSmallCaveTwice)
    }

    private fun countPathsFrom(node: String, visited: List<String>, visitOneSmallCaveTwice: Boolean): Int {
        if (node == "end") return 1
        val newVisited = visited.toMutableList().let { it.add(node); it }
        val validNodes =
            if (visitOneSmallCaveTwice && newVisited.distinct().filter { it != "start" && it[0].isLowerCase() }
                    .all { Collections.frequency(newVisited, it) < 2 }) {
                adjacentNodes[node]?.filter { it != "start" }
            } else {
                adjacentNodes[node]?.filter {
                    !visited.contains(it) || it[0].isUpperCase()
                }
            }
        return validNodes?.sumOf { countPathsFrom(it, newVisited, visitOneSmallCaveTwice) } ?: 0
    }
}


