import java.io.File

fun main(args: Array<String>) {
    // Day 1
    val dayOneSolution = day1.Solution()
    val dayOneInput = File("src/inputs/day1.txt").readText().trim()
    println(dayOneSolution.solve(2, dayOneInput))
    println(dayOneSolution.solve(3, dayOneInput))
    // Day 1
    val dayTwoSolution = day2.Solution()
    val dayTwoInput = File("src/inputs/day2.txt").readText().trim()
    println(dayTwoSolution.solve(day2.ValidationMethod.OLD, dayTwoInput))
    println(dayTwoSolution.solve(day2.ValidationMethod.NEW, dayTwoInput))
}