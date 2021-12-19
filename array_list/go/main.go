package main

import (
	"fmt"

	"github.com/matheusmv/data-structures-and-algorithms/arraylist"
)

type Person struct {
	Name string
}

func main() {
	names := arraylist.NewEmptyArrayList()

	fmt.Println(names.GetLength())

	names.Append(Person{"Jhon"})
	names.Append(Person{"Alex"})
	names.Append(Person{"Joe"})
	names.Append(Person{"Alice"})

	fmt.Println(names.GetLength())

	names.Show()

	name := names.Remove()
	fmt.Println("Removed:", name)

	names.Show()
	fmt.Println(names.GetLength())

	names.Clear()
	fmt.Println(names.GetLength())

	names.Show()
}
