package main

import (
	"fmt"
	"io/ioutil"
	"strings"
  "strconv"
)

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		fmt.Println(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), ",")
  outputArray := make([]int, len(inputArray))
  for index, opcode := range inputArray {
    outputArray[index], err = strconv.Atoi(opcode)
    if err != nil {
      fmt.Println(err)
    }
  }
  
  fmt.Println(executeIndex(0, outputArray))
}

func executeIndex(index int, array []int) []int {
  switch array[index] {
  	case 1:
      input1, input2 := array[array[index + 1]], array[array[index + 2]]
  		array[array[index + 3]] = input1 + input2
      return executeIndex(index + 4, array)
  	case 2:
      input1, input2 := array[array[index + 1]], array[array[index + 2]]
    	array[array[index + 3]] = input1 * input2
      return executeIndex(index + 4, array)
  	case 99:
  		return array
	}
  return array
}
