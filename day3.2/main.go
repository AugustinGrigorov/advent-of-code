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

func main() {
	wireOnePointsAndDistanceFromStart := make(map[string]int)
	wireTwoPointsAndDistanceFromStart := make(map[string]int)

	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")
	wireOneInput := strings.Split(inputArray[0], ",")
	wireTwoInput := strings.Split(inputArray[1], ",")

	currentCoordinates := coordinates{0, 0}
	distance := 0
	for _, lineFragmentSpec := range wireOneInput {
		var additionalDistance int
		currentCoordinates, additionalDistance = addLineCoordinatesAndDistances(currentCoordinates, lineFragmentSpec, distance, wireOnePointsAndDistanceFromStart)
		distance += additionalDistance
	}

	currentCoordinates = coordinates{0, 0}
	distance = 0
	for _, lineFragmentSpec := range wireTwoInput {
		var additionalDistance int
		currentCoordinates, additionalDistance = addLineCoordinatesAndDistances(currentCoordinates, lineFragmentSpec, distance, wireTwoPointsAndDistanceFromStart)
		distance += additionalDistance
	}

	var lowestDistance int
	for coordinates := range wireTwoPointsAndDistanceFromStart {
		if _, ok := wireOnePointsAndDistanceFromStart[coordinates]; ok {
			combinedDistance := wireTwoPointsAndDistanceFromStart[coordinates] + wireOnePointsAndDistanceFromStart[coordinates]
			if combinedDistance > 0 {
				if lowestDistance == 0 || combinedDistance < lowestDistance {
					lowestDistance = combinedDistance
				}
			}
		}
	}
	fmt.Println(lowestDistance)
}

func addLineCoordinatesAndDistances(currentPosition coordinates, lineFragmentSpec string, currentDistance int, coordinateAndDistance map[string]int) (coordinates, int) {
	var newPosition coordinates
	distance, err := strconv.Atoi(lineFragmentSpec[1:])
	if err != nil {
		panic(err)
	}
	switch lineFragmentSpec[0] {
	case 'L':
		newPosition = coordinates{currentPosition.x - distance, currentPosition.y}
		for i := 0; i > -distance; i-- {
			if _, ok := coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x+i, currentPosition.y)]; !ok {
				coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x+i, currentPosition.y)] = currentDistance + abs(i)
			}
		}
	case 'R':
		newPosition = coordinates{currentPosition.x + distance, currentPosition.y}
		for i := 0; i < distance; i++ {
			if _, ok := coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x+i, currentPosition.y)]; !ok {
				coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x+i, currentPosition.y)] = currentDistance + abs(i)
			}
		}
	case 'U':
		newPosition = coordinates{currentPosition.x, currentPosition.y + distance}
		for i := 0; i < distance; i++ {
			if _, ok := coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x, currentPosition.y+i)]; !ok {
				coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x, currentPosition.y+i)] = currentDistance + abs(i)
			}
		}
	case 'D':
		newPosition = coordinates{currentPosition.x, currentPosition.y - distance}
		for i := 0; i > -distance; i-- {
			if _, ok := coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x, currentPosition.y+i)]; !ok {
				coordinateAndDistance[fmt.Sprintf("%v,%v", currentPosition.x, currentPosition.y+i)] = currentDistance + abs(i)
			}
		}
	}
	return newPosition, distance
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
