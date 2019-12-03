package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

type coordinates struct {
	x int
	y int
}

type line struct {
	beginning coordinates
	end       coordinates
}

func main() {
	wireOneLines := make([]line, 0)
	wireTwoLines := make([]line, 0)
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		fmt.Println(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")
	wireOneInput := strings.Split(inputArray[0], ",")
	wireTwoInput := strings.Split(inputArray[1], ",")
	currentCoordinates := coordinates{0, 0}
	for _, lineFragmentSpec := range wireOneInput {
		var line line
		line, currentCoordinates = plotLineFragment(currentCoordinates, lineFragmentSpec)
		wireOneLines = append(wireOneLines, line)
	}
	currentCoordinates = coordinates{0, 0}
	for _, lineFragmentSpec := range wireTwoInput {
		var line line
		line, currentCoordinates = plotLineFragment(currentCoordinates, lineFragmentSpec)
		wireTwoLines = append(wireTwoLines, line)
	}
	fmt.Println(wireOneLines, wireTwoLines)
}

func plotLineFragment(currentPosition coordinates, lineFragmentSpec string) (line, coordinates) {
	distance, err := strconv.Atoi(lineFragmentSpec[1:])
	line := line{
		beginning: currentPosition,
	}
	var newPosition coordinates
	if err != nil {
		fmt.Printf("can't parse distance from %v %v \n", lineFragmentSpec, err)
	}
	switch lineFragmentSpec[0] {
	case 'L':
		newPosition = coordinates{currentPosition.x - distance, currentPosition.y}
	case 'R':
		newPosition = coordinates{currentPosition.x + distance, currentPosition.y}
	case 'U':
		newPosition = coordinates{currentPosition.x, currentPosition.y + distance}
	case 'D':
		newPosition = coordinates{currentPosition.x, currentPosition.y - distance}
	}
	line.end = newPosition
	return line, newPosition
}

func linesCross(lineOne, lineTwo line) bool {
	return false
}
