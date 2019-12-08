package main

import (
	"fmt"
	"io/ioutil"
)

const width = 25
const height = 6

func main() {
	pixelsInALayer := width * height
	outputPixels := make([]rune, pixelsInALayer)

	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}
	inputString := string(input)

	zeroesLeft := pixelsInALayer
	for index, pixel := range inputString {
		if outputPixels[index%pixelsInALayer] == 0 {
			if pixel == '0' || pixel == '1' {
				outputPixels[index%pixelsInALayer] = pixel
				zeroesLeft--
			}
			if zeroesLeft == 0 {
				break
			}
		}
	}

	var outputMessage string
	for index, pixel := range outputPixels {
		if index != 0 && index%width == 0 {
			outputMessage += "\n"
		}
		switch pixel {
		case 0:
			outputMessage += " "
		case '0':
			outputMessage += "◼️"
		case '1':
			outputMessage += "◻️"
		}
	}

	fmt.Print(outputMessage)
}
