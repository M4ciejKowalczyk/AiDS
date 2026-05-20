#pragma once


template<typename T>
class Vector
{
private:
	T* data;
	size_t capacity;
	size_t size;

	void resize() {
		capacity = capacity * 2;
		T* newData = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
	}
public:
	Vector() : capacity(8), size(0) {
		data = new T[capacity];
	}

	explicit Vector(size_t initialSize) : capacity(initialSize), size(initialSize) {
		data = new T[capacity];
	}

	Vector(size_t initialSize, const T& initialValue) : capacity(initialSize), size(initialSize) {
		data = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			data[i] = initialValue;
		}
	}

	Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
		data = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			data[i] = other.data[i];
		}
	}

	Vector& operator=(const Vector& other) {
		if (this ==&other)return *this;
		T* newData = new T[other.capacity];
		for (size_t i = 0; i < other.size; i++) {
			newData[i] = other.data[i];
		}

		delete[] data;
		data = newData;
		capacity = other.capacity;
		size = other.size;
		
		return *this;
	}

	~Vector() {
		delete[] data;
	}

	void push_back(const T& value) {
		if (size == capacity) {
			resize();
		}
		data[size] = value;
		size++;
	}

	const T& operator[] (size_t index) const {
		return data[index];
	}

	T& operator[] (size_t index) {
		return data[index];
	}

	size_t getSize() const {
		return size;
	}

	void clear() {
		size = 0;
	}
};

