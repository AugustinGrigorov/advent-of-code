package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

type registry map[string]formula

type formula struct {
	quantityProduced int
	ingredients      map[string]int
}

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)
	inputArray := strings.Split(strings.Trim(inputString, "\n"), "\n")
	reg := make(registry, len(inputArray))

	for _, rawFormula := range inputArray {
		reg.parseFormula(rawFormula)
	}
}

func (r *registry) parseFormula(rawFormula string) {
	fmt.Println(rawFormula)
}
