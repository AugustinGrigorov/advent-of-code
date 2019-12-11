package main

import (
	"fmt"
	"io/ioutil"
	"math"
	"sort"
	"strings"
)

type coordinates struct {
	x, y float64
}

type asteroid struct {
	visibleAsteroids      int
	tangentsOfObstruction map[string]bool
}

type distance struct {
	coordinates
	value float64
}

type byDistance []distance

func (d byDistance) Len() int           { return len(d) }
func (d byDistance) Swap(i, j int)      { d[i], d[j] = d[j], d[i] }
func (d byDistance) Less(i, j int) bool { return d[i].value < d[j].value }

func main() {
	var asteroidCoordinates []coordinates

	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")

	for y, row := range inputArray {
		for x, el := range row {
			if el == '#' {
				asteroidCoordinates = append(asteroidCoordinates, coordinates{float64(x), float64(y)})
			}
		}
	}

	var mostVisibleAsteroids int

	for _, firstCoordinates := range asteroidCoordinates {
		var distances []distance
		currentAsteroid := asteroid{
			tangentsOfObstruction: make(map[string]bool),
		}
		for _, secondCoordinates := range asteroidCoordinates {
			if firstCoordinates != secondCoordinates {
				distances = append(distances, distance{secondCoordinates, findDistance(firstCoordinates, secondCoordinates)})
			}
		}
		sort.Sort(byDistance(distances))
		for _, distance := range distances {
			quadrant := getQuadrant(firstCoordinates, distance.coordinates)
			tangent := (firstCoordinates.x - distance.x) / (firstCoordinates.y - distance.y)
			if !currentAsteroid.tangentsOfObstruction[fmt.Sprintf("%v_%v", quadrant, tangent)] {
				currentAsteroid.visibleAsteroids++
				currentAsteroid.tangentsOfObstruction[fmt.Sprintf("%v_%v", quadrant, tangent)] = true
			}
		}
		if currentAsteroid.visibleAsteroids > mostVisibleAsteroids {
			mostVisibleAsteroids = currentAsteroid.visibleAsteroids
		}
	}

	fmt.Println(mostVisibleAsteroids)
}

func findDistance(a, b coordinates) float64 {
	return math.Sqrt(math.Pow(a.x-b.x, 2) + math.Pow(a.y-b.y, 2))
}

func getQuadrant(a, b coordinates) int {
	if a.x > b.x && a.y > b.y {
		return 1
	}
	if a.x < b.x && a.y > b.y {
		return 2
	}
	if a.x > b.x && a.y < b.y {
		return 3
	}
	if a.x < b.x && a.y < b.y {
		return 4
	}
	return 0
}
