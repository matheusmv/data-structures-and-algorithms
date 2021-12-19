package arraylist

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type person struct {
	Name string
}

func TestAppend(t *testing.T) {
	arrayList := NewEmptyArrayList()

	t.Run("when item is appended", func(t *testing.T) {
		expectedArrayList := NewArrayList([]Data{
			person{"Jhon"},
			person{"Alex"},
			person{"Joe"},
		})

		t.Run("arraylist should be updated", func(t *testing.T) {
			arrayList.Append(person{"Jhon"})
			arrayList.Append(person{"Alex"})
			arrayList.Append(person{"Joe"})

			assert.Equal(t, arrayList, expectedArrayList)
		})
	})
}

func TestRemove(t *testing.T) {
	arrayList := NewEmptyArrayList()

	t.Run("when arraylist is empty", func(t *testing.T) {
		expectedArrayList := NewEmptyArrayList()

		t.Run("it should return nil response", func(t *testing.T) {
			item := arrayList.Remove()

			assert.Nil(t, item)
			assert.Equal(t, arrayList, expectedArrayList)
		})
	})

	t.Run("when arraylist is not empty", func(t *testing.T) {
		expectedArrayList := NewArrayList([]Data{
			person{"Jhon"},
			person{"Alex"},
		})

		t.Run("it should return last inserted item and update the arraylist", func(t *testing.T) {
			arrayList.Append(person{"Jhon"})
			arrayList.Append(person{"Alex"})
			arrayList.Append(person{"Joe"})

			item := arrayList.Remove()

			assert.Equal(t, item, person{"Joe"})
			assert.Equal(t, arrayList, expectedArrayList)
		})
	})
}

func TestIsEmpty(t *testing.T) {
	arrayList := NewEmptyArrayList()

	t.Run("when arraylist is not empty", func(t *testing.T) {
		t.Run("it should return false", func(t *testing.T) {
			arrayList.Append(person{"Jhon"})

			assert.False(t, arrayList.IsEmpty())
		})
	})

	t.Run("when arraylist is empty", func(t *testing.T) {
		t.Run("it should return true", func(t *testing.T) {
			arrayList.Remove()

			assert.True(t, arrayList.IsEmpty())
		})
	})
}

func TestGetLength(t *testing.T) {
	arrayList := NewEmptyArrayList()

	t.Run("when arraylist is provided", func(t *testing.T) {
		t.Run("it should return number of items in arraylist", func(t *testing.T) {
			arrayList.Append(person{"Jhon"})

			assert.Equal(t, arrayList.GetLength(), 1)

			arrayList.Remove()

			assert.Equal(t, arrayList.GetLength(), 0)
		})
	})
}

func TestGet(t *testing.T) {
	t.Run("when arraylist is not empty", func(t *testing.T) {
		arrayList := NewEmptyArrayList()

		expectedArrayList := NewArrayList([]Data{
			person{"Jhon"},
			person{"Alex"},
			person{"Joe"},
		})

		t.Run("it should return the value at the given index and no change in arraylist", func(t *testing.T) {
			arrayList.Append(person{"Jhon"})
			arrayList.Append(person{"Alex"})
			arrayList.Append(person{"Joe"})

			item := arrayList.Get(0)

			assert.Equal(t, item, person{"Jhon"})
			assert.Equal(t, arrayList, expectedArrayList)
		})
	})

	t.Run("when arraylist is empty", func(t *testing.T) {
		arrayList := NewEmptyArrayList()

		t.Run("it should return nil", func(t *testing.T) {
			item := arrayList.Get(0)

			assert.Nil(t, item)
		})
	})

	t.Run("when an invalid index is provided", func(t *testing.T) {
		arrayList := NewArrayList([]Data{
			person{"Jhon"},
			person{"Alex"},
			person{"Joe"},
		})

		t.Run("it should return nil", func(t *testing.T) {
			item1 := arrayList.Get(-1)
			item2 := arrayList.Get(10)

			assert.Nil(t, item1)
			assert.Nil(t, item2)
		})
	})
}

func TestClear(t *testing.T) {
	arrayList := NewEmptyArrayList()

	t.Run("when arraylist is provided", func(t *testing.T) {
		expectedArrayList := NewEmptyArrayList()

		t.Run("it should clear all items in arraylist", func(t *testing.T) {
			arrayList.Append(person{"Jhon"})
			arrayList.Append(person{"Alex"})
			arrayList.Append(person{"Joe"})

			arrayList.Clear()

			assert.Equal(t, arrayList, expectedArrayList)
		})
	})
}
