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

type dimentionBounds struct {
	lowerBound int
	upperBound int
}

type bounds struct {
	x dimentionBounds
	y dimentionBounds
}

func main() {
	wireOneLines := make([]line, 0)
	wireTwoLines := make([]line, 0)
	gridBounds := bounds{}

	input, err := ioutil.ReadFile("input1.txt")
	if err != nil {
		fmt.Println(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")
	//wireOneInput := strings.Split(inputArray[0], ",")
	wireTwoInput := strings.Split(inputArray[1], ",")
	currentCoordinates := coordinates{0, 0}
	//for _, lineFragmentSpec := range wireOneInput {
	//	var line line
	//	line, currentCoordinates = computeLineFragmentsAndBounds(currentCoordinates, lineFragmentSpec, &gridBounds)
	//	wireOneLines = append(wireOneLines, line)
	//}
	currentCoordinates = coordinates{0, 0}
	for _, lineFragmentSpec := range wireTwoInput {
		var line line
		line, currentCoordinates = computeLineFragmentsAndBounds(currentCoordinates, lineFragmentSpec, &gridBounds)
		wireTwoLines = append(wireTwoLines, line)
	}

	fmt.Println(gridBounds)

	grid := make([][]int, abs(gridBounds.x.lowerBound)+gridBounds.x.upperBound)
	for i := range grid {
		grid[i] = make([]int, abs(gridBounds.y.lowerBound)+gridBounds.y.upperBound)
	}
	fmt.Println("Grid compilation complete")
	for _, line := range wireOneLines {
		plotLine(line, grid, gridBounds, 1)
	}
	for _, line := range wireTwoLines {
		plotLine(line, grid, gridBounds, 2)
	}
}

func computeLineFragmentsAndBounds(currentPosition coordinates, lineFragmentSpec string, gridBounds *bounds) (line, coordinates) {
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
		if currentPosition.x-distance < gridBounds.x.lowerBound {
			gridBounds.x.lowerBound = currentPosition.x - distance
		}
		newPosition = coordinates{currentPosition.x - distance, currentPosition.y}
	case 'R':
		if currentPosition.x+distance > gridBounds.x.upperBound {
			gridBounds.x.upperBound = currentPosition.x + distance
		}
		newPosition = coordinates{currentPosition.x + distance, currentPosition.y}
	case 'U':
		if currentPosition.y+distance > gridBounds.y.upperBound {
			gridBounds.y.upperBound = currentPosition.y + distance
		}
		newPosition = coordinates{currentPosition.x, currentPosition.y + distance}
	case 'D':
		if currentPosition.y-distance < gridBounds.y.lowerBound {
			gridBounds.y.lowerBound = currentPosition.y - distance
		}
		newPosition = coordinates{currentPosition.x, currentPosition.y - distance}
	}
	line.end = newPosition
	return line, newPosition
}

func plotLine(line line, grid [][]int, gridBounds bounds, lineNumber int) {
	xOffset := abs(gridBounds.x.lowerBound)
	yOffset := abs(gridBounds.y.lowerBound)

	if line.beginning.x == line.end.x {
		if line.end.y-line.beginning.y < 0 {
			for i := 0; i > line.end.y-line.beginning.y; i-- {
				grid[line.beginning.x+xOffset][line.beginning.y+yOffset+i] = lineNumber
			}
		} else {
			for i := 0; i < line.end.y-line.beginning.y; i++ {
				grid[line.beginning.x+xOffset][line.beginning.y+yOffset+i] = lineNumber
			}
		}
	} else {
		if line.end.x-line.beginning.x < 0 {
			for i := 0; i > line.beginning.x-line.end.x; i-- {
				grid[line.beginning.x+xOffset+i][line.beginning.y+yOffset] = lineNumber
			}
		} else {
			for i := 0; i < line.end.x-line.beginning.x; i++ {
				fmt.Println(line, xOffset, gridBounds.x.upperBound)
				grid[line.beginning.x+xOffset+i][line.beginning.y+yOffset] = lineNumber
			}
		}
	}
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
