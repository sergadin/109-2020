#include "class.h"

/*#define Max2(a, b) ((a)>(b) & (a) : (b))
#define Min2(a, b) ((a)<(b) & (a) : (b))*/

/* что ещё надо сделать:
 * understand these fucking exceptions aaaaaahhhr
 * Конструктор копирования, оператор присваивания.
 * Пересечение двух множеств, пересечение множества с другим множеством (операторы * и *=).
 * Проверка равенства множеств (оператор сравнения ==).
 * */




limited_int::limited_int(int min, int max) {
    if (min <= max) {
        min_ = min;
        max_ = max;
    } else {
        min_ = max;
        max_ = min;
    }
    size_ = 0;
}

void limited_int::order_data() {
    if ((size_ == 0) || (size_ == 1))
	return;
    int temp;
    for (int i = 0; i < size_ -1; i++) {
	for (int j = 0; j < size_ - i - 1; j++) {
	    if (data_[j] > data_[j+1]) {
		temp = data_[j];
		data_[j] = data_[j+1];
		data_[j+1] = temp;
	    }
	}
    }
    return;
}

bool operator== (const limited_int &right, const limited_int &left) {
    if ((right.min_ != left.min_) || (right.max_ != left.max_) || (right.size_ != left.size_))
	return false;
    for (int i = 0; i < left.size_; i++)
	if(!right.is_there(left.data_[i]))
	     return false;
    for (int i = 0; i < right.size_; i++)
	if(!left.is_there(right.data_[i]))
	     return false;
    return true;
}

bool limited_int::is_there(int element) const {
    if (size_ == 0)
        return false;
    else {
        for (int i = 0; i < size_; i++)
            if (element == data_[i])
                return true;
    }
    return false;
}

int limited_int::how_many() const {
    return size_;
}

int limited_int::left() const {
    return min_;
}
int limited_int::right() const {
    return max_;
}

int limited_int::getmin() const {
    if (size_ == 0)
	return 0;
        //throw UserException(1, "nothing to get :((((");
    int min = data_[0];
    for (int i = 1; i < size_ - 1; i++) {
        if (data_[i] < min)
            min = data_[i];
    }
    return min;
}
int limited_int::getmax() const {
    if (size_ == 0)
	return 0;
        //throw UserException(1, "nothing to get :((((");
    int max = data_[0];
    for (int i = 1; i < size_ - 1; i++) {
        if (data_[i] > max)
            max = data_[i];
    }
    return max;
}

bool limited_int::is_empty() const {
    if (size_ == 0)
        return true;
    else
        return false;
}

limited_int::~limited_int() {
    if (size_ != 0)
        delete[] data_;
    min_ = 0;
    max_ = 0;
}

void limited_int::put_element(int element) {

    if ((element < min_) || (element > max_))
        return;
       // throw UserException(2, "not our client, sorry");

    if (is_there(element) == 1)
        return;
    int *backup;

    if (size_ == 0) {
        data_ = new int[1];
        data_[0] = element;
        size_ ++;

    } else {
        backup = new int[size_ + 1];
        for (int i = 0; i < size_; i++)
            backup[i] = data_[i];
        backup[size_] = element;
        delete[] data_;
        size_++;
        data_ = new int[size_];
        for (int i = 0; i < size_; i++)
            backup[i] = data_[i];
        delete[] backup;
    }


}

void limited_int::delete_element(int element) {
    if (size_ == 0)
        return;
       //throw UserException(3, "nothing to delete :((((");
    if (is_there(element) == 0)
        return;
    if ((element < min_) || (element > max_))
        return;
    if (size_ == 1) {
        delete[] data_;
        size_ = 0;
        return;
    }

    int *backup;
    backup = new int[size_ - 1];
    for (int i = 0; i < size_; i++) {
        backup[i] = data_[i];
        if (element == data_[i]) {
            for (int k = i; k < size_; k++)
                backup[k] = data_[k + 1];
        }
        break;
    }
    delete[] data_;
    size_ --;
    data_ = new int[size_];
    for (int i = 0; i < size_ - 1; i++)
        backup[i] = data_[i];
    delete[] backup;
}


