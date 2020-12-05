package day4

class Solution {
    private val fieldValidators = hashMapOf<String, (String) -> Boolean>(
        "byr" to { it.toInt() in 1920..2002 },
        "iyr" to { it.toInt() in 2010..2020 },
        "eyr" to { it.toInt() in 2020..2030 },
        "hgt" to {
            val heightAndUnit = it.split(Regex("(?=(cm)|(in))"))
            if (heightAndUnit.size == 2) {
                when (heightAndUnit[1]) {
                    "cm" -> heightAndUnit[0].toInt() in 150..193
                    "in" -> heightAndUnit[0].toInt() in 59..76
                    else -> false
                }
            } else {
                false
            }

        },
        "hcl" to { Regex("^#[a-f0-9]{6}$").matches(it) },
        "ecl" to { Regex("^amb|blu|brn|gry|grn|hzl|oth$").matches(it) },
        "pid" to { Regex("^[0-9]{9}$").matches(it) }
    )

    fun solve(validateFields: Boolean, input: String): Int {
        val passports = input.split("\n\n").map { passport ->
            val passportsData = hashMapOf<String, String>()
            val fields = passport.split(Regex("[ \n]"))
            fields.forEach {
                val fieldValuePair = it.split(":")
                passportsData[fieldValuePair[0]] = fieldValuePair[1]
            }
            passportsData
        }

        return passports.count {
            validatePassport(it, validateFields)
        }
    }

    private fun validatePassport(fields: HashMap<String, String>, validateFields: Boolean): Boolean {
        return fieldValidators.all { validator ->
            val currentField = fields[validator.key]
            if (currentField != null) {
                !validateFields || validator.value(currentField)
            }else {
                false
            }
        }
    }
}