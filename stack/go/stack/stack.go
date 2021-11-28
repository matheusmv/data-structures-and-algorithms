package stack

import "fmt"

type node struct {
	Data interface{}
	Next *node
}

type stack struct {
	Size uint
	Top  *node
	Base *node
}

func newNode(data interface{}, next *node) *node {
	return &node{
		Data: data,
		Next: next,
	}
}

func Newstack() *stack {
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

func (stk *stack) GetSize() uint {
	return stk.Size
}

func (stk *stack) IsEmpty() bool {
	return stk.Size == 0
}

func (stk *stack) Push(data interface{}) {
	newNode := newNode(data, stk.Top)

	if stk.Base == nil {
		stk.Base = newNode
	}

	stk.Top = newNode

	stk.increaseSize()
}

func (stk *stack) Pop() interface{} {
	if !stk.IsEmpty() {
		top := stk.Top
		stk.Top = top.Next
		stk.decreaseSize()
		return top.Data
	}

	return nil
}

func (stk *stack) Peek() *node {
	if !stk.IsEmpty() {
		return stk.Top
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
