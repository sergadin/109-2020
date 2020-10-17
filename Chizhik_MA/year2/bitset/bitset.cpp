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

	cache_ = NULL;
	cache_len_ = 0;
	last_actual_cached_ = -1;
	cached_max_ = sup_ + 1;

	list_start_ = inf_ - INT_CARDINALITY;
	size_ = range_len / INT_CARDINALITY + 3;

	list_ = (unsigned int *)calloc(size_, sizeof(int));
}

BitIntSet::BitIntSet(const BitIntSet& set): inf_(set.inf_), sup_(set.sup_) {
	len_ = set.len_;

	cache_len_ = set.cache_len_;
	last_actual_cached_ = set.last_actual_cached_;
	cached_max_ = set.cached_max_;

	size_ = set.size_;
	list_start_ = set.list_start_;

	list_ = (unsigned int *)malloc(size_ * sizeof(int));
	cache_ = (int *)malloc(cache_len_ * sizeof(int));

	for (int i = 0; i < size_; i++) list_[i] = set.list_[i];
	for (int j = 0; j < cache_len_; j++) cache_[j] = set.cache_[j];
}

BitIntSet::~BitIntSet() {
	free(list_);
	free(cache_);
}

BitIntSet& BitIntSet::operator=(const BitIntSet& B) {
	if (this == &B) return *this;
	inf_ = B.inf_;
	sup_ = B.sup_;
	list_start_ = B.list_start_;
	size_ = B.size_;

	len_ = B.len_;

	cache_len_ = B.cache_len_;
	last_actual_cached_ = B.last_actual_cached_;
	cached_max_ = B.cached_max_;

	free(list_);
	free(cache_);

	list_ = (unsigned int *)malloc(sizeof(int) * size_);
	cache_ = (int *)malloc(sizeof(int) * cache_len_);
	
	for (int i = 0; i < size_; i++) list_[i] = B.list_[i];
	for (int j = 0; j < cache_len_; j++) cache_[j] = B.cache_[j];
	return *this;
}

int BitIntSet::min() const {
	if (this->empty()) throw BitIntSetException(2, "Set is empty");
	if (last_actual_cached_ >= 0) return cache_[0];
	return this->get(0);

}

int BitIntSet::max() const {
	if (this->empty()) throw BitIntSetException(2, "Set is empty");
	if (cached_max_ <= sup_) return cached_max_;

	for (int i = size_ - 1; i >= 0; i--) {
		if (list_[i] == 0) continue;
		for (int k = 0; k < INT_CARDINALITY; k++) {
			if (((list_[i] & (1 << k)) ^ (1 << k)) == 0) {
				int max = list_start_ + (i + 1) * INT_CARDINALITY - (k + 1);
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
	last_actual_cached_ = -1;
}

void BitIntSet::add(int a) {
	if ((a < inf_)) {
		inf_ = a;
		if (a < list_start_) {
			int difference = list_start_ - a;
			int shift = difference / INT_CARDINALITY + 1;
			list_ = (unsigned int *)realloc(list_, sizeof(int) * (size_ + shift));

			for (int i = size_ - 1; i >= 0; i--) {
				list_[i + shift] = list_[i]; 
			}
			for (int j = 0; j < shift; j++) list_[j] = 0;

			size_ += shift;
			list_start_ -= shift * INT_CARDINALITY;
		}
	} else if (a > sup_) {
		int list_end = list_start_ + size_ * INT_CARDINALITY - 1;
		sup_ = a;
		if (a > list_end) {
			int difference = a - list_end;
			int top = difference / INT_CARDINALITY + 1;
			list_ = (unsigned int *)realloc(list_, sizeof(int) * (size_ + top));
			for (int j = size_; j < size_ + top; j++) list_[j] = 0;

			size_ += top;
		}
	}

	int index_in_sub = (a - list_start_) % INT_CARDINALITY;
	int elem_mask = 1 << (INT_CARDINALITY - index_in_sub - 1);
	
	int index_of_subarr = (a - list_start_) / INT_CARDINALITY;

	if (list_[index_of_subarr] & elem_mask) return;

	if ((last_actual_cached_ > -1) && (cache_[last_actual_cached_] > a)) {
		if (a < cache_[0]) {
			cache_[0] = a;
			last_actual_cached_ = 0;
		} else {
			do {
				last_actual_cached_--;
			} while (cache_[last_actual_cached_] > a);
			cache_[++last_actual_cached_] = a;
		}
	}

	list_[index_of_subarr] |= elem_mask;
	len_++;
}

int BitIntSet::remove (int a) {
	if ((a < inf_) || (a > sup_)) return -1;

	int index_in_sub = (a - list_start_) % INT_CARDINALITY;
	int elem_mask = 1 << (INT_CARDINALITY - index_in_sub - 1);

	int index_of_subarr = (a - list_start_) / INT_CARDINALITY;
	if (!(list_[index_of_subarr] & elem_mask)) return -1;

	if ((last_actual_cached_ > -1) && (cache_[last_actual_cached_] >= a)) {
		if (a <= cache_[0]) last_actual_cached_ = -1; 
		else while ((last_actual_cached_ > -1) && (cache_[last_actual_cached_] >= a)) last_actual_cached_--;
	}
	if (a == cached_max_) cached_max_ = sup_ + 1;

	list_[index_of_subarr] &= ~elem_mask;
	len_--;
	return 0;
}

bool BitIntSet::belongs (int a) const {
	if ((a > sup_) || (a < inf_)) return false;
	int index_in_sub = (a - list_start_) % INT_CARDINALITY;
	int elem_mask = 1 << (INT_CARDINALITY - index_in_sub - 1);

	int index_of_subarr = (a - list_start_) / INT_CARDINALITY;
	return list_[index_of_subarr] & elem_mask;
}


BitIntSet operator*(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return A;
	BitIntSet product = A;
	typename BitIntSet::Iterator I = BitIntSet::Iterator(&A);
	for (; !I.at_end(); I.next()) {
		if (!B.belongs(I.curr())) product.remove(I.curr());
	}
	return product;
}

BitIntSet operator+(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return A;
	BitIntSet sum = A;
	if (B.empty()) return sum;

	sum.add(B.min());
	if (B.len() > 1) sum.add(B.max());

	typename BitIntSet::Iterator I = BitIntSet::Iterator(&B, 1);
	for (; I.curr_index() < (B.len() - 1); I.next()) {
		sum.add(I.curr());
	}
	return sum;
}

BitIntSet operator-(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return BitIntSet(A.left(), A.right());
	BitIntSet diff = A;
	if (B.empty()) return diff;

	typename BitIntSet::Iterator I = BitIntSet::Iterator(&B);
	for (; !I.at_end(); I.next()) {
		if (diff.belongs(I.curr())) diff.remove(I.curr());
	}
	return diff;
}

BitIntSet operator^(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return BitIntSet(A.left(), A.right());
	BitIntSet sym_diff = (A + B);

	typename BitIntSet::Iterator I = BitIntSet::Iterator(&A);
	for (; !I.at_end(); I.next()) {
		if (B.belongs(I.curr())) sym_diff.remove(I.curr());
	}
	return sym_diff;
}

int BitIntSet::get(int index) const {
	typename BitIntSet::Iterator I = BitIntSet::Iterator(this, index);
	return I.curr();
}

int BitIntSet::operator[](int index) {
	if (len_ == 0) throw BitIntSetException(2, "Set is empty");
	if ((index >= len_) || (index < 0)) throw BitIntSetException(3, "Element doesn't exist");

	if (last_actual_cached_ > index - 1) return cache_[index];

	if (cache_len_ != len_) cache_ = (int *)realloc(cache_, sizeof(int) * (cache_len_ = len_));
	int start_position = (last_actual_cached_ >= 0) ? (cache_[last_actual_cached_] - list_start_ + 1) : 0;
	int start_block = start_position / INT_CARDINALITY;
	for (int i = start_block; i < this->size_; i++) {
		if (list_[i] == 0) continue;

		unsigned int bit_mask = 1 << (INT_CARDINALITY - 1);
		for (int k = 0; k < INT_CARDINALITY; k++) {
			if (i * INT_CARDINALITY + k < start_position) {
				bit_mask >>= 1;
				continue;	
			}
			if (((list_[i] & bit_mask) ^ bit_mask) == 0) {
				int next_element = list_start_ + i * INT_CARDINALITY + k;
				cache_[++last_actual_cached_] = next_element;
				if (last_actual_cached_ == index) {
					return next_element;
				}
			}
			bit_mask >>= 1;
		}
	}
	throw BitIntSetException(3, "Element doesn't exist");
}

BitIntSet& BitIntSet::operator*=(const BitIntSet& B) {
	if (this == &B) return *this;
	if (B.empty()) {
		this->clear();
		return *this;
	}

	for (int i = 0; i < this->len(); i++) {
		if (!(B.belongs((*this)[i]))) this->remove((*this)[i--]);
	}
	return *this;
}

BitIntSet& BitIntSet::operator+=(const BitIntSet& B) {
	if ((this == &B) || B.empty()) return *this;

	this->add(B.min());
	if (B.len() > 1) this->add(B.max());

	typename BitIntSet::Iterator I = BitIntSet::Iterator(&B, 1);
	for (; I.curr_index() < B.len() - 1; I.next()) {
		this->add(I.curr());
	}

	return *this;
}

BitIntSet& BitIntSet::operator-=(const BitIntSet& B) {
	if (this == &B) {
		this->clear();
		return *this;
	}
	if (B.empty()) return *this;

	typename BitIntSet::Iterator I = BitIntSet::Iterator(&B);
	for (; !I.at_end(); I.next()) {
		if (this->belongs(I.curr())) this->remove(I.curr());
	}
	return *this;
}

BitIntSet& BitIntSet::operator^=(const BitIntSet& B) {
	if (this == &B) {
		this->clear();
		return *this;
	}
	*this = *this ^ B;

	return *this;
}

bool operator<=(const BitIntSet& A, const BitIntSet& B) {
	if (&A == &B) return true;
	if (A.len() > B.len()) return false;

	typename BitIntSet::Iterator I = BitIntSet::Iterator(&A);
	for (; !I.at_end(); I.next()) {
		if (!B.belongs(I.curr())) return false;
	}
	return true;
}

bool operator==(const BitIntSet& A, const BitIntSet& B) {
	if (A.len() != B.len()) return false;
	typename BitIntSet::Iterator iter_A = BitIntSet::Iterator(&A);
	typename BitIntSet::Iterator iter_B = BitIntSet::Iterator(&B);

	for (; !iter_A.at_end(); iter_A.next(), iter_B.next()) {
		if (iter_A.curr() != iter_B.curr()) return false;
	}
	return true;
}

ostream& operator<<(ostream& os, const BitIntSet& set) {
	typename BitIntSet::Iterator I = BitIntSet::Iterator(&set);
	os << "{";
	for (; !I.at_end(); I.next()) {
		os << I.curr();
		if (I.curr_index() < set.len() - 1) os << ", ";
	}
	os << "}";
	return os;
}

ostream& operator<<(ostream& os, const BitIntSetException& e) {
	os << "Error " << e.code() << ": " << e.message();
	return os;
}

//BitIntSet::Iterator::Iterator(): parent_set_(nullptr), step_(1) {
//	curr_position_ = 0;
//	curr_index_ = -1;
//}

BitIntSet::Iterator::Iterator(const BitIntSet* parent_set, int start_index, int step): parent_set_(parent_set), step_(step) {
	if (step_ == 0) throw BitIntSetException(4, "Step must be non-zero integer");
	if (start_index < -1 || start_index > parent_set_->len_) throw BitIntSetException(5, "Invalid start point of iterator");

	curr_position_= parent_set_->list_start_ - 1;
	curr_index_ = -1;
	
	while (curr_index_ < start_index) this->next();
}

BitIntSet::Iterator::Iterator(const BitIntSet::Iterator& iter): parent_set_(iter.parent_set_), step_(iter.step_) {
	curr_position_ = iter.curr_position_;
	curr_index_ = iter.curr_index_;
}

BitIntSet::Iterator::~Iterator() {}

void BitIntSet::Iterator::begin() {
	curr_position_ = parent_set_->list_start_ - 1;
	curr_index_ = -1;
}

void BitIntSet::Iterator::end() {
	curr_position_ = parent_set_->list_start_ + parent_set_->size_ * INT_CARDINALITY;
	curr_index_ = parent_set_->len_;
}

int BitIntSet::Iterator::next() {
	if (curr_index_ > parent_set_->len_) throw BitIntSetException(3, "Next element doesn't exist");

	if (parent_set_->last_actual_cached_ > curr_index_) {
		curr_position_ = parent_set_->cache_[++curr_index_];
		return curr_position_;
	}

	int start_position = curr_position_ - parent_set_->list_start_ + 1;
	int start_block = start_position / INT_CARDINALITY;

	for (int i = start_block; i < parent_set_->size_; i++) {
		if (parent_set_->list_[i] == 0) continue;
		
		unsigned int bit_mask = 1 << (INT_CARDINALITY - 1);
		for (int k = 0; k < INT_CARDINALITY; k++) {
			if (i * INT_CARDINALITY + k < start_position) {
				bit_mask >>= 1;
				continue;
			}
			if (((parent_set_->list_[i] & bit_mask) ^ bit_mask) == 0) {
				curr_position_ = parent_set_->list_start_ + i * INT_CARDINALITY + k;
				++curr_index_;
				return curr_position_;
			}
			bit_mask >>= 1;
		}
	}
	curr_index_ = parent_set_->len_;
	curr_position_ = parent_set_->list_start_ + parent_set_->size_ * INT_CARDINALITY;
	return curr_index_;
}

int BitIntSet::Iterator::prev() {
	if (curr_index_ < 0) throw BitIntSetException(3, "Previous element doesn't exist");

	if (parent_set_->last_actual_cached_ > curr_index_ - 2 && curr_index_ != 0) {
		curr_position_ = parent_set_->cache_[--curr_index_];
		return curr_position_;
	}

	int start_position = curr_position_ - parent_set_->list_start_ - 1;
	int start_block = start_position / INT_CARDINALITY;

	for (int i = start_block; i >= 0; i--) {
		if (parent_set_->list_[i] == 0) continue;
		
		unsigned int bit_mask = 1;
		for (int k = INT_CARDINALITY - 1; k >= 0; k--) {
			if (i * INT_CARDINALITY + k < start_position) {
				bit_mask <<= 1;
				continue;
			}
			if (((parent_set_->list_[i] & bit_mask) ^ bit_mask) == 0) {
				curr_position_ = parent_set_->list_start_ + i * INT_CARDINALITY + k;
				--curr_index_;
				return curr_position_;
			}
			bit_mask <<= 1;
		}
	}
	curr_index_ = -1;
	curr_position_ = parent_set_->list_start_ - 1;
	return curr_index_;
}

int BitIntSet::Iterator::next_step() {
	int next_item;
	if (step_ > 0) {
		for (int i = 0; i < step_; i++) {
			next_item = this->next();
			if (this->at_end()) break;
		}
	} else {
		for (int i = 0; i < -step_; i++) {
			next_item = this->prev();
			if (this->at_begin()) break;
		}
	}
	return next_item;
}
