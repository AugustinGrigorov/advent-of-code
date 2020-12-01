package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), ",")
	patternArray := make([]int, len(inputArray))
	for index, opcode := range inputArray {
		patternArray[index], err = strconv.Atoi(opcode)
		if err != nil {
			panic(err)
		}
	}
	for i := 0; i < 100; i++ {
		for j := 0; j < 100; j++ {
			patternArray[1] = i
			patternArray[2] = j

			outputArray := make([]int, len(inputArray))
			copy(outputArray, patternArray)
			if executeIndex(0, outputArray)[0] == 19690720 {
				fmt.Println(100*i + j)
			}
		}
	}
}

func executeIndex(index int, array []int) []int {
	switch array[index] {
	case 1:
		input1, input2 := array[array[index+1]], array[array[index+2]]
		array[array[index+3]] = input1 + input2
		return executeIndex(index+4, array)
	case 2:
		input1, input2 := array[array[index+1]], array[array[index+2]]
		array[array[index+3]] = input1 * input2
		return executeIndex(index+4, array)
	case 99:
		return array
	}
	return array
}
