#include "sets.hpp"

using namespace std;

IntSet::IntSet(int min, int max) {
	len_ = 0;
	size_ = 100;
	list_ = new int[size_];

	inf_ = min;
	sup_ = max;
}

IntSet::IntSet(IntSet& set) {
	len_ = set.len_;
	size_ = set.size_;
	list_ = new int[size_];

	inf_ = set.inf_;
	sup_ = set.sup_;

	for (int i = 0; i < len_; i++) {
		list_[i] = set.list_[i];
	}
}

IntSet::~IntSet() {
	delete[] list_;
}

void IntSet::add_element(int a) {
	if ((a > sup_) || (a < inf_)) throw IntSetException(-2, "Out of range");
	for (int i = 0; i < len_; i++) {
		if (a == list_[i]) return;
	}
	if (len_ >= size_) {
		list_ = (int *)realloc(list_, sizeof(int)*(size_ + 10));
		size += 10;
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

int IntSet::min() {
	if (this->is_empty()) throw IntSetException(-1, "Set is empty");
	int min = list_[0];
	for (int i = 1; i < len_; i++) {
		if (list_[i] < min) min = list_[i];
	}
	return min;
}

int IntSet::min() {
	if (this->is_empty()) throw IntSetException(-1, "Set is empty");
	int max = list_[0];
	for (int i = 1; i < len_; i++) {
		if (list_[i] > max) max = list_[i];
	}
	return max;
}
