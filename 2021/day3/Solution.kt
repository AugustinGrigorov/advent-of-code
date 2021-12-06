package day3

import java.io.File
import kotlin.math.pow

class Solution(private val file: File) {
    fun findPowerConsumption(): Int {
        val sumOfAllBits = IntArray(12) { 0 }
        var totalLines = 0
        val gammaRateBits = IntArray(12)
        val epsilonRateBits = IntArray(12)
        file.forEachLine {
            totalLines++
            toCollectionOfBytes(it).forEachIndexed { index, bitInt -> sumOfAllBits[index] += bitInt }
        }
        sumOfAllBits.forEachIndexed { index, it ->
            if (it < totalLines.toDouble() / 2.0) {
                gammaRateBits[index] = 0
                epsilonRateBits[index] = 1
            } else {
                gammaRateBits[index] = 1
                epsilonRateBits[index] = 0
            }
        }
        return byteArrayToInt(gammaRateBits) * byteArrayToInt(epsilonRateBits)
    }

    fun findLifeSupportRating(): Int {
        val values = file.readLines().map(::toCollectionOfBytes)
        var oxygenGeneratorCandidates = values.map { it }
        var co2ScrubberCandidates = values.map { it }

        for (i in 0..11) {
            if (oxygenGeneratorCandidates.size > 1) {
                oxygenGeneratorCandidates = oxygenGeneratorCandidates.filter { it[i] == findMostCommonAt(i, oxygenGeneratorCandidates) }
            }
            if (co2ScrubberCandidates.size > 1) {
                co2ScrubberCandidates = co2ScrubberCandidates.filter { it[i] == 1 - findMostCommonAt(i, co2ScrubberCandidates) }
            }
        }

        return byteArrayToInt(oxygenGeneratorCandidates[0].toIntArray()) * byteArrayToInt(co2ScrubberCandidates[0].toIntArray())
    }

    private fun toCollectionOfBytes (value: String): List<Int> {
        return value.split("").filter { chunk -> chunk != "" }.map { bit ->
            bit.toInt()
        }
    }

    private fun byteArrayToInt(arr: IntArray): Int {
        return arr.reversedArray().reduceIndexed { index, acc, i -> acc + i * 2.0.pow(index.toDouble()).toInt() }
    }

    private fun findMostCommonAt(pos: Int, list: List<List<Int>>): Int {
        var sum = 0.0
        list.forEach { sum += it[pos] }
        if (sum < list.size.toDouble() / 2.0) {
            return 0
        }
        return 1
    }
}