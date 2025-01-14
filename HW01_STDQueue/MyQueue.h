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
	
	// prints all elements in queue
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
		// if full
		if (capacity <= size)
		{
			// double capacity
			capacity *= 2;

			// create temporary array
			T* tempArray = new T[capacity];

			// copy to temporary array
			for (int i = 0; i < capacity; i++)
			{
				tempArray[i] = data[i];
			}

			// add new alberto to the end
			tempArray[size] = newAlberto;

			// get rid of old array
			delete[] data;

			// update data pointer
			data = tempArray;
		}
		// if not full, add alberto as normal
		else
		{
			data[size] = newAlberto;
		}
		size++;
		Sort();
	}

	// sorts albertos in the queue
	void Sort()
	{
		// checks each alberto
		for (int i = 0; i < size; i++)
		{
			// and compares to every other alberto
			for (int j = 0; j < size; j++)
			{
				// if alberto1 < alberto2, swap places
				if (data[i] < data[j])
				{
					T temp = data[i];
					data[i] = data[j];
					data[j] = temp;
				}
			}
		}
	}

	// removes alberto at the front of the queue

	void Pop()
	{
		// shift all items in queue down by one
		for (int i = 1; i < size; i++)
		{
			data[i - 1] = data[i];
		}
		// remove item on the end and decrease size
		data[size - 1] = NULL;
		size--;
	}

	// returns size of the queue
	int GetSize()
	{
		return size;
	}

	// returns whether the queue is empty
	bool IsEmpty()
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};


#endif //__MYQUEUE_H__
