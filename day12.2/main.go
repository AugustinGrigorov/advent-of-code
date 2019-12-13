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
	var steps int64
	var alignmentFound int
	var moonInitialStates []*moon

	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	moonSpecs := strings.Split(inputString, "\n")

	for _, ms := range moonSpecs {
		coordinates := make(map[dimension]int, 3)
		initialCoordinates := make(map[dimension]int, 3)

		coordinates[x] = getCoordinate(x, ms)
		coordinates[y] = getCoordinate(y, ms)
		coordinates[z] = getCoordinate(z, ms)

		for k, v := range coordinates {
			initialCoordinates[k] = v
		}

		m := moon{
			coordinates: coordinates,
			velocities:  make(map[dimension]int, 3),
		}
		initialState := moon{
			coordinates: initialCoordinates,
			velocities:  make(map[dimension]int, 3),
		}

		moons = append(moons, &m)
		moonInitialStates = append(moonInitialStates, &initialState)
	}

	alignments := make(map[dimension]int64, 0)

	for alignmentFound < 3 {
		steps++
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

		xAlignment := true
		yAlignment := true
		zAlignment := true
		for i := 0; i < len(moons); i++ {
			if steps != 0 {
				initialStateCoordinates := moonInitialStates[i].coordinates
				moonCoordinates := moons[i].coordinates
				if moonCoordinates[x] != initialStateCoordinates[x] {
					xAlignment = false
				}
				if moonCoordinates[y] != initialStateCoordinates[y] {
					yAlignment = false
				}
				if moonCoordinates[z] != initialStateCoordinates[z] {
					zAlignment = false
				}
			}
		}

		if xAlignment && alignments[x] == 0 {
			alignments[x] = steps + 1
			alignmentFound++
		}
		if yAlignment && alignments[y] == 0 {
			alignments[y] = steps + 1
			alignmentFound++
		}
		if zAlignment && alignments[z] == 0 {
			alignments[z] = steps + 1
			alignmentFound++
		}
	}

	stepsToReachAlignment := lcm(alignments[x], alignments[y], alignments[z])
	fmt.Println(stepsToReachAlignment)
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

func gcd(a, b int64) int64 {
	for b != 0 {
		t := b
		b = a % b
		a = t
	}
	return a
}

func lcm(integers ...int64) int64 {
	a := integers[0]
	b := integers[1]
	result := a * b / gcd(a, b)

	for i := 2; i < len(integers); i++ {
		result = lcm(result, integers[i])
	}

	return result
}
