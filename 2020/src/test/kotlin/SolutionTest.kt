import org.junit.jupiter.api.Test

class SolutionTest  {
    private val dayOneSolution = day1.Solution()
    private val dayTwoSolution = day2.Solution()

    val dayOneTestInput = "1721\n" +
            "979\n" +
            "366\n" +
            "299\n" +
            "675\n" +
            "1456"
    @Test
    fun day1_findTwoNumbersCorrectly () {
        assert(dayOneSolution.solve(2, dayOneTestInput) == 514579)
    }

    @Test
    fun day1_findThreeNumbersCorrectly () {
        assert(dayOneSolution.solve(3, dayOneTestInput) == 241861950)
    }

    val dayTwoTestInput = "1-3 a: abcde\n" +
            "1-3 b: cdefg\n" +
            "2-9 c: ccccccccc"
    @Test
    fun day2_validatesPasswordsWithOldRulesCorrectly () {
        assert(dayTwoSolution.solve(day2.ValidationMethod.OLD, dayTwoTestInput) == 2)
    }

    @Test
    fun day2_validatesPasswordWithNewRulesCorrectly () {
        assert(dayTwoSolution.solve(day2.ValidationMethod.NEW, dayTwoTestInput) == 1)
    }
}