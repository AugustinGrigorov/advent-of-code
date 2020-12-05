package day5

class Solution(input: String) {
    private var idList = listOf<Int>()

    init {
        idList = input.split("\n").map {
            it.replace('F', '0').replace('B', '1').replace('L', '0').replace('R', '1').toInt(2)
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