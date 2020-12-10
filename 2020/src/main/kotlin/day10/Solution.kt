package day10

class Solution(input: String) {
    private val sortedVoltages = input.split("\n").map { it.toInt() }.sorted().toMutableList().let {
        it.add(0, 0)
        it.add(it.maxOrNull()!! + 3)
        it
    }
    private val memoTable = hashMapOf<Int, Long>()

    fun findVoltageDifference(): Int {
        var oneJoltDifferences = 0
        var threeJoltDifferences = 0
        for (i in 0 until sortedVoltages.size - 1) {
            when (sortedVoltages[i + 1] - sortedVoltages[i]) {
                1 -> oneJoltDifferences++
                3 -> threeJoltDifferences++
            }
        }
        return oneJoltDifferences * threeJoltDifferences
    }

    fun findAdapterCombinations(): Long {
        return findAllPossibleCombinationsAtIndex(0)
    }

    private fun findAllPossibleCombinationsAtIndex(index: Int) : Long {
        if (index == sortedVoltages.size - 1) return 1L
        memoTable[index]?.let { return it }
        var cursor = index + 1
        var acc = 0L
        while (cursor < sortedVoltages.size && sortedVoltages[cursor] <= sortedVoltages[index] + 3) {
            acc += findAllPossibleCombinationsAtIndex(cursor)
            cursor++
        }
        memoTable[index] = acc
        return acc
    }
}