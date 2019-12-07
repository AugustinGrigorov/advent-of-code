package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
	"sync"
)

func main() {
	var possibleOptions [][]int
	var wg sync.WaitGroup

	data, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(data)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), ",")
	instructions := make([]int, len(inputArray))
	for index, opcode := range inputArray {
		instructions[index], err = strconv.Atoi(opcode)
		if err != nil {
			panic(err)
		}
	}

	generateAllInputOptions(5, []int{0, 1, 2, 3, 4}, &possibleOptions)
	wg.Add(len(possibleOptions))
	outputChannel := make(chan int, len(possibleOptions))

	for _, option := range possibleOptions {
		go func(option []int) {
			var output int
			for _, setting := range option {
				instructionsCopy := make([]int, len(instructions))
				copy(instructionsCopy, instructions)
				executeIndex(0, instructionsCopy, setting, &output, false)
			}
			outputChannel <- output
			wg.Done()
		}(option)
	}

	wg.Wait()
	close(outputChannel)

	var highestOutput int
	for output := range outputChannel {
		if output > highestOutput {
			highestOutput = output
		}
	}
	fmt.Println(highestOutput)
}

func executeIndex(index int, array []int, input int, output *int, secondInput bool) []int {
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
		return executeIndex(index+4, array, input, output, secondInput)
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
		return executeIndex(index+4, array, input, output, secondInput)
	case 3:
		firstParamImmediateMode, _, _ := getFlags(array[index])
		if firstParamImmediateMode {
			if secondInput {
				array[index+1] = *output
			} else {
				secondInput = true
				array[index+1] = input
			}
		} else {
			if secondInput {
				array[array[index+1]] = *output
			} else {
				secondInput = true
				array[array[index+1]] = input
			}
		}
		return executeIndex(index+2, array, input, output, secondInput)
	case 4:
		firstParamImmediateMode, _, _ := getFlags(array[index])
		if firstParamImmediateMode {
			param1 = array[index+1]
		} else {
			param1 = array[array[index+1]]
		}
		*output = param1
		// fmt.Println(*output)
		return executeIndex(index+2, array, input, output, secondInput)
	case 5:
		firstParamImmediateMode, secondParamImmediateMode, _ := getFlags(array[index])
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
		if param1 > 0 {
			return executeIndex(param2, array, input, output, secondInput)
		}
		return executeIndex(index+3, array, input, output, secondInput)
	case 6:
		firstParamImmediateMode, secondParamImmediateMode, _ := getFlags(array[index])
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
		if param1 == 0 {
			return executeIndex(param2, array, input, output, secondInput)
		}
		return executeIndex(index+3, array, input, output, secondInput)
	case 7:
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
		var value int
		if param1 < param2 {
			value = 1
		}
		if thirdParamImmediateMode {
			array[index+3] = value
		} else {
			array[array[index+3]] = value
		}
		return executeIndex(index+4, array, input, output, secondInput)
	case 8:
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
		var value int
		if param1 == param2 {
			value = 1
		}
		if thirdParamImmediateMode {
			array[index+3] = value
		} else {
			array[array[index+3]] = value
		}
		return executeIndex(index+4, array, input, output, secondInput)
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

func generateAllInputOptions(n int, elements []int, possibleOptions *[][]int) {
	if n == 1 {
		option := make([]int, len(elements))
		copy(option, elements)
		*possibleOptions = append(*possibleOptions, option)
	} else {
		for i := 0; i < n-1; i++ {
			generateAllInputOptions(n-1, elements, possibleOptions)
			if n%2 == 0 {
				el1, el2 := elements[i], elements[n-1]
				elements[i], elements[n-1] = el2, el1
			} else {
				el1, el2 := elements[0], elements[n-1]
				elements[0], elements[n-1] = el2, el1
			}
		}
		generateAllInputOptions(n-1, elements, possibleOptions)
	}
}
