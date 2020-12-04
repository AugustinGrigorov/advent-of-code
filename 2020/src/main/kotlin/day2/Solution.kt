package day2

enum class ValidationMethod {
    OLD, NEW
}

class Solution {
    fun solve(validationMethod: ValidationMethod, input: String): Int {
        val passwordCandidates = processInput(input)
        return passwordCandidates.count{
            it.validate(validationMethod)
        }
    }

    private fun processInput(input: String): List<PasswordCandidate> {
        return input.split("\n").map {
            var passwordAndPattern = it.split(": ")
            var password = passwordAndPattern[1]
            var pattern = passwordAndPattern[0]
            var patternParameters = pattern.split(Regex("[ -]"))
            PasswordCandidate(
                password,
                Rule(patternParameters[0].toInt(), patternParameters[1].toInt(), patternParameters[2].single())
            )
        }
    }

    class PasswordCandidate(private val password: String, private val rule: Rule) {
        fun validate (validationMethod: ValidationMethod) : Boolean {
            return when(validationMethod) {
                ValidationMethod.OLD -> {
                    val occurrences = password.count{
                        it == rule.char
                    }
                    occurrences >= rule.firstParam && occurrences <= rule.secondParam
                }
                ValidationMethod.NEW -> {
                    var valid = false
                    arrayOf(rule.firstParam, rule.secondParam).forEach {
                        if (password[it - 1] == rule.char) valid = !valid
                    }
                    valid
                }
            }
        }
    }
    data class Rule(val firstParam: Int, val secondParam: Int, val char: Char)
}