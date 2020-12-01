## --- Part Two ---

It turns out that this circuit is very timing-sensitive; you actually need to _minimize the signal delay_.

To do this, calculate the _number of steps_ each wire takes to reach each intersection; choose the intersection where the _sum of both wires' steps_ is lowest. If a wire visits a position on the grid multiple times, use the steps value from the _first_ time it visits that position when calculating the total value of a specific intersection.

The number of steps a wire takes is the total number of grid squares the wire has entered to get to that location, including the intersection being considered. Again consider the example from above:

    ...........
    .+-----+...
    .|.....|...
    .|..+--X-+.
    .|..|..|.|.
    .|.-X--+.|.
    .|..|....|.
    .|.......|.
    .o-------+.
    ...........

In the above example, the intersection closest to the central port is reached after `8+5+5+2 = _20_` steps by the first wire and `7+6+4+3 = _20_` steps by the second wire for a total of `20+20 = _40_` steps.

However, the top-right intersection is better: the first wire takes only `8+5+2 = _15_` and the second wire takes only `7+6+2 = _15_`, a total of `15+15 = _30_` steps.

Here are the best steps for the extra examples from above:

*   `R75,D30,R83,U83,L12,D49,R71,U7,L72  
    U62,R66,U55,R34,D71,R55,D58,R83` = `610` steps
*   `R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51  
    U98,R91,D20,R16,D67,R40,U7,R15,U6,R7` = `410` steps

_What is the fewest combined steps the wires must take to reach an intersection?_
