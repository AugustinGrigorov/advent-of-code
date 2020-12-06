package day6

class Solution(input: String) {
    var groupAnswersList = listOf<String>()

    init {
        groupAnswersList = input.split("\n\n")
    }

    fun anyone(): Int {
        return groupAnswersList.fold(0) { acc, it ->
            acc + it.replace("\n", "").toSet().size
        }
    }

    fun everyone(): Int {
        return groupAnswersList.fold(0) { acc, groupAnswers ->
            val groupAnswersPerPerson = groupAnswers.split("\n")
            var currentSet = groupAnswersPerPerson[0].toSet()
            groupAnswersPerPerson.forEach {
                currentSet = currentSet.intersect(it.toSet())
            }
            acc + currentSet.size
        }
    }
}