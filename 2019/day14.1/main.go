package main

import (
	"fmt"
	"io/ioutil"
	"math"
	"strconv"
	"strings"
)

const fuel = "FUEL"
const ore = "ORE"

type registry map[string]*element

type element struct {
	formula  formula
	quantity float64
}

type formula struct {
	quantityProduced float64
	ingredients      map[string]float64
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
	requiredOre := reg.calculateRequiredOre(fuel, 1)

	fmt.Println(int(requiredOre))
}

func (r registry) parseFormula(rawFormula string) {
	conversion := strings.Split(rawFormula, "=>")
	from, to := conversion[0], conversion[1]
	fromElements := strings.Split(from, ",")
	ingrgedients := make(map[string]float64)
	for _, ingrgedient := range fromElements {
		name, amount := getElementAndQuantity(ingrgedient)
		ingrgedients[name] = amount
	}
	productName, productAmount := getElementAndQuantity(to)
	el := element{
		formula: formula{
			quantityProduced: productAmount,
			ingredients:      ingrgedients,
		},
	}
	r[productName] = &el
}

func getElementAndQuantity(rawElementAndAmount string) (string, float64) {
	elementAndAmount := strings.Split(strings.Trim(rawElementAndAmount, " "), " ")
	amount, err := strconv.ParseFloat(elementAndAmount[0], 10)
	if err != nil {
		fmt.Printf("could not parse element amount %v", err)
	}
	return elementAndAmount[1], amount
}

func (r registry) calculateRequiredOre(elementName string, amountNeeded float64) float64 {
	if elementName == ore {
		return amountNeeded
	}
	var total float64
	var requiredExecutions float64
	element := r[elementName]
	if amountNeeded > element.quantity {
		requiredExecutions = math.Ceil((amountNeeded - element.quantity) / element.formula.quantityProduced)
		element.quantity += requiredExecutions*element.formula.quantityProduced - amountNeeded
	} else {
		element.quantity -= amountNeeded
	}
	for ingredient, amount := range element.formula.ingredients {
		total += r.calculateRequiredOre(ingredient, requiredExecutions*amount)
	}
	return total
}
