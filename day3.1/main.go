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
	wireOnePoints := make([]string, 0)
	wireTwoPoints := make([]string, 0)

	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")
	wireOneInput := strings.Split(inputArray[0], ",")
	wireTwoInput := strings.Split(inputArray[1], ",")

	currentCoordinates := coordinates{0, 0}
	for _, lineFragmentSpec := range wireOneInput {
		var linePointsCoordinateStrings []string
		linePointsCoordinateStrings, currentCoordinates = computeLineFragments(currentCoordinates, lineFragmentSpec)
		wireOnePoints = append(wireOnePoints, linePointsCoordinateStrings...)
	}

	currentCoordinates = coordinates{0, 0}
	for _, lineFragmentSpec := range wireTwoInput {
		var linePointsCoordinateStrings []string
		linePointsCoordinateStrings, currentCoordinates = computeLineFragments(currentCoordinates, lineFragmentSpec)
		wireTwoPoints = append(wireTwoPoints, linePointsCoordinateStrings...)
	}

	intersections := findIntersections(wireOnePoints, wireTwoPoints)
	var lowestDistance int
	for _, intersection := range intersections {
		if intersection != "0,0" {
			pointCoordinates := strings.Split(intersection, ",")
			pointX, _ := strconv.Atoi(pointCoordinates[0])
			pointY, _ := strconv.Atoi(pointCoordinates[1])
			distance := abs(pointX) + abs(pointY)
			if lowestDistance == 0 || lowestDistance > distance {
				lowestDistance = distance
			}
		}
	}

	fmt.Println(lowestDistance)
}

func computeLineFragments(currentPosition coordinates, lineFragmentSpec string) ([]string, coordinates) {
	var linePoints []string
	var newPosition coordinates
	distance, err := strconv.Atoi(lineFragmentSpec[1:])
	if err != nil {
		panic(err)
	}
	switch lineFragmentSpec[0] {
	case 'L':
		newPosition = coordinates{currentPosition.x - distance, currentPosition.y}
		for i := 0; i > -distance; i-- {
			linePoints = append(linePoints, fmt.Sprintf("%v,%v", currentPosition.x+i, currentPosition.y))
		}
	case 'R':
		newPosition = coordinates{currentPosition.x + distance, currentPosition.y}
		for i := 0; i < distance; i++ {
			linePoints = append(linePoints, fmt.Sprintf("%v,%v", currentPosition.x+i, currentPosition.y))
		}
	case 'U':
		newPosition = coordinates{currentPosition.x, currentPosition.y + distance}
		for i := 0; i < distance; i++ {
			linePoints = append(linePoints, fmt.Sprintf("%v,%v", currentPosition.x, currentPosition.y+i))
		}
	case 'D':
		newPosition = coordinates{currentPosition.x, currentPosition.y - distance}
		for i := 0; i > -distance; i-- {
			linePoints = append(linePoints, fmt.Sprintf("%v,%v", currentPosition.x, currentPosition.y+i))
		}
	}
	return linePoints, newPosition
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func findIntersections(a, b []string) (c []string) {
	m := make(map[string]bool)

	for _, item := range a {
		m[item] = true
	}

	for _, item := range b {
		if _, ok := m[item]; ok {
			c = append(c, item)
		}
	}
	return
}
