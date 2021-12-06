package day4

import java.io.File

class Solution(file: File) {
    private val draw: List<String>
    private val numberInBingoSlip = HashMap<String, MutableList<BingoSlip>>()
    private val numberOccurrences = HashMap<String, MutableList<NumberOccurrence>>()
    private val totalSlips: Int
    private var winners = mutableSetOf<BingoSlip>()

    init {
        val rawInput = file.readText().trim().split("\n\n").toMutableList()
        draw = rawInput[0].split(",")
        rawInput.removeAt(0)
        totalSlips = rawInput.size
        rawInput.forEach { BingoSlip(it, numberInBingoSlip, numberOccurrences) }
    }

    // Is it possible 2 slips to win at the same time? Assuming no
    fun findFirstWinningTicketScore(): Int {
        draw.forEach { numberDrawn ->
            numberOccurrences[numberDrawn]?.forEach {
                it.occurrence = true
            }
            numberInBingoSlip[numberDrawn]?.forEach { slipContainingNumber ->
                slipContainingNumber.checkScore(numberDrawn).let { score ->
                    if (score != 0) return score
                }
            }
        }
        return 0
    }

    fun findLastWinningTicketScore(): Int {
        draw.forEach { numberDrawn ->
            numberOccurrences[numberDrawn]?.forEach {
                it.occurrence = true
            }
            numberInBingoSlip[numberDrawn]?.forEach { slipContainingNumber ->
                slipContainingNumber.checkScore(numberDrawn).let { score ->
                    if (score != 0) winners.add(slipContainingNumber)
                    if (winners.size == totalSlips) return score
                }
            }
        }
        return 0
    }

    class BingoSlip(
        data: String,
        numberInBingoSlip: HashMap<String, MutableList<BingoSlip>>,
        numberOccurrences: HashMap<String, MutableList<NumberOccurrence>>
    ) {
        private val numbers = data.split("\n").map { rowNumbers ->
            rowNumbers.trim().split(Regex("\\s+")).map { number ->
                numberInBingoSlip[number] = numberInBingoSlip.getOrDefault(number, mutableListOf()).let {
                    it.add(this)
                    it
                }
                val numberOccurrence = NumberOccurrence(number, false)
                numberOccurrences[number] = numberOccurrences.getOrDefault(number, mutableListOf()).let {
                    it.add(numberOccurrence)
                    it
                }
                numberOccurrence
            }
        }

        fun checkScore(number: String): Int {
            for (i in 0..4) {
                var fullRow = true
                var fullCol = true
                for (j in 0..4) {
                    if (!numbers[i][j].occurrence) fullRow = false
                    if (!numbers[j][i].occurrence) fullCol = false
                }
                if (fullRow || fullCol) {
                    var sum = 0
                    numbers.forEach { rowNumbers ->
                        rowNumbers.forEach { numberOccurrence ->
                            if (!numberOccurrence.occurrence) {
                                sum += numberOccurrence.number.toInt()
                            }
                        }
                    }
                    return sum * number.toInt()
                }
            }
            return 0
        }
    }

    data class NumberOccurrence(val number: String, var occurrence: Boolean)
}