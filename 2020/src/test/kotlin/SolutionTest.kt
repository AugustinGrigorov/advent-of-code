import org.junit.jupiter.api.Test

class SolutionTest  {
    private val day1 = Day1.Solution()

    @Test
    fun findTwoNumbersCorrectly () {
        val input = "1721\n" +
                "979\n" +
                "366\n" +
                "299\n" +
                "675\n" +
                "1456"
        assert(day1.solve(2, input) == 514579)
    }

    @Test
    fun findThreeNumbersCorrectly () {
        val input = "1721\n" +
                "979\n" +
                "366\n" +
                "299\n" +
                "675\n" +
                "1456"
        assert(day1.solve(3, input) == 241861950)
    }
}