/* Appending to a slice modifies underlying array! */
package main

import (
	"fmt"
)

func main() {
	slice := []int{0, 0, 0};
	newSlice := slice[0:2]
	newSlice = append(newSlice, 1)
	fmt.Println(slice)
}
