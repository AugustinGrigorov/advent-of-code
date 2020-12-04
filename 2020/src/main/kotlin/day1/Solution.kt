package day1

class Solution {
    fun solve (desiredAddends: Int, input: String) : Int {
        if (desiredAddends < 2) return 0
        val targetSum = 2020
        val numbers = input.split("\n").map { it.toInt() }
        val sums = hashMapOf<Int, MutableSet<Int>>()

        val requiredAddends = desiredAddends - 2

        numbers.forEach { firstNumber ->
            for (i in 0..requiredAddends) {
                numbers.forEach {
                    val addends = mutableSetOf<Int>(firstNumber)
                    if (!addends.contains(it)) {
                        addends.add(it)
                    }
                    if (addends.size == desiredAddends - 1) {
                        sums[addends.sum()] = addends
                    }
                }
            }
        }

        numbers.forEach{ num ->
            var result = num;
            sums[targetSum - num]?.let { it ->
                it.forEach{
                    result *= it
                }
                return result
            }
        }
        return 0
    }
}