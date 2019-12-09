package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

const input = 5

type opMode int

const (
	positionMode  opMode = 0
	immediateMode opMode = 1
	relativeMode  opMode = 2
)

func main() {
	input, err := ioutil.ReadFile("../day5.2/input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), ",")
	outputArray := make([]int, len(inputArray))
	for index, opcode := range inputArray {
		outputArray[index], err = strconv.Atoi(opcode)
		if err != nil {
			panic(err)
		}
	}
	executeIndex(0, 0, outputArray)
}

func executeIndex(index, relativeBase int, instructions []int) []int {
	operator := instructions[index]
	switch operator % 100 {
	case 1:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 3)
		*params[2] = *params[0] + *params[1]
		return executeIndex(index+4, relativeBase, instructions)
	case 2:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 3)
		*params[2] = *params[0] * *params[1]
		return executeIndex(index+4, relativeBase, instructions)
	case 3:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 1)
		*params[0] = input
		return executeIndex(index+2, relativeBase, instructions)
	case 4:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 1)
		fmt.Println(*params[0])
		return executeIndex(index+2, relativeBase, instructions)
	case 5:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 2)
		if *params[0] > 0 {
			return executeIndex(*params[1], relativeBase, instructions)
		}
		return executeIndex(index+3, relativeBase, instructions)
	case 6:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 2)
		if *params[0] == 0 {
			return executeIndex(*params[1], relativeBase, instructions)
		}
		return executeIndex(index+3, relativeBase, instructions)
	case 7:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 3)
		if *params[0] < *params[1] {
			*params[2] = 1
		} else {
			*params[2] = 0
		}
		return executeIndex(index+4, relativeBase, instructions)
	case 8:
		flags := getFlags(operator)
		params := getParameters(index, relativeBase, instructions, flags, 3)
		if *params[0] == *params[1] {
			*params[2] = 1
		} else {
			*params[2] = 0
		}
		return executeIndex(index+4, relativeBase, instructions)
	case 99:
		return instructions
	}
	return instructions
}

func getParameters(index, relativeBase int, instructions []int, flags []opMode, requiredParams int) (params []*int) {
	for i := 0; i < requiredParams; i++ {
		params = append(params, getParameter(index+i, relativeBase, instructions, flags[i]))
	}
	return
}

func getParameter(index int, relativeBase int, instructions []int, mode opMode) *int {
	switch mode {
	case positionMode:
		return &instructions[instructions[index+1]]
	case immediateMode:
		return &instructions[index+1]
	case relativeMode:
		return &instructions[instructions[relativeBase+1]]
	}
	return nil
}

func getFlags(operator int) []opMode {
	return []opMode{
		opMode(operator / 100 % 10),
		opMode(operator / 1000 % 10),
		opMode(operator / 10000 % 10),
	}
}
