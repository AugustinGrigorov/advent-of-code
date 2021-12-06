package day6

import java.io.File

class Solution(file: File) {
    private val initialFishState = hashMapOf<Int, Long>()
    private var currentFishState = hashMapOf<Int, Long>()

    init {
        file.readText().trim().split(",").map { it.toInt() }.forEach {
            initialFishState[it] = initialFishState.getOrDefault(it, 0) + 1
        }
    }

    fun getNumberOfFishIn(days: Int): Long {
        currentFishState = initialFishState
        for (i in 0 until days) {
            val newFishState = hashMapOf<Int, Long>()
            currentFishState.entries.forEach {
                val (key, value) = it
                if (key == 0) {
                    newFishState[6] = newFishState.getOrDefault(6, 0L) + value
                    newFishState[8] = newFishState.getOrDefault(8, 0L) + value
                } else {
                    val newKey = key - 1
                    newFishState[newKey] = newFishState.getOrDefault(newKey, 0L) + value
                }
            }
            currentFishState = newFishState
        }
        return currentFishState.values.sum()
    }
}