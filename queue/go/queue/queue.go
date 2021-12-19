package queue

import (
	"fmt"
	"sync"
)

type node struct {
	Data interface{}
	Next *node
}

type queue struct {
	Size  int
	Start *node
	End   *node
	Lock  sync.Mutex
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

func (q *queue) GetSize() int {
	return q.Size
}

func (q *queue) IsEmpty() bool {
	return q.Size == 0
}

func (q *queue) Enqueue(data interface{}) {
	q.Lock.Lock()
	defer q.Lock.Unlock()

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
	q.Lock.Lock()
	defer q.Lock.Unlock()

	if !q.IsEmpty() {
		start := q.Start

		if q.GetSize() > 1 {
			q.Start = start.Next
		} else {
			q.Start = nil
			q.End = nil
		}

		q.decreaseSize()
		return start.Data
	}

	return nil
}

func (q *queue) Peek() interface{} {
	if !q.IsEmpty() {
		return q.Start.Data
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
