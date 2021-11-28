package main

import (
	"fmt"

	"github.com/matheusmv/data-structures-and-algorithms/queue"
)

type Student struct {
	Name   string
	Number uint
}

func main() {
	q := queue.NewQueue()

	q.Enqueue(Student{"Student 1", 1})
	q.Enqueue(Student{"Student 2", 2})
	q.Enqueue(Student{"Student 3", 3})
	q.Enqueue(Student{"Student 4", 4})
	q.Enqueue(Student{"Student 5", 5})

	q.Show()

	student := q.Dequeue()

	fmt.Println("Dequeue: ", student)

	q.Show()

	q.Clear()

	q.Show()
}
