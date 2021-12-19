package stack

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type user struct {
	Username string
	Password string
}

func TestPush(t *testing.T) {
	stack := NewStack()

	t.Run("when item is pushed", func(t *testing.T) {
		expectedStack := NewStack()
		expectedStack.Push(user{"username 1", "password 1"})
		expectedStack.Push(user{"username 2", "password 2"})
		expectedStack.Push(user{"username 3", "password 3"})

		t.Run("stack should be updated", func(t *testing.T) {
			stack.Push(user{"username 1", "password 1"})
			stack.Push(user{"username 2", "password 2"})
			stack.Push(user{"username 3", "password 3"})

			assert.Equal(t, stack, expectedStack)
		})
	})
}

func TestPop(t *testing.T) {
	stack := NewStack()

	t.Run("when stack is empty", func(t *testing.T) {
		expectedStack := NewStack()

		t.Run("it should return nil response", func(t *testing.T) {
			item := stack.Pop()

			assert.Nil(t, item)
			assert.Equal(t, stack, expectedStack)
		})
	})

	t.Run("when stack is not empty", func(t *testing.T) {
		expectedStack := NewStack()
		expectedStack.Push(user{"username 1", "password 1"})
		expectedStack.Push(user{"username 2", "password 2"})

		t.Run("it should return last inserted item and update the stack", func(t *testing.T) {
			stack.Push(user{"username 1", "password 1"})
			stack.Push(user{"username 2", "password 2"})
			stack.Push(user{"username 3", "password 3"})

			item := stack.Pop()

			assert.Equal(t, item, user{"username 3", "password 3"})
			assert.Equal(t, stack, expectedStack)
		})
	})
}

func TestIsEmpty(t *testing.T) {
	stack := NewStack()

	t.Run("when stack is not empty", func(t *testing.T) {
		t.Run("it should return false", func(t *testing.T) {
			stack.Push(user{"username 1", "password 1"})

			assert.False(t, stack.IsEmpty())
		})
	})

	t.Run("when stack is empty", func(t *testing.T) {
		t.Run("it should return true", func(t *testing.T) {
			stack.Pop()

			assert.True(t, stack.IsEmpty())
		})
	})
}

func TestPeek(t *testing.T) {

	t.Run("when stack is not empty", func(t *testing.T) {
		stack := NewStack()

		expectedStack := NewStack()
		expectedStack.Push(user{"username 1", "password 1"})
		expectedStack.Push(user{"username 2", "password 2"})
		expectedStack.Push(user{"username 3", "password 3"})

		t.Run("it should return last inserted item and no change in stack", func(t *testing.T) {
			stack.Push(user{"username 1", "password 1"})
			stack.Push(user{"username 2", "password 2"})
			stack.Push(user{"username 3", "password 3"})

			item := stack.Peek()

			assert.Equal(t, item, user{"username 3", "password 3"})
			assert.Equal(t, stack, expectedStack)
		})
	})

	t.Run("when stack is empty", func(t *testing.T) {
		stack := NewStack()

		t.Run("it should return nil", func(t *testing.T) {
			item := stack.Peek()

			assert.Nil(t, item)
		})
	})
}

func TestGetSize(t *testing.T) {
	stack := NewStack()

	t.Run("when stack is provided", func(t *testing.T) {
		t.Run("it should return number of items in stack", func(t *testing.T) {
			stack.Push(user{"username 1", "password 1"})

			assert.Equal(t, stack.GetSize(), 1)

			stack.Pop()

			assert.Equal(t, stack.GetSize(), 0)
		})
	})
}

func TestClear(t *testing.T) {
	stack := NewStack()

	t.Run("when stack is provided", func(t *testing.T) {
		expectedStack := NewStack()

		t.Run("it should clear all items in stack", func(t *testing.T) {
			stack.Push(user{"username 1", "password 1"})
			stack.Push(user{"username 2", "password 2"})
			stack.Push(user{"username 3", "password 3"})

			stack.Clear()

			assert.Equal(t, stack, expectedStack)
		})
	})
}
