package arraylist

import (
	"fmt"
	"sync"
)

type Data interface{}

type array_list struct {
	length int
	array  []Data
	lock   sync.Mutex
}

func (al *array_list) increaseLength() {
	al.length += 1
}

func (al *array_list) decreaseLength() {
	if al.length > 0 {
		al.length -= 1
	}
}

func NewEmptyArrayList() *array_list {
	return &array_list{}
}

func NewArrayList(data []Data) *array_list {
	return &array_list{
		length: len(data),
		array:  data,
	}
}

func (al *array_list) GetLength() int {
	return al.length
}

func (al *array_list) IsEmpty() bool {
	return al.length == 0
}

func (al *array_list) Append(data interface{}) {
	al.lock.Lock()
	defer al.lock.Unlock()

	al.array = append(al.array, data)

	al.increaseLength()
}

func (al *array_list) Remove() interface{} {
	al.lock.Lock()
	defer al.lock.Unlock()

	if !al.IsEmpty() {
		value := al.array[len(al.array)-1]
		al.array = al.array[:len(al.array)-1]
		al.decreaseLength()
		return value
	}

	return nil
}

func (al *array_list) Get(index int) interface{} {
	if !al.IsEmpty() && index >= 0 && index < al.length {
		return al.array[index]
	}

	return nil
}

func (al *array_list) Show() {
	if al.length > 0 {
		for _, v := range al.array {
			fmt.Println(v)
		}
	}
}

func (al *array_list) Clear() {
	al.lock.Lock()
	defer al.lock.Unlock()

	if al.length > 0 {
		al.array = nil
		al.length = 0
	}
}
