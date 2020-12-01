package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

const input = 1

func main() {
	input, err := ioutil.ReadFile("input.txt")
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
	executeIndex(0, outputArray)
}

func executeIndex(index int, array []int) []int {
	operator := array[index]
	var param1, param2 int

	switch operator % 100 {
	case 1:
		firstParamImmediateMode, secondParamImmediateMode, thirdParamImmediateMode := getFlags(array[index])
		if firstParamImmediateMode {
			param1 = array[index+1]
		} else {
			param1 = array[array[index+1]]
		}
		if secondParamImmediateMode {
			param2 = array[index+2]
		} else {
			param2 = array[array[index+2]]
		}
		if thirdParamImmediateMode {
			array[index+3] = param1 + param2
		} else {
			array[array[index+3]] = param1 + param2
		}
		return executeIndex(index+4, array)
	case 2:
		firstParamImmediateMode, secondParamImmediateMode, thirdParamImmediateMode := getFlags(array[index])
		if firstParamImmediateMode {
			param1 = array[index+1]
		} else {
			param1 = array[array[index+1]]
		}
		if secondParamImmediateMode {
			param2 = array[index+2]
		} else {
			param2 = array[array[index+2]]
		}
		if thirdParamImmediateMode {
			array[index+3] = param1 * param2
		} else {
			array[array[index+3]] = param1 * param2
		}
		return executeIndex(index+4, array)
	case 3:
		firstParamImmediateMode, _, _ := getFlags(array[index])
		if firstParamImmediateMode {
			array[index+1] = input
		} else {
			array[array[index+1]] = input
		}
		return executeIndex(index+2, array)
	case 4:
		firstParamImmediateMode, _, _ := getFlags(array[index])
		if firstParamImmediateMode {
			param1 = array[index+1]
		} else {
			param1 = array[array[index+1]]
		}
		fmt.Println(param1)
		return executeIndex(index+2, array)
	case 99:
		return array
	}
	return array
}

func getFlags(operator int) (firstParamImmediateMode bool, secondParamImmediateMode bool, thirdParamImmediateMode bool) {
	if operator > 10000 {
		thirdParamImmediateMode = true
		if operator/1000%10 == 1 {
			secondParamImmediateMode = true
		}
		if operator/100%10 == 1 {
			firstParamImmediateMode = true
		}
		return
	}
	if operator > 1000 {
		secondParamImmediateMode = true
		if operator/100%10 == 1 {
			firstParamImmediateMode = true
		}
		return
	}
	if operator > 100 {
		firstParamImmediateMode = true
		return
	}
	return false, false, false
}
