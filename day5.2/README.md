## --- Part Two ---

The air conditioner comes online! Its cold air feels good for a while, but then the TEST alarms start to go off. Since the air conditioner <span title="Honestly, I'm not sure what you expected.">can't vent its heat anywhere</span> but back into the spacecraft, it's actually making the air inside the ship _warmer_.

Instead, you'll need to use the TEST to extend the [thermal radiators](https://en.wikipedia.org/wiki/Spacecraft_thermal_control). Fortunately, the diagnostic program (your puzzle input) is already equipped for this. Unfortunately, your Intcode computer is not.

Your computer is only missing a few opcodes:

*   Opcode `5` is _jump-if-true_: if the first parameter is _non-zero_, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
*   Opcode `6` is _jump-if-false_: if the first parameter _is zero_, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
*   Opcode `7` is _less than_: if the first parameter is _less than_ the second parameter, it stores `1` in the position given by the third parameter. Otherwise, it stores `0`.
*   Opcode `8` is _equals_: if the first parameter is _equal to_ the second parameter, it stores `1` in the position given by the third parameter. Otherwise, it stores `0`.

Like all instructions, these instructions need to support _parameter modes_ as described above.

Normally, after an instruction is finished, the instruction pointer increases by the number of values in that instruction. _However_, if the instruction modifies the instruction pointer, that value is used and the instruction pointer is _not automatically increased_.

For example, here are several programs that take one input, compare it to the value `8`, and then produce one output:

*   `3,9,8,9,10,9,4,9,99,-1,8` - Using _position mode_, consider whether the input is _equal to_ `8`; output `1` (if it is) or `0` (if it is not).
*   `3,9,7,9,10,9,4,9,99,-1,8` - Using _position mode_, consider whether the input is _less than_ `8`; output `1` (if it is) or `0` (if it is not).
*   `3,3,1108,-1,8,3,4,3,99` - Using _immediate mode_, consider whether the input is _equal to_ `8`; output `1` (if it is) or `0` (if it is not).
*   `3,3,1107,-1,8,3,4,3,99` - Using _immediate mode_, consider whether the input is _less than_ `8`; output `1` (if it is) or `0` (if it is not).

Here are some jump tests that take an input, then output `0` if the input was zero or `1` if the input was non-zero:

*   `3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9` (using _position mode_)
*   `3,3,1105,-1,9,1101,0,0,12,4,12,99,1` (using _immediate mode_)

Here's a larger example:

    3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
    1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
    999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99

The above example program uses an input instruction to ask for a single number. The program will then output `999` if the input value is below `8`, output `1000` if the input value is equal to `8`, or output `1001` if the input value is greater than `8`.

This time, when the TEST diagnostic program runs its input instruction to get the ID of the system to test, _provide it `5`_, the ID for the ship's thermal radiator controller. This diagnostic test suite only outputs one number, the _diagnostic code_.

_What is the diagnostic code for system ID `5`?_
