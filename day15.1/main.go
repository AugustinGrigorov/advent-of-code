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

var clockwiseRotation = []direction{north, east, south, west}
var visitedCoordinates = make(map[coordinates]bool)

type droid struct {
	position       coordinates
	directionIndex int
	blocked        bool
	stepsBack      []int
	stepsBackIndex int
}

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), ",")
	output := make(map[int64]int64, len(inputArray))
	for index, opcode := range inputArray {
		output[int64(index)], err = strconv.ParseInt(opcode, 10, 64)
		if err != nil {
			panic(err)
		}
	}

	d := droid{}

	executeIndex(0, 0, output, &d)
}

func (d *droid) output(status int64) {
	newPos := d.getMoveCoordinates(d.getDirection())
	visitedCoordinates[newPos] = true

	switch status {
	case 0:
		d.directionIndex++
	case 1:
		if !d.blocked {
			if len(d.stepsBack) == d.stepsBackIndex {
				d.stepsBack = append(d.stepsBack, d.directionIndex+2)
				d.stepsBackIndex++
			} else {
				d.stepsBack[d.stepsBackIndex] = d.directionIndex + 2
				d.stepsBackIndex++
			}
			d.directionIndex = 0
		} else {
			d.directionIndex = d.stepsBack[d.stepsBackIndex]
			d.stepsBackIndex--
		}
		d.position = newPos
		fmt.Printf("%v, %v\n", d.position.x, d.position.y)
	case 2:
		d.position = newPos
		fmt.Println("Found problem at", d.position)
	}
}

func (d *droid) input() direction {
	var moves int

	for visitedCoordinates[d.getMoveCoordinates(d.getDirection())] {
		d.directionIndex++
		moves++
		if moves == 4 {
			d.blocked = true
			break
		}
	}
	d.blocked = false

	return d.getDirection()
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

func (d *droid) getDirection() direction {
	return clockwiseRotation[d.directionIndex%4]
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
		input := d.input()
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		instructions[paramIndexes[0]] = int64(input)
		return executeIndex(index+2, relativeBase, instructions, d)
	case 4:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		d.output(instructions[paramIndexes[0]])
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
