import org.junit.jupiter.api.Test

class SolutionTest {
    private val dayOneSolution = day1.Solution()
    private val dayTwoSolution = day2.Solution()
    private val dayThreeSolution = day3.Solution()

    private val dayOneTestInput = "1721\n" +
            "979\n" +
            "366\n" +
            "299\n" +
            "675\n" +
            "1456"

    @Test
    fun day1_findTwoNumbersCorrectly() {
        assert(dayOneSolution.solve(2, dayOneTestInput) == 514579)
    }

    @Test
    fun day1_findThreeNumbersCorrectly() {
        assert(dayOneSolution.solve(3, dayOneTestInput) == 241861950)
    }

    private val dayTwoTestInput = "1-3 a: abcde\n" +
            "1-3 b: cdefg\n" +
            "2-9 c: ccccccccc"

    @Test
    fun day2_validatesPasswordsWithOldRulesCorrectly() {
        assert(dayTwoSolution.solve(day2.ValidationMethod.OLD, dayTwoTestInput) == 2)
    }

    @Test
    fun day2_validatesPasswordWithNewRulesCorrectly() {
        assert(dayTwoSolution.solve(day2.ValidationMethod.NEW, dayTwoTestInput) == 1)
    }

    private val dayThreeInput = "..##.......\n" +
            "#...#...#..\n" +
            ".#....#..#.\n" +
            "..#.#...#.#\n" +
            ".#...##..#.\n" +
            "..#.##.....\n" +
            ".#.#.#....#\n" +
            ".#........#\n" +
            "#.##...#...\n" +
            "#...##....#\n" +
            ".#..#...#.#"

    @Test
    fun day3_countsTreesCorrectly() {
        assert(dayThreeSolution.solve(dayThreeInput, arrayOf(arrayOf(1, 1))) == 2L)
        assert(dayThreeSolution.solve(dayThreeInput, arrayOf(arrayOf(1, 3))) == 7L)
        assert(dayThreeSolution.solve(dayThreeInput, arrayOf(arrayOf(1, 5))) == 3L)
        assert(dayThreeSolution.solve(dayThreeInput, arrayOf(arrayOf(1, 7))) == 4L)
        assert(dayThreeSolution.solve(dayThreeInput, arrayOf(arrayOf(2, 1))) == 2L)
    }

    @Test
    fun day3_countsTreesOnMultipleTrajectories() {
        assert(
            dayThreeSolution.solve(
                dayThreeInput,
                arrayOf(arrayOf(1, 1), arrayOf(1, 3), arrayOf(1, 5), arrayOf(1, 7), arrayOf(2, 1))
            ) == 336L
        )
    }
}