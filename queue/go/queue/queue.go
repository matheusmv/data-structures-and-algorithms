package queue

import "fmt"

type node struct {
	Data interface{}
	Next *node
}

type queue struct {
	Size  uint
	Start *node
	End   *node
}

func newNode(data interface{}, next *node) *node {
	return &node{
		Data: data,
		Next: next,
	}
}

func NewQueue() *queue {
	return &queue{}
}

func (q *queue) increaseSize() {
	q.Size += 1
}

func (q *queue) decreaseSize() {
	if q.Size > 0 {
		q.Size -= 1
	}
}

func (q *queue) GetSize() uint {
	return q.Size
}

func (q *queue) IsEmpty() bool {
	return q.Size == 0
}

func (q *queue) Enqueue(data interface{}) {
	newNode := newNode(data, nil)

	if q.Start == nil {
		q.Start = newNode
	}

	if !q.IsEmpty() {
		q.End.Next = newNode
	}

	q.End = newNode

	q.increaseSize()
}

func (q *queue) Dequeue() interface{} {
	if !q.IsEmpty() {
		start := q.Start
		q.Start = start.Next
		q.decreaseSize()
		return start.Data
	}

	return nil
}

func (q *queue) Peek() *node {
	if !q.IsEmpty() {
		return q.Start
	}

	return nil
}

func (q *queue) Show() {
	if !q.IsEmpty() {
		start := q.Start

		for start != nil {
			fmt.Println(start.Data)
			start = start.Next
		}
	}
}

func (q *queue) Clear() {
	for !q.IsEmpty() {
		q.Dequeue()
	}
}
