## --- Day 13: Care Package ---

As you ponder the solitude of space and the ever-increasing three-hour roundtrip for messages between you and Earth, you notice that the Space Mail Indicator Light is blinking. To help keep you sane, the Elves have sent you a care package.

It's a new game for the ship's [arcade cabinet](https://en.wikipedia.org/wiki/Arcade_cabinet)! Unfortunately, the arcade is _all the way_ on the other end of the ship. Surely, it won't be hard to build your own - the care package even comes with schematics.

The arcade cabinet runs [Intcode](9) software like the game the Elves sent (your puzzle input). It has a primitive screen capable of drawing square _tiles_ on a grid. The software draws tiles to the screen with output instructions: every three output instructions specify the `x` position (distance from the left), `y` position (distance from the top), and `tile id`. The `tile id` is interpreted as follows:

*   `0` is an _empty_ tile. No game object appears in this tile.
*   `1` is a _wall_ tile. Walls are indestructible barriers.
*   `2` is a _block_ tile. Blocks can be broken by the ball.
*   `3` is a _horizontal paddle_ tile. The paddle is indestructible.
*   `4` is a _ball_ tile. The ball moves diagonally and bounces off objects.

For example, a sequence of output values like `1,2,3,6,5,4` would draw a _horizontal paddle_ tile (`1` tile from the left and `2` tiles from the top) and a _ball_ tile (`6` tiles from the left and `5` tiles from the top).

Start the game. _How many block tiles are on the screen when the game exits?_
