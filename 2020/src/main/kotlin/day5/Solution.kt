package day5

class Solution(input: String) {
    private var idList = listOf<Int>()

    init {
        idList = input.split("\n").map {
            val row = it.substring(0, 7).replace('F', '0').replace('B', '1').toInt(2)
            val col = it.substring(7).replace('L', '0').replace('R', '1').toInt(2)
            row * 8 + col
        }
    }

    fun biggest(): Int {
        return idList.maxOrNull()!!
    }

    fun missing(): Int {
        // A heap would be a more efficient implementation but it's substantially moore effort
        val seats = idList.toIntArray()
        seats.sort()
        for (i in 0..seats.size) {
            val candidate = seats[i] + 1
            if (candidate != seats[i + 1]) return candidate
        }
        return 0
    }
}