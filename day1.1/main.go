package main

import (
	"fmt"
	"io/ioutil"
	"strings"
  "strconv"
)

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		fmt.Println(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")
  var fuelNeeded int
  for _, moduleMass := range inputArray {
    moduleMassInt, err := strconv.Atoi(moduleMass)
    if err != nil {
      fmt.Println(err)
    }
    fuelNeeded += calculateFuelNeeded(moduleMassInt)
  }
  fmt.Println(fuelNeeded)
}

func calculateFuelNeeded (mass int) int {
  return mass / 3 - 2
}
