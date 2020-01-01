package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

type opMode int64

const (
	positionMode  opMode = 0
	immediateMode opMode = 1
	relativeMode  opMode = 2
)

type coordinates struct {
	x, y int64
}

type direction int

const (
	north direction = 1
	south direction = 2
	west  direction = 3
	east  direction = 4
)

type item int

const (
	wall     item = 0
	corridor item = 1
	problem  item = 2
	start    item = 3
	path     item = 4
)

var clockwiseDirections = []direction{north, east, south, west}
var visitedCoordinates = make(map[coordinates]item)

var lowerX, upperX, lowerY, upperY int64

type droid struct {
	position       coordinates
	blocked        bool
	directionIndex int
	distance       int
	path           []coordinates
}

var smallestDistance int
var shortestPath []coordinates

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), ",")
	instructions := make(map[int64]int64, len(inputArray))
	for index, opcode := range inputArray {
		instructions[int64(index)], err = strconv.ParseInt(opcode, 10, 64)
		if err != nil {
			panic(err)
		}
	}
	visitedCoordinates[coordinates{0, 0}] = start

	for index := range clockwiseDirections {
		d := droid{
			directionIndex: index,
		}
		executeIndex(0, 0, copyInstructions(instructions), &d)
	}

	for _, coord := range shortestPath {
		visitedCoordinates[coord] = path
	}

	// This bit is just a visualisation for fun
	for y := upperY; y > lowerY-1; y-- {
		fmt.Println()
		for x := lowerX; x < upperX+1; x++ {
			switch visitedCoordinates[coordinates{x, y}] {
			case wall:
				fmt.Print(" ◻️ ")
			case corridor:
				fmt.Print("   ")
			case path:
				fmt.Print(" + ")
			case problem:
				fmt.Print(" X ")
			default:
				fmt.Print(" O ")
			}
		}
	}
	fmt.Println()

	fmt.Println("Shortest distance:", smallestDistance)
}

func copyInstructions(instructions map[int64]int64) map[int64]int64 {
	copy := make(map[int64]int64, len(instructions))
	for k, v := range instructions {
		copy[k] = v
	}
	return copy
}

func (d *droid) output(index int64, relativeBase int64, instructions map[int64]int64, status int64) {
	currentCoordinates := d.getMoveCoordinates(getDirection(d.directionIndex))
	if _, ok := visitedCoordinates[currentCoordinates]; ok {
		d.blocked = true
	}
	visitedCoordinates[currentCoordinates] = item(status)

	if currentCoordinates.x > upperX {
		upperX = currentCoordinates.x
	}
	if currentCoordinates.y > upperY {
		upperY = currentCoordinates.y
	}
	if currentCoordinates.x < lowerX {
		lowerX = currentCoordinates.x
	}
	if currentCoordinates.y < lowerY {
		lowerY = currentCoordinates.y
	}

	if status == 1 {
		d.path = append(d.path, currentCoordinates)
	}

	if status == 1 || status == 2 {
		d.position = currentCoordinates
		d.distance++
		for i := 1; i < 4; i += 2 {
			newDirectionIndex := d.directionIndex + i
			newCoordinates := d.getMoveCoordinates(getDirection(newDirectionIndex))
			if _, ok := visitedCoordinates[newCoordinates]; !ok {
				np := make([]coordinates, len(d.path))
				copy(np, d.path)
				nd := droid{
					position:       d.position,
					directionIndex: newDirectionIndex,
					distance:       d.distance,
					path:           np,
				}
				executeIndex(index, relativeBase, copyInstructions(instructions), &nd)
			}
		}
	}

	if status == 2 {
		if smallestDistance == 0 || d.distance < smallestDistance {
			smallestDistance = d.distance
			shortestPath = d.path
		}
	}
}

func (d *droid) input() direction {
	return getDirection(d.directionIndex)
}

func (d *droid) getMoveCoordinates(direct direction) coordinates {
	pos := d.position
	switch direct {
	case north:
		pos.y++
	case south:
		pos.y--
	case east:
		pos.x++
	case west:
		pos.x--
	}
	return pos
}

func getDirection(index int) direction {
	return clockwiseDirections[index%4]
}

func executeIndex(index, relativeBase int64, instructions map[int64]int64, d *droid) map[int64]int64 {
	operator := instructions[index]
	switch operator % 100 {
	case 1:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		instructions[paramIndexes[2]] = instructions[paramIndexes[0]] + instructions[paramIndexes[1]]
		return executeIndex(index+4, relativeBase, instructions, d)
	case 2:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		instructions[paramIndexes[2]] = instructions[paramIndexes[0]] * instructions[paramIndexes[1]]
		return executeIndex(index+4, relativeBase, instructions, d)
	case 3:
		if !d.blocked {
			input := d.input()
			flags := getFlags(operator)
			paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
			instructions[paramIndexes[0]] = int64(input)
			return executeIndex(index+2, relativeBase, instructions, d)
		}
	case 4:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		d.output(index+2, relativeBase, instructions, instructions[paramIndexes[0]])
		return executeIndex(index+2, relativeBase, instructions, d)
	case 5:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 2)
		if instructions[paramIndexes[0]] > 0 {
			return executeIndex(instructions[paramIndexes[1]], relativeBase, instructions, d)
		}
		return executeIndex(index+3, relativeBase, instructions, d)
	case 6:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 2)
		if instructions[paramIndexes[0]] == 0 {
			return executeIndex(instructions[paramIndexes[1]], relativeBase, instructions, d)
		}
		return executeIndex(index+3, relativeBase, instructions, d)
	case 7:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		if instructions[paramIndexes[0]] < instructions[paramIndexes[1]] {
			instructions[paramIndexes[2]] = 1
		} else {
			instructions[paramIndexes[2]] = 0
		}
		return executeIndex(index+4, relativeBase, instructions, d)
	case 8:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		if instructions[paramIndexes[0]] == instructions[paramIndexes[1]] {
			instructions[paramIndexes[2]] = 1
		} else {
			instructions[paramIndexes[2]] = 0
		}
		return executeIndex(index+4, relativeBase, instructions, d)
	case 9:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		return executeIndex(index+2, relativeBase+instructions[paramIndexes[0]], instructions, d)
	case 99:
		return instructions
	}
	return instructions
}

func getParameterIndexes(index, relativeBase int64, instructions map[int64]int64, flags []opMode, requiredParams int64) (params []int64) {
	for i := int64(0); i < requiredParams; i++ {
		params = append(params, getParameterIndex(index+i+1, relativeBase, instructions, flags[i]))
	}
	return
}

func getParameterIndex(parameterIndex int64, relativeBase int64, instructions map[int64]int64, mode opMode) int64 {
	switch mode {
	case positionMode:
		return instructions[parameterIndex]
	case immediateMode:
		return parameterIndex
	case relativeMode:
		return instructions[parameterIndex] + relativeBase
	}
	return 0
}

func getFlags(operator int64) []opMode {
	return []opMode{
		opMode(operator / 100 % 10),
		opMode(operator / 1000 % 10),
		opMode(operator / 10000 % 10),
	}
}
