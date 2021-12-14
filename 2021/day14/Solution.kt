package day14

import java.io.File

class Solution(file: File) {
    private val polymerMappings = hashMapOf<String, Char>()
    private var polymerCount = hashMapOf<Char, Long>()
    private var pairCounts = hashMapOf<String, Long>()
    private val reset: () -> Unit

    init {
        val (polymerTemplate, rawMappings) = file.readText().trim().split("\n\n")

        val initialPolymerCount = hashMapOf<Char, Long>()
        polymerTemplate.forEach {
            initialPolymerCount[it] = initialPolymerCount.getOrDefault(it, 0) + 1
        }

        val initialPairCounts = hashMapOf<String, Long>()
        for (i in 1 until polymerTemplate.length) {
            val key = "${polymerTemplate[i - 1]}${polymerTemplate[i]}"
            initialPairCounts[key] = initialPairCounts.getOrDefault(key, 0) + 1
        }

        reset = {
            polymerCount = HashMap(initialPolymerCount)
            pairCounts = HashMap(initialPairCounts)
        }

        rawMappings.split("\n").forEach {
            val (from, to) = it.split(" -> ")
            polymerMappings[from] = to[0]
        }

    }

    fun runForNStepsAndReturnMostCommonByLeastCommon(steps: Int): Long {
        reset()
        for (i in 0 until steps) {
            performStep()
        }
        return polymerCount.maxOf { it.value } - polymerCount.minOf { it.value }
    }

    private fun performStep() {
        val newPairCounts = hashMapOf<String, Long>()
        pairCounts.forEach {
            val (key, value) = it
            polymerMappings[key]?.let { polymer ->
                polymerCount[polymer] = polymerCount.getOrDefault(polymer, 0) + value
                val newPairs = listOf("${key[0]}${polymer}", "${polymer}${key[1]}")
                newPairs.forEach { pair ->
                    if (polymerMappings.contains(pair)) newPairCounts[pair] = newPairCounts.getOrDefault(pair, 0L) + value
                }
            }
        }
        pairCounts = newPairCounts
    }
}