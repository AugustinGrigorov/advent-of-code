package day9

class Solution(input: String) {
    private val numberSeries = input.split("\n").map { it.toLong() }

    fun findOutlier(permeableLength: Int): Long {
        for (i in permeableLength..numberSeries.size) {
            val candidate = numberSeries[i]
            val range = numberSeries.subList(i - permeableLength, i)
            if (!range.any {
                    val target = candidate - it
                    target != it && range.contains(candidate - it)
                }) return candidate
        }
        throw Exception("No outlier found")
    }

    fun findEncryptionWeakness(permeableLength: Int): Long {
        val outlier = findOutlier(permeableLength)
        for (i in 0..numberSeries.size) {
            var remainder = outlier
            var cursor = i
            val range = mutableSetOf<Long>()
            while (remainder > 0 && cursor < numberSeries.size) {
                val nextNumber = numberSeries[cursor]
                remainder -= nextNumber
                range.add(nextNumber)
                cursor++
            }

            if (remainder == 0L && range.size > 1) {
                return range.minOrNull()!! + range.maxOrNull()!!
            }
        }
        throw Exception("No weakness found")
    }
}