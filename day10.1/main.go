package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")
	spaceMap := make([][]rune, len(inputArray))
	for x, _ := range spaceMap {
		spaceMap[x] = make([]rune, len(inputArray))
		for y, el := range inputArray[x] {
			spaceMap[x][y] = el
		}
	}
	fmt.Println(spaceMap)
}
