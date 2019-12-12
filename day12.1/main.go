package main

import (
	"fmt"
	"io/ioutil"
	"regexp"
	"strconv"
	"strings"
)

type dimension string

const (
	x dimension = "x"
	y dimension = "y"
	z dimension = "z"
)

type moon struct {
	coordinates map[dimension]int
	velocities  map[dimension]int
}

func main() {
	var moons []*moon
	var totalEnergy int

	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	moonSpecs := strings.Split(inputString, "\n")

	for _, ms := range moonSpecs {
		coordinates := make(map[dimension]int, 3)
		velocities := make(map[dimension]int, 3)

		coordinates[x] = getCoordinate(x, ms)
		coordinates[y] = getCoordinate(y, ms)
		coordinates[z] = getCoordinate(z, ms)

		m := moon{
			coordinates: coordinates,
			velocities:  velocities,
		}

		moons = append(moons, &m)
	}

	for i := 0; i < 1000; i++ {
		for _, m1 := range moons {
			for _, m2 := range moons {
				if m1 != m2 {
					adjustVelocity(m1, m2)
				}
			}
		}

		for _, m := range moons {
			applyVelocity(m)
		}
	}

	for _, m := range moons {
		dimensions := []dimension{x, y, z}
		var potentialEnergy int
		var kineticEnergy int
		for _, d := range dimensions {
			potentialEnergy += abs(m.coordinates[d])
			kineticEnergy += abs(m.velocities[d])
		}
		totalEnergy += potentialEnergy * kineticEnergy
	}

	fmt.Println(totalEnergy)
}

func adjustVelocity(m1 *moon, m2 *moon) {
	dimensions := []dimension{x, y, z}
	for _, d := range dimensions {
		if m1.coordinates[d] > m2.coordinates[d] {
			m1.velocities[d]--
		}
		if m1.coordinates[d] < m2.coordinates[d] {
			m1.velocities[d]++
		}
	}
}

func applyVelocity(m *moon) {
	dimensions := []dimension{x, y, z}
	for _, d := range dimensions {
		m.coordinates[d] = m.coordinates[d] + m.velocities[d]
	}
}

func getCoordinate(dimension dimension, moonSpec string) int {
	matchValue := regexp.MustCompile(fmt.Sprintf("%v=(.*?)(,|>)", dimension))
	valueResult := matchValue.FindStringSubmatch(moonSpec)
	coordinate, err := strconv.Atoi(valueResult[1])
	if err != nil {
		panic(err)
	}
	return coordinate
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
