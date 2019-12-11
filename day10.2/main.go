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
	var laserLocation coordinates
	var laserQuadrants [][]distance

	for _, firstCoordinates := range asteroidCoordinates {
		var distances []distance
		quadrants := make([][]distance, 4)
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
			quadrants[quadrant] = append(quadrants[quadrant], distance)
			tangent := (firstCoordinates.x - distance.x) / (firstCoordinates.y - distance.y)
			if !currentAsteroid.tangentsOfObstruction[fmt.Sprintf("%v_%v", quadrant, tangent)] {
				currentAsteroid.visibleAsteroids++
				currentAsteroid.tangentsOfObstruction[fmt.Sprintf("%v_%v", quadrant, tangent)] = true
			}
		}
		if currentAsteroid.visibleAsteroids > mostVisibleAsteroids {
			laserLocation = firstCoordinates
			laserQuadrants = quadrants
			mostVisibleAsteroids = currentAsteroid.visibleAsteroids
		}
	}

	var asteroidsDestroyed int
	alreadyDestroyed := make(map[string]bool)
	currentQuadrant := 0

	for {
		laser := asteroid{
			tangentsOfObstruction: make(map[string]bool),
		}
		asteroidsForDestruction := make(map[float64]coordinates)
		for _, distance := range laserQuadrants[currentQuadrant] {
			tangent := (laserLocation.x - distance.x) / (laserLocation.y - distance.y)
			if !alreadyDestroyed[fmt.Sprintf("%v:%v", distance.x, distance.y)] {
				if !laser.tangentsOfObstruction[fmt.Sprintf("%v_%v", currentQuadrant, tangent)] {
					if currentQuadrant%2 == 0 {
						asteroidsForDestruction[math.Abs(tangent)] = distance.coordinates
					} else {
						asteroidsForDestruction[-math.Abs(tangent)] = distance.coordinates
					}
					laser.tangentsOfObstruction[fmt.Sprintf("%v_%v", currentQuadrant, tangent)] = true
				}
			}
		}
		var tangents []float64
		for tan := range asteroidsForDestruction {
			tangents = append(tangents, tan)
		}
		sort.Float64s(tangents)

		for _, tan := range tangents {
			asteroidsDestroyed++
			currentAsteroidCoordinates := asteroidsForDestruction[tan]
			fmt.Println(asteroidsDestroyed, currentAsteroidCoordinates, tan)
			alreadyDestroyed[fmt.Sprintf("%v:%v", currentAsteroidCoordinates.x, currentAsteroidCoordinates.y)] = true
			if asteroidsDestroyed == 200 {
				fmt.Println(currentAsteroidCoordinates.x*100 + currentAsteroidCoordinates.y)
				break
			}
		}
		if asteroidsDestroyed == 200 {
			break
		}
		currentQuadrant = (currentQuadrant + 1) % 4
	}
}

func findDistance(a, b coordinates) float64 {
	return math.Sqrt(math.Pow(a.x-b.x, 2) + math.Pow(a.y-b.y, 2))
}

func getQuadrant(a, b coordinates) int {
	if a.x <= b.x && a.y > b.y {
		return 0
	} else if a.x < b.x && a.y <= b.y {
		return 1
	} else if a.x >= b.x && a.y < b.y {
		return 2
	} else if a.x > b.x && a.y >= b.y {
		return 3
	} else {
		panic(b)
	}
}
