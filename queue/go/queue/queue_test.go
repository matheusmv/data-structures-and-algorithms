package queue

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type student struct {
	Name   string
	Number uint
}

func TestEnqueue(t *testing.T) {
	queue := NewQueue()

	t.Run("when item is enqueued", func(t *testing.T) {
		expectedQueue := NewQueue()
		expectedQueue.Enqueue(student{"Student 1", 1})
		expectedQueue.Enqueue(student{"Student 2", 2})
		expectedQueue.Enqueue(student{"Student 3", 3})

		t.Run("queue should br updated", func(t *testing.T) {
			queue.Enqueue(student{"Student 1", 1})
			queue.Enqueue(student{"Student 2", 2})
			queue.Enqueue(student{"Student 3", 3})

			assert.Equal(t, queue, expectedQueue)
		})
	})
}

func TestDequeue(t *testing.T) {
	queue := NewQueue()

	t.Run("when queue is empty", func(t *testing.T) {
		expectedQueue := NewQueue()

		t.Run("it should return nil response", func(t *testing.T) {
			item := queue.Dequeue()

			assert.Nil(t, item)
			assert.Equal(t, queue, expectedQueue)
		})
	})

	t.Run("when queue is not empty", func(t *testing.T) {
		expectedQueue := NewQueue()
		expectedQueue.Enqueue(student{"Student 2", 2})
		expectedQueue.Enqueue(student{"Student 3", 3})

		t.Run("it should return first inserted item and update the queue", func(t *testing.T) {
			queue.Enqueue(student{"Student 1", 1})
			queue.Enqueue(student{"Student 2", 2})
			queue.Enqueue(student{"Student 3", 3})

			item := queue.Dequeue()

			assert.Equal(t, item, student{"Student 1", 1})
			assert.Equal(t, queue, expectedQueue)
		})
	})
}

func TestIsEmpty(t *testing.T) {
	queue := NewQueue()

	t.Run("when queue is not empty", func(t *testing.T) {
		t.Run("it should return false", func(t *testing.T) {
			queue.Enqueue(student{"Student 1", 1})

			assert.False(t, queue.IsEmpty())
		})
	})

	t.Run("when queue is empty", func(t *testing.T) {
		t.Run("it should return true", func(t *testing.T) {
			queue.Dequeue()

			assert.True(t, queue.IsEmpty())
		})
	})
}

func TestPeek(t *testing.T) {
	t.Run("when stack is not empty", func(t *testing.T) {
		queue := NewQueue()

		expectedQueue := NewQueue()
		expectedQueue.Enqueue(student{"Student 1", 1})
		expectedQueue.Enqueue(student{"Student 2", 2})
		expectedQueue.Enqueue(student{"Student 3", 3})

		t.Run("it should return first inserted item and no change in queue", func(t *testing.T) {
			queue.Enqueue(student{"Student 1", 1})
			queue.Enqueue(student{"Student 2", 2})
			queue.Enqueue(student{"Student 3", 3})

			item := queue.Peek()

			assert.Equal(t, item, student{"Student 1", 1})
			assert.Equal(t, queue, expectedQueue)
		})
	})

	t.Run("when queue is empty", func(t *testing.T) {
		queue := NewQueue()

		t.Run("it should return nil", func(t *testing.T) {
			item := queue.Peek()

			assert.Nil(t, item)
		})
	})
}

func TestGetSize(t *testing.T) {
	queue := NewQueue()

	t.Run("when queue is provided", func(t *testing.T) {
		t.Run("it should return number of items in queue", func(t *testing.T) {
			queue.Enqueue(student{"Student 1", 1})

			assert.Equal(t, queue.GetSize(), 1)

			queue.Dequeue()

			assert.Equal(t, queue.GetSize(), 0)
		})
	})
}

func TestClear(t *testing.T) {
	queue := NewQueue()

	t.Run("when queue is provided", func(t *testing.T) {
		expectedQueue := NewQueue()

		t.Run("it should clear all items in queue", func(t *testing.T) {
			queue.Enqueue(student{"Student 1", 1})
			queue.Enqueue(student{"Student 2", 2})
			queue.Enqueue(student{"Student 3", 3})

			queue.Clear()

			assert.Equal(t, queue, expectedQueue)
		})
	})
}
