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

type arcade struct {
	instructionsExecuted int
	blockTiles           int
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

	arc := arcade{}

	executeIndex(0, 0, output, &arc)
	fmt.Println(arc.blockTiles)
}

func (a *arcade) executeCommand(command int64) {
	if a.instructionsExecuted%3 == 2 && command == 2 {
		a.blockTiles++
	}
	a.instructionsExecuted++
}

func executeIndex(index, relativeBase int64, instructions map[int64]int64, a *arcade) map[int64]int64 {
	operator := instructions[index]
	switch operator % 100 {
	case 1:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		instructions[paramIndexes[2]] = instructions[paramIndexes[0]] + instructions[paramIndexes[1]]
		return executeIndex(index+4, relativeBase, instructions, a)
	case 2:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		instructions[paramIndexes[2]] = instructions[paramIndexes[0]] * instructions[paramIndexes[1]]
		return executeIndex(index+4, relativeBase, instructions, a)
	case 3:
		panic("input operation not supported")
	case 4:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		a.executeCommand(instructions[paramIndexes[0]])
		return executeIndex(index+2, relativeBase, instructions, a)
	case 5:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 2)
		if instructions[paramIndexes[0]] > 0 {
			return executeIndex(instructions[paramIndexes[1]], relativeBase, instructions, a)
		}
		return executeIndex(index+3, relativeBase, instructions, a)
	case 6:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 2)
		if instructions[paramIndexes[0]] == 0 {
			return executeIndex(instructions[paramIndexes[1]], relativeBase, instructions, a)
		}
		return executeIndex(index+3, relativeBase, instructions, a)
	case 7:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		if instructions[paramIndexes[0]] < instructions[paramIndexes[1]] {
			instructions[paramIndexes[2]] = 1
		} else {
			instructions[paramIndexes[2]] = 0
		}
		return executeIndex(index+4, relativeBase, instructions, a)
	case 8:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 3)
		if instructions[paramIndexes[0]] == instructions[paramIndexes[1]] {
			instructions[paramIndexes[2]] = 1
		} else {
			instructions[paramIndexes[2]] = 0
		}
		return executeIndex(index+4, relativeBase, instructions, a)
	case 9:
		flags := getFlags(operator)
		paramIndexes := getParameterIndexes(index, relativeBase, instructions, flags, 1)
		return executeIndex(index+2, relativeBase+instructions[paramIndexes[0]], instructions, a)
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
