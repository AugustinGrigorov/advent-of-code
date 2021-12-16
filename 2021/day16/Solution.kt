package day16

import java.io.File
import java.util.*

class Solution(file: File) {
    private val bitSequence: String

    init {
        val hexCharToBitSequence = hashMapOf(
            '0' to "0000",
            '1' to "0001",
            '2' to "0010",
            '3' to "0011",
            '4' to "0100",
            '5' to "0101",
            '6' to "0110",
            '7' to "0111",
            '8' to "1000",
            '9' to "1001",
            'A' to "1010",
            'B' to "1011",
            'C' to "1100",
            'D' to "1101",
            'E' to "1110",
            'F' to "1111"
        )
        bitSequence = file.readText().trim().map { hexCharToBitSequence[it]!! }.joinToString(separator = "")

    }

    fun addPackageVersions(): Int {
        var versionSum = 0
        val subPackets = ArrayDeque<Packet>()
        subPackets.add(parseFrom(0).first)

        while (subPackets.isNotEmpty()) {
            val next = subPackets.pop()
            versionSum += next.version
            subPackets += next.subPackets
        }
        return versionSum
    }

    fun getEndResultOfExpression(): Long {
        return parseFrom(0).first.literalValue
    }

    private fun parseFrom(index: Int): Pair<Packet, Int> {
        val version = bitSequence.slice(index..index + 2).toInt(2)
        val type = bitSequence.slice(index + 3..index + 5).toInt(2)
        val subPackets = mutableListOf<Packet>()
        var literalValue = 0L
        var nextIndex = index
        if (type != 4) {
            when (bitSequence[index + 6]) {
                '0' -> {
                    // the next 15 bits are a number that represents the total length in bits of the sub-packets contained by this packet.
                    val lenOfSubPackets = bitSequence.slice(index + 7..index + 21).toInt(2)
                    nextIndex = index + 22 + lenOfSubPackets
                    var (subPacket, nextBit) = parseFrom(index + 22)
                    subPackets.add(subPacket)
                    while (nextBit != nextIndex) {
                        val result = parseFrom(nextBit)
                        subPacket = result.first
                        nextBit = result.second
                        subPackets.add(subPacket)
                    }
                }
                '1' -> {
                    // then the next 11 bits are a number that represents the number of sub-packets immediately contained by this packet.
                    val numOfSubPackets = bitSequence.slice(index + 7..index + 17).toInt(2)
                    var nextBit = index + 18
                    repeat(numOfSubPackets) {
                        val result = parseFrom(nextBit)
                        subPackets.add(result.first)
                        nextBit = result.second
                    }
                    nextIndex = nextBit
                }
            }
        } else {
            var nextBit = index + 6
            var valueInBinary = ""
            while (bitSequence[nextBit] != '0') {
                valueInBinary += bitSequence.slice(nextBit + 1 .. nextBit + 4)
                nextBit += 5
            }
            valueInBinary += bitSequence.slice(nextBit + 1 .. nextBit + 4)
            literalValue = valueInBinary.toLong(2)
            nextIndex = nextBit + 5
        }
        when(type) {
            0 -> literalValue = subPackets.sumOf { it.literalValue }
            1 -> literalValue = subPackets.fold(1L) { total, next -> total * next.literalValue }
            2 -> literalValue = subPackets.minOf { it.literalValue }
            3 -> literalValue = subPackets.maxOf { it.literalValue }
            5 -> literalValue = if (subPackets[0].literalValue > subPackets[1].literalValue) 1L else 0L
            6 -> literalValue = if (subPackets[0].literalValue < subPackets[1].literalValue) 1L else 0L
            7 -> literalValue = if (subPackets[0].literalValue == subPackets[1].literalValue) 1L else 0L
        }
        return Pair(Packet(version, type, subPackets, literalValue), nextIndex)
    }

    data class Packet(
        val version: Int,
        val type: Int,
        val subPackets: List<Packet>,
        val literalValue: Long
    )
}