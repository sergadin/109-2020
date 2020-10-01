#include <string>
#include "sets.hpp"

#include <stdio.h>

using namespace std;

IntSet::IntSet(int min, int max): sup_(max), inf_(min) {
	if (sup_ < inf_) {
		throw IntSetException(-1, "Incorrect range");
	}
	len_ = 0;
	size_ = 10;
	list_ = new int[size_];
}

IntSet::IntSet(const IntSet& set): sup_(set.sup_), inf_(set.inf_) {
	len_ = set.len();
	size_ = len_ + 10;
	list_ = new int[size_];

	for (int i = 0; i < len_; i++) {
		list_[i] = set.list_[i];
	}
}

IntSet::~IntSet() {
	delete[] list_;
}

void IntSet::add_element(int a) {
	if ((a > this->right()) || (a < this->left())) throw IntSetException(-2, "Out of range");
	for (int i = 0; i < len_; i++) {
		if (a == list_[i]) return;
	}
	if (len_ >= size_) {
		list_ = (int *)realloc(list_, sizeof(int)*(size_ + 10));
		size_ += 10;
	}
	list_[len_++] = a;
}

void IntSet::remove_element(int a) {
	int i = 0;
	while(i < len_) {
		if (list_[i] == a) {
			len_--;
			break;
		}
		i++;
	}
	for (; i < len_; i++) {
		list_[i] = list_[i + 1];
	}
}

int IntSet::min() const {
	if (this->is_empty()) throw IntSetException(-3, "Set is empty");
	int min = list_[0];
	for (int i = 1; i < len_; i++) {
		if (list_[i] < min) min = list_[i];
	}
	return min;
}

int IntSet::max() const {
	if (this->is_empty()) throw IntSetException(-3, "Set is empty");
	int max = list_[0];
	for (int i = 1; i < len_; i++) {
		if (list_[i] > max) max = list_[i];
	}
	return max;
}

bool operator<=(const IntSet& A, const IntSet& B) {
	bool subset = true;
	for (int i = 0; i < A.len(); i++) {
		bool belongs = false;
		for (int j = 0; j < B.len(); j++) {
			if (A.list_[i] == B.list_[j]) {
				belongs = true;
				break;
			}
		}
		if (!belongs) break;
	}
	return subset;
}

bool operator==(const IntSet& A, const IntSet& B) {
	return (A <= B) && (B <= A);
}

IntSet& IntSet::operator=(const IntSet &B) {
	if (&B == this) return *this;
	delete[] list_;
	size_ = B.len_ + 10;
	len_ = B.len();
	list_ = new int[size_];

	for (int i = 0; i < len_; i++) {
		list_[i] = B.list_[i];
	}

	return *this;
}

IntSet operator*(const IntSet& A, const IntSet& B) {
	int left = (A.left() < B.left()) ? B.left() : A.left();
	int right = (A.right() > B.right()) ? B.right() : A.right();

	IntSet product = IntSet(left, right);
	for (int i = 0; i < A.len_; i++) {
		for (int k = 0; k < B.len(); k++) {
			if (A.list_[i] == B.list_[k]) {
				product.add_element(A.list_[i]);
			}
		}
	}

	return product;
}

IntSet& operator*=(IntSet& A, const IntSet& B) {
	A = A * B;
	return A;
}
