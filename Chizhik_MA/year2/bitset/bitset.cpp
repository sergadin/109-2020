#include <cstdlib>
#include <string>

#include "bitset.hpp"

using namespace std;

int BitIntSet::INT_CARDINALITY = (int)(CHAR_BIT * sizeof(int));

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
}

BitIntSet& BitIntSet::operator=(const BitIntSet& B) {
	if (this == &B) return *this;
	inf_ = B.inf_;
	sup_ = B.sup_;
	list_start_ = B.list_start_;
	size_ = B.size_;
	len_ = B.len_;

	free(list_);
	list_ = (int *)malloc(sizeof(int) * size_);

	for (int i = 0; i < size_; i++) list_[i] = B.list_[i];
	return *this;
}

int BitIntSet::min() const {
	if (this->empty()) throw BitIntSetException(2, "Set is empty");
	for (int i = 0; i < this->size_; i++) {
		if (list_[i] == 0) continue;
		for (int k = BitIntSet::INT_CARDINALITY - 1; k >= 0; k--) {
			if (((list_[i] & (1 << k)) ^ (1 << k)) == 0) {
				int min = this->list_start_ + (i + 1) * BitIntSet::INT_CARDINALITY - (k + 1);
				return min;
			}
		}
	}
	throw BitIntSetException(2, "Set is empty");
}

int BitIntSet::max() const {
	if (this->empty()) throw BitIntSetException(2, "Set is empty");
	for (int i = this->size_ - 1; i >= 0; i--) {
		if (list_[i] == 0) continue;
		for (int k = 0; k < BitIntSet::INT_CARDINALITY; k++) {
			if (((list_[i] & (1 << k)) ^ (1 << k)) == 0) {
				int max = this->list_start_ + (i + 1) * BitIntSet::INT_CARDINALITY - (k + 1);
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
	len_ = 0;
}

void BitIntSet::add(int a) {
	if ((a < inf_)) {
		inf_ = a;
		if (a < list_start_) {
			int difference = list_start_ - a;
			int shift = difference / BitIntSet::INT_CARDINALITY + 1;
			list_ = (int *)realloc(list_, sizeof(int) * (size_ + shift));

			for (int i = size_ - 1; i >= 0; i--) {
				list_[i + shift] = list_[i]; 
			}
			for (int j = 0; j < shift; j++) list_[j] = 0;

			size_ += shift;
			list_start_ -= shift * BitIntSet::INT_CARDINALITY;
		}
	} else if (a > sup_) {
		int list_end = list_start_ + size_ * BitIntSet::INT_CARDINALITY - 1;
		sup_ = a;
		if (a > list_end) {
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

	if (list_[index_of_subarr] & elem_mask) return;
	list_[index_of_subarr] |= elem_mask;
	len_++;
}

void BitIntSet::remove (int a) {
	if ((a < inf_) || (a > sup_)) {
		cout << "Warning: you're trying to remove element which is out of the set's range" << endl;
		return;
	}

	int index_in_sub = (a - list_start_) % BitIntSet::INT_CARDINALITY;
	int elem_mask = 1 << (BitIntSet::INT_CARDINALITY - index_in_sub - 1);

	int index_of_subarr = (a - list_start_) / BitIntSet::INT_CARDINALITY;
	if (!(list_[index_of_subarr] & elem_mask)) return;
	list_[index_of_subarr] &= ~elem_mask;
	len_--;
}

bool BitIntSet::belongs (int a) const {
	if ((a > sup_) || (a < inf_)) return false;
	int index_in_sub = (a - list_start_) % BitIntSet::INT_CARDINALITY;
	int elem_mask = 1 << (BitIntSet::INT_CARDINALITY - index_in_sub - 1);

	int index_of_subarr = (a - list_start_) / BitIntSet::INT_CARDINALITY;
	return list_[index_of_subarr] & elem_mask;
}


BitIntSet operator*(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return A;
	BitIntSet product = A;
	for (int i = 0; i < A.len(); i++) {
		if (!(B.belongs(A[i]))) product.remove(A[i]);
	}
	return product;
}

BitIntSet operator+(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return A;
	BitIntSet sum = A;
	if (B.empty()) return sum;

	sum.add(B.min());
	if (B.len() > 1) sum.add(B.max());
	for (int i = 1; i < B.len() - 1; i++) {
		sum.add(B[i]);
	}
	return sum;
}

BitIntSet operator-(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) {
		BitIntSet swap = A;
		swap.clear();
		return swap;
	}
	BitIntSet diff = A;
	if (B.empty()) return diff;

	for (int i = 0; i < B.len(); i++) {
		if (diff.belongs(B[i])) diff.remove(B[i]);
	}
	return diff;
}

BitIntSet operator^(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return BitIntSet(A.left(), A.right());
	BitIntSet sym_diff = (A + B);
	for (int i = 0; i < A.len(); i++) {
		if (B.belongs(A[i])) sym_diff.remove(A[i]);
	}
	return sym_diff;
}

int BitIntSet::operator[](int index) const {
	if ((index >= len_) || (index < 0)) throw BitIntSetException(3, "Element doesn't exist");
	int elems_detected = -1;	
	for (int i = 0; i < this->size_; i++) {
		if (list_[i] == 0) continue;
		for (int k = BitIntSet::INT_CARDINALITY - 1; k >= 0; k--) {
			if (((list_[i] & (1 << k)) ^ (1 << k)) == 0) {
				if (++elems_detected == index) {
					int needed_element = this->list_start_ + (i + 1) * BitIntSet::INT_CARDINALITY - (k + 1);
					return needed_element;
				}
			}
		}
	}
	throw BitIntSetException(3, "Element doesn't exist");
}

BitIntSet& BitIntSet::operator*=(const BitIntSet& B) {
	if (*this == B) return *this;
	BitIntSet product = *this * B;
	*this = product;
	return *this;
}

BitIntSet& BitIntSet::operator+=(const BitIntSet& B) {
	if (*this == B) return *this;
	BitIntSet sum = *this + B;
	*this = sum;
	return *this;
}

BitIntSet& BitIntSet::operator-=(const BitIntSet& B) {
	if (*this == B) {
		this->clear();
		return *this;
	}
	BitIntSet diff = *this - B;
	*this = diff;
	return *this;
}

BitIntSet& BitIntSet::operator^=(const BitIntSet& B) {
	if (*this == B) {
		this->clear();
		return *this;
	}
	BitIntSet sym_diff = *this ^ B;
	*this = sym_diff;
	return *this;
}


bool operator<=(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return true;
	if (A.len() > B.len()) return false;
	for (int i = 0; i < A.len(); i++) {
		if (!B.belongs(A[i])) return false;
	}
	return true;
}

bool operator==(const BitIntSet& A, const BitIntSet& B) {
	if (A.len() != B.len()) return false;
	for (int i = 0; i < A.len(); i++) {
		if (A[i] != B[i]) return false;
	}
	return true;
}

ostream& operator<<(ostream& os, const BitIntSet& set) {
	os << "{";
	for (int i = 0; i < set.len(); i++) {
		os << set[i];
		if (i < set.len() - 1) os << ", ";
	}
	os << "}";
	return os;
}

ostream& operator<<(ostream& os, const BitIntSetException& e) {
	os << "Error " << e.code() << ": " << e.message();
	return os;
}
