package main

import (
	"fmt"
	"io/ioutil"
)

const width = 25
const height = 6

func main() {
	var fewestZeroes int
	var productOfOneTwo int
	pixelsInALayer := width * height

	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)

	var zeroes, ones, twoes int
	for index, pixel := range inputString {
		if index%pixelsInALayer == 0 {
			if zeroes < fewestZeroes || index == pixelsInALayer {
				fewestZeroes = zeroes
				productOfOneTwo = ones * twoes
			}
			zeroes, ones, twoes = 0, 0, 0
		}
		switch pixel {
		case '0':
			zeroes++
		case '1':
			ones++
		case '2':
			twoes++
		}
	}

	fmt.Print(productOfOneTwo)
}
