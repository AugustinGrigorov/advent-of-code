import java.io.File

fun main(args: Array<String>) {
    // Day 1
    val day1 = Day1.Solution()
    val input = File("src/inputs/day1.txt").readText().trim()
    println(day1.solve(2, input))
    println(day1.solve(3, input))
}