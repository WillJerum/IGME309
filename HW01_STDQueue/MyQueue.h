#ifndef __MYQUEUE_H_
#define __MYQUEUE_H_

#include <stdio.h>
#include <iostream>

template <typename T>
class MyQueue
{
public:

	// initialize required vars
	int capacity = 0; // size of queue
	int size = 0; // tracks index
	T* data = nullptr; // data will be stored here
	T* tempArray = nullptr; // temporary array to use later

	MyQueue()
	{
		capacity = 2;
		size = 0;
		data = new T[capacity];
	}
	~MyQueue() // destructor
	{
		Destroy();
	}

	void Destroy(void) // when destructor is called
	{
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
		}
	}

	void CopyData(MyQueue& source) // copies data from source
	{
		this->capacity = source.capacity;
		this->size = source.size;
		this->data = new T[capacity];
		memcpy(this->data, source.data, sizeof(T) * size);
	}

	MyQueue(MyQueue& source)
	{
		if (this != &source)
		{
			CopyData(source);
		}
	}

	MyQueue& operator=(MyQueue& source)
	{
		if (this != &source)
		{
			Destroy();
			CopyData(source);
		}

	}

	void Print(void)
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << data[i] << "\n";
		}
	}

	void Push(int age)
	{
		AlbertoClass newAlberto = AlbertoClass(age);

		// check if queue is full
		// if not, add new alberto
		if (capacity > size)
		{
			data[size] = newAlberto;
			size++;
		}
		// if queue is full, double capacity
		else
		{
			tempArray = new T[capacity * 2];
			for (int i = 0; i < capacity; i++)
			{
				tempArray[i] = data[i];
			}
			// add new alberto to the end
			tempArray[size] = newAlberto;
			// copy new array to current array
			data = tempArray;
			size++;
			capacity = capacity * 2;
		}
	}
	// sorts albertos in the queue
	void Sort()
	{

	}

};


#endif //__MYQUEUE_H__
