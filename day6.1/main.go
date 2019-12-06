package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

const rootBody = "COM"

type celestialBody struct {
	bodiesInOrbit []*celestialBody
}

func main() {
	bodiesLookup := make(map[string]*celestialBody)
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")

	for _, celestialBodyConnection := range inputArray {
		celestialBodies := strings.Split(celestialBodyConnection, ")")
		bodyOrbited := createBodyIfNoneExists(celestialBodies[0], bodiesLookup)
		bodyOrbiting := createBodyIfNoneExists(celestialBodies[1], bodiesLookup)
		bodyOrbited.bodiesInOrbit = append(bodyOrbited.bodiesInOrbit, bodyOrbiting)
	}

	fmt.Println(countBodiesInOrbit(bodiesLookup[rootBody], 0))
}

func createBodyIfNoneExists(name string, bodiesLookup map[string]*celestialBody) *celestialBody {
	if bodiesLookup[name] == nil {
		newBody := celestialBody{}
		bodiesLookup[name] = &newBody
		return &newBody
	}
	return bodiesLookup[name]
}

func countBodiesInOrbit(body *celestialBody, bodiesFromTheCenter int) int {
	sum := 0
	for _, bodyInOrbit := range body.bodiesInOrbit {
		sum += countBodiesInOrbit(bodyInOrbit, bodiesFromTheCenter+1)
	}
	return sum + bodiesFromTheCenter
}
