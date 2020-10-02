#include <cstdlib>
#include <string>

#include "bitset.hpp"

using namespace std;

BitIntSet::BitIntSet(int left, int right): inf_(left), sup_(right) {
	if (inf_ > sup_) {
		throw BitIntSetException(1, "Incorrect range");
	}

	int range_len = sup_ - inf_ + 1;
	len_ = 0;

	list_start_ = inf_ - BitIntSet::INT_CARDINALITY;
	size_ = range_len / BitIntSet::INT_CARDINALITY + 3;

	list_ = (int *)calloc(size_, sizeof(int));
}

BitIntSet::BitIntSet(const BitIntSet& set): inf_(set.inf_), sup_(set.sup_) {
	len_ = set.len_;
	size_ = set.size_;
	list_start_ = set.list_start_;

	list_ = (int *)calloc(size_, sizeof(int));
	for (int i = 0; i < size_; i++) {
		list_[i] = set.list_[i];
	}
}

BitIntSet::~BitIntSet() {
	free(list_);
	list_ = NULL;
}

int BitIntSet::min() const {
	if (this->empty()) throw BitIntSetException(2, "Set is empty");
	int min = this->sup_;
	for (int i = 0; i < this->size_; i++) {
		if (list_[i] == 0) continue;
		for (int k = 0; k < BitIntSet::INT_CARDINALITY; k++) {
			if (((list_[i] & (1 << k)) ^ (1 << k)) == 0) {
				min = this->list_start_ + i * BitIntSet::INT_CARDINALITY + k;
				return min;
			}
		}
	}
	throw BitIntSetException(2, "Set is empty");
}

int BitIntSet::max() const {
	if (this->empty()) throw BitIntSetException(2, "Set is empty");
	int max = this->inf_;
	for (int i = this->size_; i >= 0; i--) {
		if (list_[i] == 0) continue;
		for (int k = BitIntSet::INT_CARDINALITY - 1; k >= 0; k++) {
			if (((list_[i] & (1 << k)) ^ (1 << k)) == 0) {
				max = this->list_start_ + i * BitIntSet::INT_CARDINALITY + k;
				return max;
			}
		}
	}
	throw BitIntSetException(2, "Set is empty");
}

void BitIntSet::clear() {
	for (int i = 0; i < this->size_; i++) {
		list_[i] = 0;
	}
}

void BitIntSet::add(int a) {
	if ((a < inf_)) {
		if (a > list_start_) {
			inf_ = a;
		} else {
			int difference = list_start_ - a;
			int shift = difference / BitIntSet::INT_CARDINALITY + 1;
			list_ = (int *)realloc(list_, sizeof(int) * (size_ + shift));

			for (int i = size_ - 1; i >= 0; i++) {
				list_[i + shift] = list_[i]; 
			}
			for (int j = 0; j < shift; j++) list_[j] = 0;

			size_ += shift;
			list_start_ -= shift * BitIntSet::INT_CARDINALITY;
		}
	} else if (a > sup_) {
		int list_end = list_start_ + size_ * BitIntSet::INT_CARDINALITY;
		if (a < list_end) {
			sup_ = a;
		} else {
			int difference = a - list_end;
			int top = difference / BitIntSet::INT_CARDINALITY + 1;
			list_ = (int *)realloc(list_, sizeof(int) * (size_ + top));
			for (int j = size_; j < size_ + top; j++) list_[j] = 0;

			size_ += top;
		}
	}

	int index_in_sub = (a - list_start_) % BitIntSet::INT_CARDINALITY;
	int elem_mask = 1 << (BitIntSet::INT_CARDINALITY - index_in_sub - 1);
	
	int index_of_subarr = (a - list_start_) / BitIntSet::INT_CARDINALITY;
	list_[index_of_subarr] |= elem_mask;
}

void BitIntSet::remove (int a) {
	if ((a < inf_) || (a > sup_)) {
		cout << "\nWarning: you're trying to remove element which is out of the set's range\n" << endl;
		return;
	}

	int index_in_sub = (a - list_start_) % BitIntSet::INT_CARDINALITY;
	int elem_mask = 1 << (BitIntSet::INT_CARDINALITY - index_in_sub - 1);

	int index_of_subarr = (a - list_start_) / BitIntSet::INT_CARDINALITY;
	list_[index_of_subarr] |= ~elem_mask;
}

bool BitIntSet::belongs (int a) const {
	int index_in_sub = (a - list_start_) % BitIntSet::INT_CARDINALITY;
	int elem_mask = 1 << (BitIntSet::INT_CARDINALITY - index_in_sub - 1);

	int index_of_subarr = (a - list_start_) / BitIntSet::INT_CARDINALITY;
	return list_[index_of_subarr] & elem_mask;
}


BitIntSet operator*(const BitIntSet& A, const BitIntSet& B) {
	return BitIntSet(0, 0);
}

BitIntSet operator+(const BitIntSet& A, const BitIntSet& B) {
	return BitIntSet(0, 0);
}

BitIntSet operator-(const BitIntSet& A, const BitIntSet& B) {
	return BitIntSet(0, 0);
}

BitIntSet operator^(const BitIntSet& A, const BitIntSet& B) {
	return BitIntSet(0, 0);
}


BitIntSet& BitIntSet::operator=(const BitIntSet& B) {
	return *this;
}

const int& BitIntSet::operator[](int index) const {
	return this->list_[0];
}


BitIntSet& BitIntSet::operator*=(const BitIntSet& B) {
	return *this;
}

BitIntSet& BitIntSet::operator+=(const BitIntSet& B) {
	return *this;
}

BitIntSet& BitIntSet::operator-=(const BitIntSet& B) {
	return *this;
}

BitIntSet& BitIntSet::operator^=(const BitIntSet& B) {
	return *this;
}


bool operator<=(const BitIntSet& A, const BitIntSet& B) {
	return true;
}

bool operator==(const BitIntSet& A, const BitIntSet& B) {
	return false;
}

ostream& operator<<(ostream& os, const BitIntSet& set) {
	os << "[";
	for (int i = 0; i < set.len(); i++) {
		os << set[i];
		if (i < set.len() - 1) os << ", ";
	}
	os << "]";
	return os;
}

ostream& operator<<(ostream& os, const BitIntSetException& e) {
	os << "Error " << e.code() << ": " << e.message() << endl;
	return os;
}
