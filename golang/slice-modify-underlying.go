/*
 * 1. Appending to a slice modifies underlying array
 * 2. But sometimes not
 */
package main

import (
	"fmt"
)

func main() {
    // Appending to a slice modifies underlying array
	slice := []int{0, 0, 0};
	newSlice := slice[0:2]
	newSlice = append(newSlice, 1)
	fmt.Println("Original, but modified", slice, " should be copy but the same", newSlice)

    // But sometimes not
    sliceCopy := slice[0:2]
    sliceCopy = append(sliceCopy, 1, 2, 3, 4, 5)
    fmt.Println("Original, not modified", slice, " copy ", sliceCopy)
}
