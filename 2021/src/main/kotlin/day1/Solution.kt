package day1

import java.io.File

class Solution (private val file: File) {
    fun largestStreakIncreasingReadings(): Int {
        var currentStreak = 0
        var longestStreak = 0
        var previousValue = Int.MAX_VALUE
        file.forEachLine {
            val currentValue = it.toInt()
            if (currentValue > previousValue) currentStreak++
            if (currentStreak > longestStreak) longestStreak = currentStreak
            previousValue = currentValue
        }
        return longestStreak
    }

    fun largestStreakIncreasingRunningWindowOfThreeReadings(): Int {
        var currentStreak = 0
        var longestStreak = 0
        var oneBack = 0
        var twoBack = 0
        var threeBack = 0
        file.forEachLine {
            val currentValue = it.toInt()
            if (threeBack == 0) threeBack = currentValue
            else if (twoBack == 0) twoBack = currentValue
            else if (oneBack == 0) oneBack = currentValue
            else {
                if (currentValue + oneBack + twoBack > oneBack + twoBack + threeBack) currentStreak++
                if (currentStreak > longestStreak) longestStreak = currentStreak
                threeBack = twoBack
                twoBack = oneBack
                oneBack = currentValue
            }
        }
        return longestStreak
    }
}


