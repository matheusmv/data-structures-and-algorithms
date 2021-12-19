package main

import (
	"fmt"

	"github.com/matheusmv/data-structures-and-algorithms/stack"
)

type User struct {
	Username string
	Password string
}

func main() {
	s := stack.NewStack()

	s.Push(User{"username 1", "password 1"})
	s.Push(User{"username 2", "password 2"})
	s.Push(User{"username 3", "password 3"})
	s.Push(User{"username 4", "password 4"})
	s.Push(User{"username 5", "password 5"})

	s.Show()

	user := s.Pop()

	fmt.Println("Pop: ", user)

	s.Show()

	s.Clear()

	s.Show()
}
