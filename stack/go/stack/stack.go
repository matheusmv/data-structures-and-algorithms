package stack

import (
	"fmt"
	"sync"
)

type node struct {
	Data interface{}
	Next *node
}

type stack struct {
	Size int
	Top  *node
	Lock sync.Mutex
}

func newNode(data interface{}, next *node) *node {
	return &node{
		Data: data,
		Next: next,
	}
}

func NewStack() *stack {
	return &stack{}
}

func (stk *stack) increaseSize() {
	stk.Size += 1
}

func (stk *stack) decreaseSize() {
	if stk.Size > 0 {
		stk.Size -= 1
	}
}

func (stk *stack) GetSize() int {
	return stk.Size
}

func (stk *stack) IsEmpty() bool {
	return stk.Size == 0
}

func (stk *stack) Push(data interface{}) {
	stk.Lock.Lock()
	defer stk.Lock.Unlock()

	newNode := newNode(data, stk.Top)

	stk.Top = newNode

	stk.increaseSize()
}

func (stk *stack) Pop() interface{} {
	stk.Lock.Lock()
	defer stk.Lock.Unlock()

	if !stk.IsEmpty() {
		top := stk.Top
		stk.Top = top.Next
		stk.decreaseSize()
		return top.Data
	}

	return nil
}

func (stk *stack) Peek() interface{} {
	if !stk.IsEmpty() {
		return stk.Top.Data
	}

	return nil
}

func (stk *stack) Show() {
	if !stk.IsEmpty() {
		top := stk.Top

		for top != nil {
			fmt.Println(top.Data)
			top = top.Next
		}
	}
}

func (stk *stack) Clear() {
	for !stk.IsEmpty() {
		stk.Pop()
	}
}
