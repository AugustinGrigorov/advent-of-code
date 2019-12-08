package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
	"sync"
)

type state struct {
	ampIndex         int
	instructionIndex int
	instructions     []int
	setting          int
	secondInput      bool
}

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

	generateAllInputOptions(5, []int{5, 6, 7, 8, 9}, &possibleOptions)
	wg.Add(len(possibleOptions))
	outputChannel := make(chan int, len(possibleOptions))

	for _, option := range possibleOptions {
		go func(option []int) {
			var output int
			indexStateMap := make(map[int]*state)
			for index, setting := range option {
				instructionsCopy := make([]int, len(instructions))
				copy(instructionsCopy, instructions)
				newState := state{
					ampIndex:     index,
					instructions: instructionsCopy,
					setting:      setting,
				}
				indexStateMap[index] = &newState
			}
			executeIndex(indexStateMap[0], &output, indexStateMap)
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

func executeIndex(state *state, output *int, ampStates map[int]*state) []int {
	operator := state.instructions[state.instructionIndex]
	var param1, param2 int

	switch operator % 100 {
	case 1:
		firstParamImmediateMode, secondParamImmediateMode, thirdParamImmediateMode := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			param1 = state.instructions[state.instructionIndex+1]
		} else {
			param1 = state.instructions[state.instructions[state.instructionIndex+1]]
		}
		if secondParamImmediateMode {
			param2 = state.instructions[state.instructionIndex+2]
		} else {
			param2 = state.instructions[state.instructions[state.instructionIndex+2]]
		}
		if thirdParamImmediateMode {
			state.instructions[state.instructionIndex+3] = param1 + param2
		} else {
			state.instructions[state.instructions[state.instructionIndex+3]] = param1 + param2
		}
		state.instructionIndex += 4
		return executeIndex(state, output, ampStates)
	case 2:
		firstParamImmediateMode, secondParamImmediateMode, thirdParamImmediateMode := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			param1 = state.instructions[state.instructionIndex+1]
		} else {
			param1 = state.instructions[state.instructions[state.instructionIndex+1]]
		}
		if secondParamImmediateMode {
			param2 = state.instructions[state.instructionIndex+2]
		} else {
			param2 = state.instructions[state.instructions[state.instructionIndex+2]]
		}
		if thirdParamImmediateMode {
			state.instructions[state.instructionIndex+3] = param1 * param2
		} else {
			state.instructions[state.instructions[state.instructionIndex+3]] = param1 * param2
		}
		state.instructionIndex += 4
		return executeIndex(state, output, ampStates)
	case 3:
		firstParamImmediateMode, _, _ := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			if state.secondInput {
				state.instructions[state.instructionIndex+1] = *output
			} else {
				state.secondInput = true
				state.instructions[state.instructionIndex+1] = state.setting
			}
		} else {
			if state.secondInput {
				state.instructions[state.instructions[state.instructionIndex+1]] = *output
			} else {
				state.secondInput = true
				state.instructions[state.instructions[state.instructionIndex+1]] = state.setting
			}
		}
		state.instructionIndex += 2
		return executeIndex(state, output, ampStates)
	case 4:
		firstParamImmediateMode, _, _ := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			param1 = state.instructions[state.instructionIndex+1]
		} else {
			param1 = state.instructions[state.instructions[state.instructionIndex+1]]
		}
		*output = param1
		state.instructionIndex += 2
		var nextAmp int
		if state.ampIndex == 4 {
			nextAmp = 0
		} else {
			nextAmp = state.ampIndex + 1
		}
		executeIndex(ampStates[nextAmp], output, ampStates)
	case 5:
		firstParamImmediateMode, secondParamImmediateMode, _ := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			param1 = state.instructions[state.instructionIndex+1]
		} else {
			param1 = state.instructions[state.instructions[state.instructionIndex+1]]
		}
		if secondParamImmediateMode {
			param2 = state.instructions[state.instructionIndex+2]
		} else {
			param2 = state.instructions[state.instructions[state.instructionIndex+2]]
		}
		if param1 > 0 {
			state.instructionIndex = param2
			return executeIndex(state, output, ampStates)
		}
		state.instructionIndex += 3
		return executeIndex(state, output, ampStates)
	case 6:
		firstParamImmediateMode, secondParamImmediateMode, _ := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			param1 = state.instructions[state.instructionIndex+1]
		} else {
			param1 = state.instructions[state.instructions[state.instructionIndex+1]]
		}
		if secondParamImmediateMode {
			param2 = state.instructions[state.instructionIndex+2]
		} else {
			param2 = state.instructions[state.instructions[state.instructionIndex+2]]
		}
		if param1 == 0 {
			state.instructionIndex = param2
			return executeIndex(state, output, ampStates)
		}
		state.instructionIndex += 3
		return executeIndex(state, output, ampStates)
	case 7:
		firstParamImmediateMode, secondParamImmediateMode, thirdParamImmediateMode := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			param1 = state.instructions[state.instructionIndex+1]
		} else {
			param1 = state.instructions[state.instructions[state.instructionIndex+1]]
		}
		if secondParamImmediateMode {
			param2 = state.instructions[state.instructionIndex+2]
		} else {
			param2 = state.instructions[state.instructions[state.instructionIndex+2]]
		}
		var value int
		if param1 < param2 {
			value = 1
		}
		if thirdParamImmediateMode {
			state.instructions[state.instructionIndex+3] = value
		} else {
			state.instructions[state.instructions[state.instructionIndex+3]] = value
		}
		state.instructionIndex += 4
		return executeIndex(state, output, ampStates)
	case 8:
		firstParamImmediateMode, secondParamImmediateMode, thirdParamImmediateMode := getFlags(state.instructions[state.instructionIndex])
		if firstParamImmediateMode {
			param1 = state.instructions[state.instructionIndex+1]
		} else {
			param1 = state.instructions[state.instructions[state.instructionIndex+1]]
		}
		if secondParamImmediateMode {
			param2 = state.instructions[state.instructionIndex+2]
		} else {
			param2 = state.instructions[state.instructions[state.instructionIndex+2]]
		}
		var value int
		if param1 == param2 {
			value = 1
		}
		if thirdParamImmediateMode {
			state.instructions[state.instructionIndex+3] = value
		} else {
			state.instructions[state.instructions[state.instructionIndex+3]] = value
		}
		state.instructionIndex += 4
		return executeIndex(state, output, ampStates)
	case 99:
		return state.instructions
	}
	return state.instructions
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
