package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

type coordinates struct {
	x, y int
}

type asteroid struct {
	visibleAsteroids      int
	tangentsOfObstruction map[int]bool
}

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

func findElementsAtDistance(point coordinates, distance int, spaceMap [][]rune) []coordinates {
	for i := -distance; i < distance; i++ {
		for j := -distance; j < distance; j++ {
			fmt.Println(point.x+i, point.y+j)
		}
	}
}
