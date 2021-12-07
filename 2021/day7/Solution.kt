package day7

import java.io.File
import kotlin.math.abs

class Solution(file: File) {
    private val depths: List<Int>
    private val seriesCache = hashMapOf<Int, Int>()

    init {
        depths = file.readText().trim().split(",").map { it.toInt() }
    }

    fun findBestAlignmentCost(): Int {
        val pos = med(depths)
        var cost = 0
        depths.forEach {
            cost += abs(pos - it)
        }
        return cost
    }

    fun findBestAlignmentCostWithFuelRequirements(): Int {
        var min = Int.MAX_VALUE
        var max = 0
        val submarinesAtDepth = hashMapOf<Int, Int>()
        depths.forEach {
            submarinesAtDepth[it] = submarinesAtDepth.getOrDefault(it, 0) + 1
            if (it < min) min = it
            if (it > max) max = it
        }
        var leastAmount = Int.MAX_VALUE
        for(candidate in min .. max) {
            var currentAmount = 0
            submarinesAtDepth.forEach{ (pos, submarinesCount) ->
                currentAmount += sumSeriesTo(abs(candidate - pos)) * submarinesCount
            }
            if (currentAmount < leastAmount) {
                leastAmount = currentAmount
            }
        }
        return leastAmount
    }

    private fun sumSeriesTo(n: Int): Int {
        seriesCache[n]?.let {
            return it
        }
        var sum = 0
        for (i in 1 .. n) {
            sum += i
        }
        seriesCache[n] = sum
        return sum
    }

    private fun med(list: List<Int>) = list.sorted().let {
        if (it.size % 2 == 0)
            (it[it.size / 2] + it[(it.size - 1) / 2]) / 2
        else
            it[it.size / 2]
    }
}