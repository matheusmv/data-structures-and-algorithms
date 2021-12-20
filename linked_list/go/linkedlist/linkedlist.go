package linkedlist

import (
	"errors"
	"fmt"
	"sync"
)

var (
	errIndexOutOfBounds = errors.New("index out of bounds")
)

type node struct {
	Data interface{}
	Next *node
}

type linkedList struct {
	length int
	head   *node
	tail   *node
	lock   sync.Mutex
}

func newNode(data interface{}, next *node) *node {
	return &node{
		Data: data,
		Next: next,
	}
}

func NewLinkedList() *linkedList {
	return &linkedList{}
}

func (l *linkedList) increaselength() {
	l.length += 1
}

func (l *linkedList) decreaselength() {
	if l.length > 0 {
		l.length -= 1
	}
}

func (l *linkedList) findNode(index int) (*node, error) {
	if !l.IsEmpty() {
		if index < 0 && index > l.length {
			return nil, errIndexOutOfBounds
		}

		node := l.head
		for i := 0; i < index; i++ {
			node = node.Next
		}

		return node, nil
	}

	return nil, nil
}

func (l *linkedList) Getlength() int {
	return l.length
}

func (l *linkedList) IsEmpty() bool {
	return l.head == nil
}

func (l *linkedList) InsertFirst(data interface{}) {
	l.lock.Lock()
	defer l.lock.Unlock()

	newNode := newNode(data, l.head)

	l.head = newNode

	if l.tail == nil {
		l.tail = newNode
	}

	l.increaselength()
}

func (l *linkedList) InsertLast(data interface{}) {
	l.lock.Lock()
	defer l.lock.Unlock()

	newNode := newNode(data, nil)

	if !l.IsEmpty() {
		l.tail.Next = newNode
	}

	l.tail = newNode

	if l.head == nil {
		l.head = newNode
	}

	l.increaselength()
}

func (l *linkedList) InsertAt(data interface{}, index int) error {

	if index < 0 || index > l.length {
		return errIndexOutOfBounds
	}

	switch index {
	case 0:
		l.InsertFirst(data)
	case l.length:
		l.InsertLast(data)
	default:
		l.lock.Lock()
		defer l.lock.Unlock()

		prev, _ := l.findNode(index - 1)
		newNode := newNode(data, prev.Next)
		prev.Next = newNode

		l.increaselength()
	}

	return nil
}

func (l *linkedList) RemoveFirst() interface{} {
	l.lock.Lock()
	defer l.lock.Unlock()

	if !l.IsEmpty() {
		head := l.head

		if l.length == 1 {
			l.head = nil
			l.tail = nil
		} else {
			l.head = head.Next
		}

		l.decreaselength()

		return head.Data
	}

	return nil
}

func (l *linkedList) RemoveLast() interface{} {
	l.lock.Lock()
	defer l.lock.Unlock()

	if !l.IsEmpty() {
		tail := l.tail

		if l.length == 1 {
			l.head = nil
			l.tail = nil
		} else {
			listEnd := l.length - 1
			prev, _ := l.findNode(listEnd - 1)
			prev.Next = nil
			l.tail = prev
		}

		l.decreaselength()

		return tail.Data
	}

	return nil
}

func (l *linkedList) RemoveAt(index int) (interface{}, error) {
	if index < 0 || index >= l.length {
		return nil, errIndexOutOfBounds
	}

	if !l.IsEmpty() {
		switch index {
		case 0:
			data := l.RemoveFirst()
			return data, nil
		case l.length - 1:
			data := l.RemoveLast()
			return data, nil
		default:
			l.lock.Lock()
			defer l.lock.Unlock()

			prev, _ := l.findNode(index - 1)
			current, _ := l.findNode(index)
			prev.Next = current.Next
			l.decreaselength()

			return current.Data, nil
		}
	}

	return nil, nil
}

func (l *linkedList) Get(index int) (interface{}, error) {
	if index < 0 || index >= l.length {
		return nil, errIndexOutOfBounds
	}

	if !l.IsEmpty() {
		node, _ := l.findNode(index)
		return node.Data, nil
	}

	return nil, nil
}

func (l *linkedList) Show() {
	if !l.IsEmpty() {
		for node := l.head; node != nil; node = node.Next {
			fmt.Println(node.Data)
		}
	}
}

func (l *linkedList) Clear() {
	l.lock.Lock()
	defer l.lock.Unlock()

	if !l.IsEmpty() {
		l.head = nil
		l.tail = nil
		l.length = 0
	}
}

func (l *linkedList) Reverse() {
	l.lock.Lock()
	defer l.lock.Unlock()

	if !l.IsEmpty() {
		l.tail = l.head

		var prev, next *node
		current := l.head
		for current != nil {
			next = current.Next
			current.Next = prev
			prev = current
			current = next
		}

		l.head = prev
	}
}
