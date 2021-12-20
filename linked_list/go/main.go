package main

import (
	"fmt"
	"log"

	"github.com/matheusmv/data-structures-and-algorithms/linkedlist"
)

type Student struct {
	Id   int
	Name string
}

func main() {
	list := linkedlist.NewLinkedList()

	fmt.Println(list.Getlength())

	list.InsertFirst(Student{1, "student 1"})
	list.InsertFirst(Student{2, "student 2"})

	fmt.Println(list.Getlength())
	list.Show()

	list.InsertLast(Student{3, "student 3"})
	list.InsertLast(Student{4, "student 4"})

	fmt.Println(list.Getlength())
	list.Show()

	err := list.InsertAt(Student{5, "student 5"}, 2)
	if err != nil {
		log.Fatal(err.Error())
	}

	fmt.Println(list.Getlength())
	list.Show()

	if value, err := list.Get(0); err != nil {
		log.Fatal(err.Error())
	} else {
		fmt.Println("Found:", value)
	}

	firstValue := list.RemoveFirst()
	fmt.Println("First:", firstValue)

	fmt.Println(list.Getlength())
	list.Show()

	lastValue := list.RemoveLast()
	fmt.Println("Last:", lastValue)

	fmt.Println(list.Getlength())
	list.Show()

	middleIndex := list.Getlength() / 2
	if middleValue, err := list.RemoveAt(middleIndex); err != nil {
		log.Fatal(err.Error())
	} else {
		fmt.Println("Middle:", middleValue)
	}

	fmt.Println(list.Getlength())
	list.Show()

	list.Clear()

	fmt.Println(list.Getlength())
	list.Show()
}
