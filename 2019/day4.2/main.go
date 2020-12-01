package main

import (
	"fmt"
	"strconv"
)

const lowerBound = 158126
const upperBound = 624574

func main() {
	var possibleKeys int
	for i := lowerBound; i < upperBound; i++ {
		if hasRepeatingNumbers(i) && checkDigitsNotDecrease(i) {
			possibleKeys++
		}
	}
	fmt.Print(possibleKeys)
}

func hasRepeatingNumbers(keyContender int) bool {
	keyStringRepresentation := strconv.Itoa(keyContender)
	for i := 0; i < len(keyStringRepresentation)-1; i++ {
		if keyStringRepresentation[i] == keyStringRepresentation[i+1] {
			if i == 0 {
				if keyStringRepresentation[i] != keyStringRepresentation[i+2] {
					return true
				}
			} else if i+2 > len(keyStringRepresentation)-1 {
				if keyStringRepresentation[i] != keyStringRepresentation[i-1] {
					return true
				}
			} else if keyStringRepresentation[i] != keyStringRepresentation[i+2] && keyStringRepresentation[i] != keyStringRepresentation[i-1] {
				return true
			}
		}
	}
	return false
}

func checkDigitsNotDecrease(keyContender int) bool {
	index := 0
	var previousDigit int
	for keyContender > 0 {
		currentDigit := keyContender % 10
		keyContender = keyContender / 10
		if index != 0 {
			if previousDigit < currentDigit {
				return false
			}
		}
		previousDigit = currentDigit
		index++
	}
	return true
}
