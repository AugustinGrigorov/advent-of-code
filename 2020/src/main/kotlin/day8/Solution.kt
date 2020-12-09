package day8

class Solution(input: String) {
    private val inputInstructions = input.split("\n").map {
        val instructionParts = it.split(" ")
        Pair(instructionParts[0], instructionParts[1].toInt())
    }

    fun run(fixInstructions: Boolean): Int {
        return if (!fixInstructions) {
            execute(inputInstructions, 0, mutableSetOf()).first
        } else {
            val changeableInstructions = mutableSetOf<Int>()
            inputInstructions.forEachIndexed { i, it ->
                if (Regex("jmp|nop").containsMatchIn(it.first)) {
                    changeableInstructions.add(i)
                }
            }

            changeableInstructions.forEach { instructionToChangeIndex ->
                val result = execute(inputInstructions.mapIndexed { i, it ->
                    if (i == instructionToChangeIndex) {
                        swap(it)
                    } else {
                        it
                    }
                }, 0, mutableSetOf())
                if (result.second) {
                    return result.first
                }
            }
            return 0
        }
    }

    private fun execute(
        instructions: List<Pair<String, Int>>,
        i: Int,
        executedInstructions: MutableSet<Int>
    ): Pair<Int, Boolean> {
        if (executedInstructions.contains(i)) {
            return Pair(0, false)
        }

        if (i == instructions.size) {
            return Pair(0, true)
        }

        executedInstructions.add(i)
        val instruction = instructions[i]
        return when (instruction.first) {
            "acc" -> {
                val nextInstructionResult = execute(instructions, i + 1, executedInstructions)
                Pair(nextInstructionResult.first + instruction.second, nextInstructionResult.second)
            }
            "jmp" -> {
                val nextInstructionResult = execute(instructions, i + instruction.second, executedInstructions)
                Pair(nextInstructionResult.first, nextInstructionResult.second)
            }
            "nop" -> {
                val nextInstructionResult = execute(instructions, i + 1, executedInstructions)
                Pair(nextInstructionResult.first, nextInstructionResult.second)
            }
            else -> throw Exception("Invalid instruction")
        }
    }

    private fun swap(instruction: Pair<String, Int>): Pair<String, Int> {
        return when (instruction.first) {
            "jmp" -> Pair("nop", instruction.second)
            "nop" -> Pair("jmp", instruction.second)
            else -> throw Exception("Instruction cannot be swapped")
        }
    }
}