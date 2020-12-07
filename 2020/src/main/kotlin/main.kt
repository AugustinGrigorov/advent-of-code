import java.io.File

fun main() {
    // Day 1
    val dayOneSolution = day1.Solution()
    val dayOneInput = File("src/inputs/day1.txt").readText().trim()
    println("---Day1---")
    println(dayOneSolution.solve(2, dayOneInput))
    println(dayOneSolution.solve(3, dayOneInput))

    // Day 2
    val dayTwoSolution = day2.Solution()
    val dayTwoInput = File("src/inputs/day2.txt").readText().trim()
    println("---Day2---")
    println(dayTwoSolution.solve(day2.ValidationMethod.OLD, dayTwoInput))
    println(dayTwoSolution.solve(day2.ValidationMethod.NEW, dayTwoInput))

    // Day 3
    val dayThreeSolution = day3.Solution()
    println("---Day3---")
    val dayThreeInput = File("src/inputs/day3.txt").readText().trim()
    println(dayThreeSolution.solve(dayThreeInput, arrayOf(arrayOf(1, 3))))
    println(
        dayThreeSolution.solve(
            dayThreeInput,
            arrayOf(arrayOf(1, 1), arrayOf(1, 3), arrayOf(1, 5), arrayOf(1, 7), arrayOf(2, 1))
        )
    )

    // Day 4
    val dayFourSolution = day4.Solution()
    val dayFourInput = File("src/inputs/day4.txt").readText().trim()
    println("---Day4---")
    println(dayFourSolution.solve(false, dayFourInput))
    println(dayFourSolution.solve(true, dayFourInput))

    // Day 5
    val dayFiveInput = File("src/inputs/day5.txt").readText().trim()
    val dayFiveSolution = day5.Solution(dayFiveInput)
    println("---Day5---")
    println(dayFiveSolution.biggest())
    println(dayFiveSolution.missing())

    // Day 6
    val daySixInput = File("src/inputs/day6.txt").readText().trim()
    val daySixSolution = day6.Solution(daySixInput)
    println("---Day6---")
    println(daySixSolution.anyone())
    println(daySixSolution.everyone())

    // Day 7
    val daySevenInput = File("src/inputs/day7.txt").readText().trim()
    val daySevenSolution = day7.Solution(daySevenInput)
    println("---Day7---")
    println(daySevenSolution.parentsOfShinyGoldBag)
    println(daySevenSolution.childrenOfShinyGoldBag)
}