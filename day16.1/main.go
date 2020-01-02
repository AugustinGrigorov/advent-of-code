package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

var basePattern = []int{0, 1, 0, -1}

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	currentMessage := strings.Trim(inputString, "\n")

	for i := 0; i < 100; i++ {
		currentMessage = encode(currentMessage)
	}
	fmt.Println(currentMessage[:8])
}

func encode(input string) string {
	inputArray := strings.Split(input, "")
	var result string
	for index := range inputArray {
		pat := getRepeatingPattern(index + 1)
		var resultingDigit int
		for index, rawDigit := range inputArray {
			digit, err := strconv.Atoi(rawDigit)
			if err != nil {
				panic("unexpected input")
			}
			resultingDigit += digit * pat[(index+1)%len(pat)]
		}
		result += strconv.Itoa(abs(resultingDigit % 10))
	}
	return result
}

func getRepeatingPattern(times int) []int {
	var result []int
	for _, digit := range basePattern {
		for i := 0; i < times; i++ {
			result = append(result, digit)
		}
	}
	return result
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
