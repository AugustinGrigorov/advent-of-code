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
	x, y int
}

type robot struct {
	instructionsExecuted int
	coordinatesPainted   map[string]int64
	currentDirection     int
	currentCoordinates   coordinates
	currentTile          int64
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

	rob := robot{
		coordinatesPainted: make(map[string]int64),
	}

	executeIndex(0, 0, output, &rob)
	fmt.Println(len(rob.coordinatesPainted))
}

func (r *robot) executeCommand(command int64) {
	switch r.instructionsExecuted % 2 {
	case 1:
		switch command {
		case 0:
			r.currentDirection--
		case 1:
			r.currentDirection++
		default:
			panic("invalid rotation")
		}
		switch loopingMod(r.currentDirection, 4) {
		case 0:
			r.currentCoordinates.y++
		case 1:
			r.currentCoordinates.x++
		case 2:
			r.currentCoordinates.y--
		case 3:
			r.currentCoordinates.x--
		default:
			panic("invalid direction")
		}
		r.currentTile = r.coordinatesPainted[fmt.Sprintf("%v:%v", r.currentCoordinates.x, r.currentCoordinates.y)]
	case 0:
		r.coordinatesPainted[fmt.Sprintf("%v:%v", r.currentCoordinates.x, r.currentCoordinates.y)] = command
	}
	r.instructionsExecuted++
}

func loopingMod(x, m int) int {
	return (x%m + m) % m
}

func executeIndex(index, relativeBase int64, instructions map[int64]int64, r *robot) map[int64]int64 {
	operator := instructions[index]
	switch operator % 100 {
	case 1:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		instructions[paramIndexes[2]] = instructions[paramIndexes[0]] + instructions[paramIndexes[1]]
		return executeIndex(index+4, relativeBase, instructions, r)
	case 2:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		instructions[paramIndexes[2]] = instructions[paramIndexes[0]] * instructions[paramIndexes[1]]
		return executeIndex(index+4, relativeBase, instructions, r)
	case 3:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		instructions[paramIndexes[0]] = r.currentTile
		return executeIndex(index+2, relativeBase, instructions, r)
	case 4:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		r.executeCommand(instructions[paramIndexes[0]])
		return executeIndex(index+2, relativeBase, instructions, r)
	case 5:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 2)
		if instructions[paramIndexes[0]] > 0 {
			return executeIndex(instructions[paramIndexes[1]], relativeBase, instructions, r)
		}
		return executeIndex(index+3, relativeBase, instructions, r)
	case 6:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 2)
		if instructions[paramIndexes[0]] == 0 {
			return executeIndex(instructions[paramIndexes[1]], relativeBase, instructions, r)
		}
		return executeIndex(index+3, relativeBase, instructions, r)
	case 7:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		if instructions[paramIndexes[0]] < instructions[paramIndexes[1]] {
			instructions[paramIndexes[2]] = 1
		} else {
			instructions[paramIndexes[2]] = 0
		}
		return executeIndex(index+4, relativeBase, instructions, r)
	case 8:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		if instructions[paramIndexes[0]] == instructions[paramIndexes[1]] {
			instructions[paramIndexes[2]] = 1
		} else {
			instructions[paramIndexes[2]] = 0
		}
		return executeIndex(index+4, relativeBase, instructions, r)
	case 9:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		return executeIndex(index+2, relativeBase+instructions[paramIndexes[0]], instructions, r)
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
