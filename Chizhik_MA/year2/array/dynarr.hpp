#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <new>

enum ErrorCodes {
	IS_EMPTY = 1,
	INVALID_INDEX,
	ACCESS_DENIED
};

template <class T>
class Array {
	private:
		T *values_;
		int len_;

		int size_;
	public:
		Array();
		Array(const Array<T>& other);
		~Array() { delete[] values_; }

		void insert(int index, const T& x);
		T del(int index, ErrorCodes err_code = INVALID_INDEX, const std::string& error_msg = "There are no elements with the given index");
		
		void push(const T& x);
		void unshift(const T& x);

		T pop();
		T shift();

		T& operator[](int i);
		const T& operator[](int i) const;

		Array<T>& operator=(const Array<T>& array);

		int len() const { return this->len_; }

		template <class U>
		friend std::ostream& operator<<(std::ostream& os, const Array<U>& arr);
};

class ListException {
	private:
		const int code_;
		const std::string reason_;
		ListException();
	public:
		ListException(int code, const std::string& message): code_(code), reason_(message) {}
		int code() const { return code_; }
		const std::string& message() const { return reason_; }
		friend std::ostream& operator<<(std::ostream& os, const ListException& e);
};

std::ostream& operator<<(std::ostream& os, const ListException& e) {
	os << "Error " << e.code() << ": " << e.message();
	return os;
}

template <class T>
Array<T>::Array(): len_(0), size_(10) {
	values_ = new T[size_];
}

template <class T>
Array<T>::Array(const Array<T>& other) {
	values_ = new T[other.len_];
	len_ = other.len_;
	size_ = other.len_;
	for (int i = 0; i < len_; i++) values_[i] = other.values_[i];
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
	delete[] values_;
	values_ = new T[other.len_];
	len_ = other.len_;
	size_ = other.len_;
	for (int i = 0; i < len_; i++) values_[i] = other.values_[i];
	return *this;
}

template <class T>
T Array<T>::del(int index, ErrorCodes err_code, const std::string& error_msg) {
	if (len_ <= index || index < 0) throw ListException(err_code, error_msg);
	int deleted = values_[index];
	--len_;
	for (int i = index; i < len_; i++) values_[i] = values_[i + 1];
	return deleted;
}

template <class T>
T Array<T>::pop() {
	return this->del(len_ - 1, IS_EMPTY, "Set is empty, nothing to pop");
}

template <class T>
T Array<T>::shift() {
	return this->del(0);
}

template <class T>
void Array<T>::insert(int index, const T& x) {
	if (index > len_ || index < 0) throw ListException(INVALID_INDEX, "Can't create element with the given index");
	if (len_ == size_) {
		size_ += 10;
		T* new_values = new T[size_];
		for (int i = 0; i < index; i++) new_values[i] = values_[i];
		new_values[index] = x;
		for (int i = index; i < len_; i++) new_values[i + 1] = values_[i];
		len_++;

		delete[] values_;
		values_ = new_values;
	} else {
		for (int i = len_; i > index; i--) values_[i] = values_[i - 1];
		values_[index] = x;
		len_++;
	}
}

template <class T>
void Array<T>::push(const T& x) {
	this->insert(len_, x);
}

template <class T>
void Array<T>::unshift(const T& x) {
	this->insert(0, x);
}

template <class T>
T& Array<T>::operator[](int index) {
	if (index < 0 || index >= len_) throw ListException(ACCESS_DENIED, "Element can't be reached");
	return values_[index];
}

template <class T>
const T& Array<T>::operator[](int index) const {
	if (index < 0 || index >= len_) throw ListException(INVALID_INDEX, "Element doesn't exist");
	return values_[index];
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
	os << "[";
	for (int i = 0; i < (&arr)->len_; i++) {
		os << arr.values_[i] << ((i < arr.len_ - 1) ? ", " : "");
	}
	os << "]";
	return os;
}