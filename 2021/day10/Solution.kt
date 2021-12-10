package day10

import java.io.File
import java.util.*

class Solution (val file: File) {
    fun getSyntaxErrorScore (): Long {
        var score = 0L
        file.forEachLine {
            val (wrongToken) = findWrongTokenAndSequence(it)
            wrongToken?.let { token ->
                score += when (token) {
                    ')' -> 3
                    ']' -> 57
                    '}' -> 1197
                    '>' -> 25137
                    else -> 0
                }
            }
        }
        return score
    }

    fun getAutocompleteScore (): Long {
        val autocompleteScores = mutableListOf<Long>()
        file.forEachLine {
            var score = 0L
            val (wrongToken, sequence) = findWrongTokenAndSequence(it)
            if (wrongToken == null) {
                sequence.reversed().forEach { token ->
                    score *= 5
                    score += when (token) {
                        '(' -> 1L
                        '[' -> 2L
                        '{' -> 3L
                        '<' -> 4L
                        else -> 0L
                    }
                }
            }
            if (score != 0L) autocompleteScores.add(score)
        }
        return med(autocompleteScores)
    }

    private fun findWrongTokenAndSequence (line: String): Pair<Char?, Stack<Char>> {
        val tokenSequence = Stack<Char>()
        return Pair(line.find { token ->
            when (token) {
                ')' -> tokenSequence.size == 0 || tokenSequence.pop() != '('
                ']' -> tokenSequence.size == 0 || tokenSequence.pop() != '['
                '}' -> tokenSequence.size == 0 || tokenSequence.pop() != '{'
                '>' -> tokenSequence.size == 0 || tokenSequence.pop() != '<'
                else -> !tokenSequence.add(token)
            }
        }, tokenSequence)
    }

    private fun med(list: List<Long>) = list.sorted().let {
        if (it.size % 2 == 0)
            (it[it.size / 2] + it[(it.size - 1) / 2]) / 2
        else
            it[it.size / 2]
    }
}