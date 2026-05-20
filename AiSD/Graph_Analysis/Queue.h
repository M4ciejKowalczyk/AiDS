#pragma once

template<typename T>
class Queue
{
private:
	T* data;
	size_t capacity;
	size_t size;
	size_t front;
	size_t rear;

	void resize() {
		size_t newCapacity = capacity * 2;
		T* newData = new T[newCapacity];
		for (size_t i = 0; i < size; i++) {
			newData[i] = data[(front + i)%capacity];
		}
		delete[] data;
		data = newData;
		front = 0;
		rear = size;
		capacity = newCapacity;
	}

public:
	Queue() : capacity(8), size(0), front(0), rear(0) {
		data = new T[capacity];
	}

	Queue(const Queue& other) : capacity(other.capacity), size(other.size), front(0), rear(other.size) {
		data = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			data[i] = other.data[(other.front + i) % other.capacity];
		}
	}

	Queue& operator=(const Queue& other) {
		if (this == &other) return *this;

		T* newData = new T[other.capacity];
		for (size_t i = 0; i < other.size; i++) {
			newData[i] = other.data[(other.front + i) % other.capacity];
		}

		delete[] data;
		data = newData;
		capacity = other.capacity;
		size = other.size;
		front = 0;
		rear = other.size;

		return *this;
	}


	~Queue() {
		delete[] data;
	}

	void push(const T& value) {
		if (size == capacity) {
			resize();
		}
		data[rear] = value;
		rear = (rear + 1) % capacity;
		size++;

	}

	void pop() {
		front = (front + 1) % capacity;
		size--;
	}

	T& getFront() {
		return data[front];
	}

	bool empty() const {
		return size == 0;
	}
	
	
};
	
