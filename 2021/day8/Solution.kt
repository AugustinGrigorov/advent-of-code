package day8

import java.io.File
import kotlin.math.pow

class Solution(private val file: File) {
    fun findCountOfDigitsWithUniqueSignature(): Int {
        val uniqueSignatureLengths = arrayOf(2, 4, 3, 7)
        var count = 0
        file.forEachLine {
            count += it.split(" | ")[1].trim().split(" ").count { digitSignature ->
                digitSignature.length in uniqueSignatureLengths
            }
        }
        return count
    }

    fun findSumOfOutputDigits(): Long {
        var sum = 0L
        file.forEachLine {
            val (numberSignatures, output) = it.split(" | ").map { it.trim() }
            val numberMap = decodeMappings(numberSignatures)
            sum +=  output.split(" ")
                .map { numberRepresentation ->
                    numberMap.getOrDefault(numberRepresentation.toSet(), 0)
                }.reversed()
                .reduceIndexed { index, acc, i ->
                    acc + 10.0.pow(index.toDouble()).toInt() * i
                }
        }
        return sum
    }

    private fun decodeMappings(source: String): HashMap<Set<Char>, Int> {
        var signatures = source.split(" ").map { it.toSet() }
        val signatureToInt = HashMap<Set<Char>, Int>()
        val intToSignature = HashMap<Int, Set<Char>>()
        val lengthToNumber = hashMapOf(
            2 to 1,
            4 to 4,
            3 to 7,
            7 to 8
        )
        lengthToNumber.forEach { (len, num) ->
            signatures = signatures.filter {
                if (it.size == len) {
                    signatureToInt[it] = num
                    intToSignature[num] = it
                    false
                } else {
                    true
                }
            }
        }
        signatures = signatures.filter {
            if (it.size == 5 && it.containsAll(intToSignature[4]!! - intToSignature[1]!!)) {
                signatureToInt[it] = 5
                intToSignature[5] = it
                false
            } else {
                true
            }
        }
        signatures = signatures.filter {
            if (it.size == 5 && it.containsAll(intToSignature[7]!!)) {
                signatureToInt[it] = 3
                intToSignature[3] = it
                false
            } else {
                true
            }
        }
        signatures = signatures.filter {
            if (it.size == 5) {
                signatureToInt[it] = 2
                intToSignature[2] = it
                false
            } else {
                true
            }
        }
        signatures = signatures.filter {
            if (it.size == 6 && !it.containsAll(intToSignature[3]!! - intToSignature[5]!!)) {
                signatureToInt[it] = 6
                intToSignature[6] = it
                false
            } else {
                true
            }
        }
        signatures = signatures.filter {
            if (it.size == 6 && !it.containsAll(intToSignature[2]!! - intToSignature[3]!!)) {
                signatureToInt[it] = 9
                intToSignature[9] = it
                false
            } else {
                true
            }
        }
        signatureToInt[signatures[0]] = 0
        return signatureToInt
    }
}