package linkedlist

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type student struct {
	id   int
	name string
}

func TestInsertFirst(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when item is inserted", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertFirst(student{1, "student 1"})
		expectedLinkedList.InsertFirst(student{2, "student 2"})
		expectedLinkedList.InsertFirst(student{3, "student 3"})

		t.Run("linkedlist should be updated", func(t *testing.T) {
			linkedList.InsertFirst(student{1, "student 1"})
			linkedList.InsertFirst(student{2, "student 2"})
			linkedList.InsertFirst(student{3, "student 3"})

			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestInsertLast(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when item is inserted", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertLast(student{1, "student 1"})
		expectedLinkedList.InsertLast(student{2, "student 2"})
		expectedLinkedList.InsertLast(student{3, "student 3"})

		t.Run("linkedlist should be updated", func(t *testing.T) {
			linkedList.InsertLast(student{1, "student 1"})
			linkedList.InsertLast(student{2, "student 2"})
			linkedList.InsertLast(student{3, "student 3"})

			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestInsertAt(t *testing.T) {
	t.Run("when item is inserted at given index", func(t *testing.T) {
		linkedList := NewLinkedList()

		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertAt(student{1, "student 1"}, 0)
		expectedLinkedList.InsertAt(student{2, "student 2"}, 1)
		expectedLinkedList.InsertAt(student{4, "student 4"}, 2)
		expectedLinkedList.InsertAt(student{3, "student 3"}, 2)

		t.Run("linkedlist should be updated", func(t *testing.T) {
			linkedList.InsertAt(student{1, "student 1"}, 0)
			linkedList.InsertAt(student{2, "student 2"}, 1)
			linkedList.InsertAt(student{4, "student 4"}, 2)
			linkedList.InsertAt(student{3, "student 3"}, 2)

			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})

	t.Run("when the item is inserted into an invalid index", func(t *testing.T) {
		linkedList := NewLinkedList()

		expectedLinkedList := NewLinkedList()

		t.Run("should return an error and no change in linkedlist", func(t *testing.T) {
			err1 := linkedList.InsertAt(student{1, "student 1"}, 10)
			err2 := linkedList.InsertAt(student{2, "student 2"}, -1)

			assert.EqualError(t, err1, errIndexOutOfBounds.Error())
			assert.EqualError(t, err2, errIndexOutOfBounds.Error())
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestRemoveFirst(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when linkedlist is empty", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()

		t.Run("it should return nil response", func(t *testing.T) {
			item := linkedList.RemoveFirst()

			assert.Nil(t, item)
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})

	t.Run("when linkedlist is not empty", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertFirst(student{1, "student 1"})
		expectedLinkedList.InsertFirst(student{2, "student 2"})

		t.Run("it should return first inserted item and update the linkedlist", func(t *testing.T) {
			linkedList.InsertFirst(student{1, "student 1"})
			linkedList.InsertFirst(student{2, "student 2"})
			linkedList.InsertFirst(student{3, "student 3"})

			item := linkedList.RemoveFirst()

			assert.Equal(t, item, student{3, "student 3"})
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestRemoveLast(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when linkedlist is empty", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()

		t.Run("it should return nil response", func(t *testing.T) {
			item := linkedList.RemoveLast()

			assert.Nil(t, item)
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})

	t.Run("when linkedlist is not empty", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertLast(student{1, "student 1"})
		expectedLinkedList.InsertLast(student{2, "student 2"})

		t.Run("it should return last inserted item and update the linkedlist", func(t *testing.T) {
			linkedList.InsertLast(student{1, "student 1"})
			linkedList.InsertLast(student{2, "student 2"})
			linkedList.InsertLast(student{3, "student 3"})

			item := linkedList.RemoveLast()

			assert.Equal(t, item, student{3, "student 3"})
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestRemoveAt(t *testing.T) {
	t.Run("when linkedlist is empty", func(t *testing.T) {
		linkedList := NewLinkedList()

		expectedLinkedList := NewLinkedList()

		t.Run("it should return nil response", func(t *testing.T) {
			item, _ := linkedList.RemoveAt(0)

			assert.Nil(t, item)
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})

	t.Run("when item is removed at given index", func(t *testing.T) {
		linkedList := NewLinkedList()
		linkedList.InsertAt(student{1, "student 1"}, 0)
		linkedList.InsertAt(student{2, "student 2"}, 1)
		linkedList.InsertAt(student{3, "student 3"}, 2)

		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertAt(student{1, "student 1"}, 0)
		expectedLinkedList.InsertAt(student{3, "student 3"}, 1)

		t.Run("linkedlist should be updated", func(t *testing.T) {
			item, _ := linkedList.RemoveAt(1)

			assert.Equal(t, item, student{2, "student 2"})
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})

	t.Run("when an item is removed at an invalid index", func(t *testing.T) {
		linkedList := NewLinkedList()
		linkedList.InsertFirst(student{1, "student 1"})
		linkedList.InsertFirst(student{2, "student 2"})
		linkedList.InsertFirst(student{3, "student 3"})

		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertFirst(student{1, "student 1"})
		expectedLinkedList.InsertFirst(student{2, "student 2"})
		expectedLinkedList.InsertFirst(student{3, "student 3"})

		t.Run("should return an error and no change in linkedlist", func(t *testing.T) {
			_, err1 := linkedList.RemoveAt(10)
			_, err2 := linkedList.RemoveAt(-1)

			assert.EqualError(t, err1, errIndexOutOfBounds.Error())
			assert.EqualError(t, err2, errIndexOutOfBounds.Error())
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestGet(t *testing.T) {
	t.Run("when linkedlist is empty", func(t *testing.T) {
		linkedList := NewLinkedList()

		expectedLinkedList := NewLinkedList()

		t.Run("it should return nil response", func(t *testing.T) {
			item, _ := linkedList.Get(0)

			assert.Nil(t, item)
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})

	t.Run("when linkedlist is not empty", func(t *testing.T) {
		linkedList := NewLinkedList()
		linkedList.InsertFirst(student{1, "student 1"})
		linkedList.InsertFirst(student{2, "student 2"})
		linkedList.InsertFirst(student{3, "student 3"})

		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertFirst(student{1, "student 1"})
		expectedLinkedList.InsertFirst(student{2, "student 2"})
		expectedLinkedList.InsertFirst(student{3, "student 3"})

		t.Run("it should return the value at the given index and no change in linkedlist", func(t *testing.T) {
			item, _ := linkedList.Get(0)

			assert.Equal(t, item, student{3, "student 3"})
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})

	t.Run("when an invalid index is provided", func(t *testing.T) {
		linkedList := NewLinkedList()
		linkedList.InsertFirst(student{1, "student 1"})
		linkedList.InsertFirst(student{2, "student 2"})
		linkedList.InsertFirst(student{3, "student 3"})

		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertFirst(student{1, "student 1"})
		expectedLinkedList.InsertFirst(student{2, "student 2"})
		expectedLinkedList.InsertFirst(student{3, "student 3"})

		t.Run("should return an error and no change in linkedlist", func(t *testing.T) {
			_, err1 := linkedList.Get(-1)
			_, err2 := linkedList.Get(10)

			assert.EqualError(t, err1, errIndexOutOfBounds.Error())
			assert.EqualError(t, err2, errIndexOutOfBounds.Error())
			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestGetLength(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when linkedlist is provided", func(t *testing.T) {
		t.Run("it should return number of items in linkedlist", func(t *testing.T) {
			linkedList.InsertFirst(student{1, "student 1"})

			assert.Equal(t, linkedList.Getlength(), 1)

			linkedList.RemoveFirst()

			assert.Equal(t, linkedList.Getlength(), 0)
		})
	})
}

func TestIsEmpty(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when linkedlist is not empty", func(t *testing.T) {
		t.Run("it should return false", func(t *testing.T) {
			linkedList.InsertFirst(student{1, "student 1"})

			assert.False(t, linkedList.IsEmpty())
		})
	})

	t.Run("when linkedlist is empty", func(t *testing.T) {
		t.Run("it should return true", func(t *testing.T) {
			linkedList.RemoveFirst()

			assert.True(t, linkedList.IsEmpty())
		})
	})
}

func TestClear(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when linkedlist is provided", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()

		t.Run("it should clear all items in linkedlist", func(t *testing.T) {
			linkedList.InsertFirst(student{1, "student 1"})
			linkedList.InsertFirst(student{2, "student 2"})
			linkedList.InsertFirst(student{3, "student 3"})

			linkedList.Clear()

			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}

func TestReverse(t *testing.T) {
	linkedList := NewLinkedList()

	t.Run("when linkedlist is provided", func(t *testing.T) {
		expectedLinkedList := NewLinkedList()
		expectedLinkedList.InsertLast(student{1, "student 1"})
		expectedLinkedList.InsertLast(student{2, "student 2"})
		expectedLinkedList.InsertLast(student{3, "student 3"})

		t.Run("it should reverse the linkedlist", func(t *testing.T) {
			linkedList.InsertFirst(student{1, "student 1"})
			linkedList.InsertFirst(student{2, "student 2"})
			linkedList.InsertFirst(student{3, "student 3"})

			linkedList.Reverse()

			assert.Equal(t, linkedList, expectedLinkedList)
		})
	})
}
