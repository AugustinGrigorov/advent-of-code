## --- Part Two ---

An Elf just remembered one more important detail: the two adjacent matching digits _are not part of a larger group of matching digits_.

Given this additional criterion, but still ignoring the range rule, the following are now true:

*   `112233` meets these criteria because the digits never decrease and all repeated digits are exactly two digits long.
*   `123_444_` no longer meets the criteria (the repeated `44` is part of a larger group of `444`).
*   `111122` meets the criteria (even though `1` is repeated more than twice, it still contains a double `22`).

_How many different passwords_ within the range given in your puzzle input meet all of the criteria?
