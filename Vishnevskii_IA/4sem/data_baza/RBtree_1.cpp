

#include<cstdio>
#include<iostream>
#include<string>
#include <list>
#include <utility>
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>


using namespace std;

struct Student {
	string name;
	int group;
	double rating;
	// char *info;
};

class Hash_table {
public:
	struct node {
		int group_number;
		std::list<Student> group_list;
		node* next = nullptr;
		node* prev = nullptr;

		node() = default;
		node(const node& rhs) = default;

		~node() {
			if (next != nullptr) {
				delete next;
			}
		}

		node(int value, const std::list<Student>& group)
			: group_number(value),
			group_list(group),
			next(nullptr),
			prev(nullptr) {}

		node(int value, const std::list<Student>& group, node* new_prev)
			: group_number(value),
			group_list(group),
			next(nullptr),
			prev(new_prev) {
			prev->next = this;
		}
	};

	class iterator : public std::iterator<std::forward_iterator_tag, int> {
		node* ptr = nullptr;
		Hash_table* set = nullptr;

	public:
		iterator() = default;
		~iterator() = default;

		explicit iterator(node* new_ptr) : ptr(new_ptr) {}

		iterator(node* new_ptr, Hash_table* new_set) : ptr(new_ptr), set(new_set) {}

		iterator& operator++() {
			if (ptr == nullptr) {
				return *this;
			}
			if (ptr->next != nullptr) {
				ptr = ptr->next;
			}
			else {
				size_t hash_value =
					set->hash_func(ptr->group_number) % set->capacity + 1;
				if (hash_value >= set->hash_table.size()) {
					ptr = nullptr;
					return *this;
				}
				while ((hash_value <= set->hash_table.size()) &&
					set->hash_table[hash_value] == nullptr) {
					hash_value++;
				}
				ptr = set->hash_table[hash_value];
			}
			return *this;
		}

		iterator operator++(int) {
			iterator res(ptr);
			++(*this);
			return res;
		}

		std::list<Student>& operator*() { return ptr->group_list; }

		std::list<Student>* operator->() { return &(ptr->group_list); }

		bool operator!=(iterator rhs) const { return ptr != rhs.ptr; }

		bool operator==(iterator rhs) const { return ptr == rhs.ptr; }
	};

	Hash_table() { hash_table.resize(capacity, nullptr); }

	~Hash_table() {
		for (auto& i : hash_table) {
			delete i;
		}
	}

	Hash_table(Hash_table& rhs)
		: hash_func(rhs.hash_func), capacity(rhs.capacity) {
		hash_table.resize(capacity, nullptr);
		for (const auto& i : rhs) {
			for (const auto& j : i) {
				insert(j);
			}
		}
	}

	Hash_table& operator=(Hash_table& rhs) {
		if (this == &rhs) {
			return *this;
		}
		hash_func = rhs.hash_func;
		capacity = rhs.capacity;
		hash_table.resize(capacity, nullptr);
		for (const auto& i : rhs) {
			for (auto j : i) {
				insert(j);
			}
		}
		return *this;
	}

	explicit Hash_table(size_t new_length) : capacity(new_length) {
		hash_table.resize(capacity, nullptr);
	}

	iterator begin() {
		if (empty()) {
			return end();
		}
		size_t hash_value = 0;
		while (hash_value < hash_table.size() &&
			hash_table[hash_value] == nullptr) {
			hash_value++;
		}
		return iterator(hash_table[hash_value], this);
	}

	iterator end() { return iterator(nullptr, this); }

	iterator insert(const Student& student) {
		if (size_ == capacity) {
			grow();
		}
		node* pos = get_pos(student.group);
		if (pos == nullptr) {
			++size_;
			size_t hash = hash_func(student.group) % capacity;
			std::list<Student> group;
			group.push_back(student);
			hash_table[hash] = new node(student.group, group);
			return iterator(hash_table[hash], this);
		}
		else {
			if (pos->group_number == student.group) {
				pos->group_list.push_back(student);
				return iterator(pos, this);
			}
			++size_;
			std::list<Student> group;
			group.push_back(student);
			pos->next = new node(student.group, group, pos);
			pos->next->prev = pos;
			return iterator(pos->next, this);
		}
	}

	void erase(int group_number) {
		node* delete_node = get_pos(group_number);
		if (delete_node == nullptr) {
			return;
		}
		size_t hash = hash_func(group_number) % capacity;
		if (delete_node->next == nullptr && delete_node->prev == nullptr) {
			hash_table[hash] = nullptr;
		}
		else if (delete_node->next == nullptr) {
			delete_node->prev->next = nullptr;
		}
		else if (delete_node->prev == nullptr) {
			delete_node->next->prev = nullptr;
			hash_table[hash] = delete_node->next;
			delete_node->next = nullptr;
		}
		else {
			delete_node->prev->next = delete_node->next;
			delete_node->next->prev = delete_node->prev;
			delete_node->next = nullptr;
		}
		delete delete_node;
		--size_;
	}

	iterator find(const int& group_number) {
		node* bucket = get_pos(group_number);
		if (bucket == nullptr || bucket->group_number != group_number) {
			return end();
		}
		return iterator(bucket, this);
	}

	size_t size() const { return size_; }

	bool empty() const { return size_ == 0; }

	void clear() { size_ = 0; }

	void swap(Hash_table& rhs) {
		std::swap(hash_table, rhs.hash_table);
		std::swap(hash_func, rhs.hash_func);
		std::swap(capacity, rhs.capacity);
		std::swap(size_, rhs.size_);
	}

	std::list<Student> operator[](size_t group_number) {
		return get_pos(group_number)->group_list;
	}

private:
	std::hash<int> hash_func;
	size_t size_ = 0;
	size_t capacity = 8;
	std::vector<node*> hash_table;

	void grow() {
		size_t new_length = capacity * 2;
		Hash_table new_set(new_length);
		for (const auto& i : *this) {
			for (auto j : i) {
				new_set.insert(j);
			}
		}
		swap(new_set);
	}

	node* get_pos(int group_number) const {
		size_t hash = hash_func(group_number) % capacity;
		node* pos = hash_table[hash];
		if (pos == nullptr) {
			return nullptr;
		}
		else {
			while (pos->next != nullptr && pos->group_number != group_number) {
				pos = pos->next;
			}
			return pos;
		}
	}
};


//! класс дерева по полю name
class RBtree_name {
	struct node_st { node_st* p1, * p2; list<Student> student_list; Student student; double value; bool red; string name; int group; }; // структура узла
	node_st* tree_root;					//!< корень
	int nodes_count;					//!< число узлов дерева
private:
	node_st* NewNode(Student student);		//!< выделение новой вешины
	void DelNode(node_st*);				//!< удаление вершины
	void Clear(node_st*);				//!< снос дерева (рекурсивная часть)
	node_st* Rotate21(node_st*);		//!< вращение влево
	node_st* Rotate12(node_st*);		//!< вращение вправо
	void BalanceInsert(node_st**);		//!< балансировка вставки
	bool BalanceRemove1(node_st**);		//!< левая балансировка удаления
	bool BalanceRemove2(node_st**);		//!< правая балансировка удаления
	bool Insert(Student, node_st**);			//!< рекурсивная часть вставки
	bool GetMin(node_st**, node_st**);	//!< найти и убрать максимальный узел поддерева
	bool Remove(node_st**, double);			//!< рекурсивная часть удаления
public: // отладочная часть
	enum check_code { error_balance, error_struct, ok };	// код ошибки
	void Show();						//!< вывод дерева
	check_code Check();					//!< проверка дерева
	bool TreeWalk(bool*, int);			//!< обход дерева и сверка значений с массивом
private: // отладочная часть
	void Show(node_st*, int, char);		//!< вывод дерева, рекурсивная часть
	check_code Check(node_st*, int, int&);//!< проверка дерева (рекурсивная часть)
	bool TreeWalk(node_st*, bool*, int);	//!< обход дерева и сверка значений с массивом (рекурсивная часть)
public:
	RBtree_name();
	~RBtree_name();
	void Clear();			//!< снести дерево				
	bool Find(double);			//!< найти значение
	void Insert(Student);		//!< вставить значение
	void Remove(double);		//!< удалить значение
	int GetNodesCount();	//!< узнать число узлов
};


RBtree_name::RBtree_name()
{
	tree_root = 0;
	nodes_count = 0;
}

RBtree_name::~RBtree_name()
{
	Clear(tree_root);
}

int RBtree_name::GetNodesCount()
{
	return nodes_count;
}

// выделение новой вешины
RBtree_name::node_st* RBtree_name::NewNode(Student student)
{
	nodes_count++;
	node_st* node = new node_st;
	node->student = student;
	node->group = student.group;
	node->name = student.name;
	node->value = student.rating;
	node->p1 = node->p2 = 0;
	node->red = true;
	return node;
}

// удаление вершины
void RBtree_name::DelNode(node_st* node)
{
	nodes_count--;
	delete node;
}

// снос дерева (рекурсивная часть)
void RBtree_name::Clear(node_st* node)
{
	if (!node) return;
	Clear(node->p1);
	Clear(node->p2);
	DelNode(node);
}

// вывод дерева, рекурсивная часть
//! \param node узел
//! \param depth глубина
//! \param dir   значёк
//! \code Show(root,0,'*'); \endcode
void RBtree_name::Show(node_st* node, int depth, char dir)
{
	int n;
	if (!node) return;
	for (n = 0; n < depth; n++) putchar(' ');

	printf("%c[Name: %s, Group Number: %d, Rating: %f | ", dir, node->name.c_str(), node->group, node->value);

	for (auto i = node->student_list.begin(); i != node->student_list.end(); ++i) cout << "Name: " << i->name << ", " << " Group Number: " << i->group << ", Rating: " << i->rating <<" | ";

	printf("] (%s)\n", node->red ? "red" : "black");

	Show(node->p1, depth + 2, '-');
	Show(node->p2, depth + 2, '+');
}


// вращение влево
//! \param index индеск вершины
//! \result новая вершина дерева
RBtree_name::node_st* RBtree_name::Rotate21(node_st* node)
{
	node_st* p2 = node->p2;
	node_st* p21 = p2->p1;
	p2->p1 = node;
	node->p2 = p21;
	return p2;
}

// вращение вправо
//! \param index индеск вершины
//! \result новая вершина дерева
RBtree_name::node_st* RBtree_name::Rotate12(node_st* node)
{
	node_st* p1 = node->p1;
	node_st* p12 = p1->p2;
	p1->p2 = node;
	node->p1 = p12;
	return p1;
}


// балансировка вершины
void RBtree_name::BalanceInsert(node_st** root)
{
	node_st* p1, * p2, * px1, * px2;
	node_st* node = *root;
	if (node->red) return;
	p1 = node->p1;
	p2 = node->p2;
	if (p1 && p1->red) {
		px2 = p1->p2;				// задача найти две рядом стоящие крастне вершины
		if (px2 && px2->red) p1 = node->p1 = Rotate21(p1);
		px1 = p1->p1;
		if (px1 && px1->red) {
			node->red = true;
			p1->red = false;
			if (p2 && p2->red) {	// отделаемся перекраской вершин
				px1->red = true;
				p2->red = false;
				return;
			}
			*root = Rotate12(node);
			return;
		}
	}
	// тоже самое в другую сторону
	if (p2 && p2->red) {
		px1 = p2->p1;				// задача найти две рядом стоящие крастне вершины
		if (px1 && px1->red) p2 = node->p2 = Rotate12(p2);
		px2 = p2->p2;
		if (px2 && px2->red) {
			node->red = true;
			p2->red = false;
			if (p1 && p1->red) {	// отделаемся перекраской вершин
				px2->red = true;
				p1->red = false;
				return;
			}
			*root = Rotate21(node);
			return;
		}
	}
}


bool RBtree_name::BalanceRemove1(node_st** root)
{
	node_st* node = *root;
	node_st* p1 = node->p1;
	node_st* p2 = node->p2;
	if (p1 && p1->red) {
		p1->red = false; return false;
	}
	if (p2 && p2->red) { // случай 1
		node->red = true;
		p2->red = false;
		node = *root = Rotate21(node);
		if (BalanceRemove1(&node->p1)) node->p1->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st* p21 = p2->p1;
	node_st* p22 = p2->p2;
	if (p21 && p21->red) mask |= 1;
	if (p22 && p22->red) mask |= 2;
	switch (mask)
	{
	case 0:		// случай 2 - if((!p21 || !p21->red) && (!p22 || !p22->red))
		p2->red = true;
		return true;
	case 1:
	case 3:		// случай 3 - if(p21 && p21->red)
		p2->red = true;
		p21->red = false;
		p2 = node->p2 = Rotate12(p2);
		p22 = p2->p2;
	case 2:		// случай 4 - if(p22 && p22->red)
		p2->red = node->red;
		p22->red = node->red = false;
		*root = Rotate21(node);
	}
	return false;
}

bool RBtree_name::BalanceRemove2(node_st** root)
{
	node_st* node = *root;
	node_st* p1 = node->p1;
	node_st* p2 = node->p2;
	if (p2 && p2->red) { p2->red = false; return false; }
	if (p1 && p1->red) { // случай 1
		node->red = true;
		p1->red = false;
		node = *root = Rotate12(node);
		if (BalanceRemove2(&node->p2)) node->p2->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st* p11 = p1->p1;
	node_st* p12 = p1->p2;
	if (p11 && p11->red) mask |= 1;
	if (p12 && p12->red) mask |= 2;
	switch (mask) {
	case 0:		// случай 2 - if((!p12 || !p12->red) && (!p11 || !p11->red))
		p1->red = true;
		return true;
	case 2:
	case 3:		// случай 3 - if(p12 && p12->red)
		p1->red = true;
		p12->red = false;
		p1 = node->p1 = Rotate21(p1);
		p11 = p1->p1;
	case 1:		// случай 4 - if(p11 && p11->red)
		p1->red = node->red;
		p11->red = node->red = false;
		*root = Rotate12(node);
	}
	return false;
}


bool RBtree_name::Find(double value)
{
	node_st* node = tree_root;
	while (node) {
		if (node->value == value) return true;
		node = node->value > value ? node->p1 : node->p2;
	}
	return false;
}
// потом изменю, если надо будет 

// рекурсивная часть вставки
//! \result true если изменений небыло или балансировка в данной вершине не нужна
bool RBtree_name::Insert(Student student, node_st** root)
{
	node_st* node = *root;
	if (!node) *root = NewNode(student);
	else {
		if (student.name == node->name)
		{

			node->student_list.push_back(student);

			return true;
		}
		if (Insert(student, student.name < node->name ? &node->p1 : &node->p2)) return true;
		BalanceInsert(root);
	}
	return false;
}


// найти и убрать максимальный узел поддерева
//! \param root корень дерева в котором надо найти элемент
//! \retval res эелемент который был удалён
//! \result true если нужен баланс
bool RBtree_name::GetMin(node_st** root, node_st** res)
{
	node_st* node = *root;
	if (node->p1) {
		if (GetMin(&node->p1, res)) return BalanceRemove1(root);
	}
	else {
		*root = node->p2;
		*res = node;
		return !node->red;
	}
	return false;
}


// рекурсивная часть удаления
//! \result true если нужен баланс
bool RBtree_name::Remove(node_st** root, double value)
{
	node_st* t, * node = *root;
	if (!node) return false;
	if (node->value < value) {
		if (Remove(&node->p2, value))	return BalanceRemove2(root);
	}
	else if (node->value > value) {
		if (Remove(&node->p1, value))	return BalanceRemove1(root);
	}
	else {
		bool res;
		if (!node->p2) {
			*root = node->p1;
			res = !node->red;
		}
		else {
			res = GetMin(&node->p2, root);
			t = *root;
			t->red = node->red;
			t->p1 = node->p1;
			t->p2 = node->p2;
			if (res) res = BalanceRemove2(root);
		}
		DelNode(node);
		return res;
	}
	return 0;
}             // потом переделаю


// вывод дерева
void RBtree_name::Show()
{
	printf("[tree_name]\n");
	Show(tree_root, 0, '*');
}

// функция вставки
void RBtree_name::Insert(Student student)
{
	Insert(student, &tree_root);
	if (tree_root) tree_root->red = false;
}

// удаление узла
void RBtree_name::Remove(double value)
{
	Remove(&tree_root, value);
}

// снос дерева
void RBtree_name::Clear()
{
	Clear(tree_root);
	tree_root = 0;
}


// проверка дерева (рекурсивная часть)
//! \param tree дерево
//! \param d    текущая чёрная глубина
//! \param h    эталонная чёрная глубина
//! \result 0 или код ошибки
RBtree_name::check_code RBtree_name::Check(node_st* tree, int d, int& h)
{
	if (!tree) {
		// количество чёрных вершин на любом пути одинаковое
		if (h < 0) h = d;
		return h == d ? ok : error_balance;
	}
	node_st* p1 = tree->p1;
	node_st* p2 = tree->p2;
	// красная вершина должна иметь чёрных потомков
	if (tree->red && (p1 && p1->red || p2 && p2->red)) return error_struct;
	if (p1 && tree->value<p1->value || p2 && tree->value>p2->value) return error_struct;
	if (!tree->red) d++;
	check_code n = Check(p1, d, h); if (n) return n;
	return Check(p2, d, h);
}


// проверка дерева
RBtree_name::check_code RBtree_name::Check()
{
	int d = 0;
	int h = -1;
	if (!tree_root) return ok;
	if (tree_root->red) return error_struct;
	return Check(tree_root, d, h);
}

// обход дерева и сверка значений с массивом (рекурсивная часть)
//! \param node  корень дерева
//! \param array массив для сверки
//! \param size  размер массива
bool RBtree_name::TreeWalk(node_st* node, bool* array, int size)
{
	if (!node) return false;
	int value = node->value;
	if (value < 0 || value >= size || !array[value]) return true;
	array[value] = false;
	return TreeWalk(node->p1, array, size) || TreeWalk(node->p2, array, size);
}

// обход дерева и сверка значений с массивом
//! \param array массив для сверки
//! \param size  размер массива
bool RBtree_name::TreeWalk(bool* array, int size)
{
	if (TreeWalk(tree_root, array, size)) return true;
	for (int n = 0; n < size; n++) if (array[n]) return true;
	return false;
}



//! класс дерева по полю rating 
class RBtree_rating {
	struct node_st { node_st* p1, * p2; list<Student> student_list; Student student; double value; bool red; string name; int group; }; // структура узла
	node_st* tree_root;					//!< корень
	int nodes_count;					//!< число узлов дерева
private:
	node_st* NewNode(Student student);		//!< выделение новой вешины
	void DelNode(node_st*);				//!< удаление вершины
	void Clear(node_st*);				//!< снос дерева (рекурсивная часть)
	node_st* Rotate21(node_st*);		//!< вращение влево
	node_st* Rotate12(node_st*);		//!< вращение вправо
	void BalanceInsert(node_st**);		//!< балансировка вставки
	bool BalanceRemove1(node_st**);		//!< левая балансировка удаления
	bool BalanceRemove2(node_st**);		//!< правая балансировка удаления
	bool Insert(Student, node_st**);			//!< рекурсивная часть вставки
	bool GetMin(node_st**, node_st**);	//!< найти и убрать максимальный узел поддерева
	bool Remove(node_st**, double);			//!< рекурсивная часть удаления
public: // отладочная часть
	enum check_code { error_balance, error_struct, ok };	// код ошибки
	void Show();						//!< вывод дерева
	check_code Check();					//!< проверка дерева
	bool TreeWalk(bool*, int);			//!< обход дерева и сверка значений с массивом
private: // отладочная часть
	void Show(node_st*, int, char);		//!< вывод дерева, рекурсивная часть
	check_code Check(node_st*, int, int&);//!< проверка дерева (рекурсивная часть)
	bool TreeWalk(node_st*, bool*, int);	//!< обход дерева и сверка значений с массивом (рекурсивная часть)
public:
	RBtree_rating();
	~RBtree_rating();
	void Clear();			//!< снести дерево				
	bool Find(double);			//!< найти значение
	void Insert(Student);		//!< вставить значение
	void Remove(double);		//!< удалить значение
	int GetNodesCount();	//!< узнать число узлов
};


RBtree_rating::RBtree_rating()
{
	tree_root = 0;
	nodes_count = 0;
}

RBtree_rating::~RBtree_rating()
{
	Clear(tree_root);
}

int RBtree_rating::GetNodesCount()
{
	return nodes_count;
}

// выделение новой вешины
RBtree_rating::node_st* RBtree_rating::NewNode(Student student)
{
	nodes_count++;
	node_st* node = new node_st;
	node->student = student;
	node->group = student.group;
	node->name = student.name;
	node->value = student.rating;
	node->p1 = node->p2 = 0;
	node->red = true;
	return node;
}

// удаление вершины
void RBtree_rating::DelNode(node_st* node)
{
	nodes_count--;
	delete node;
}

// снос дерева (рекурсивная часть)
void RBtree_rating::Clear(node_st* node)
{
	if (!node) return;
	Clear(node->p1);
	Clear(node->p2);
	DelNode(node);
}

// вывод дерева, рекурсивная часть
//! \param node узел
//! \param depth глубина
//! \param dir   значёк
//! \code Show(root,0,'*'); \endcode
void RBtree_rating::Show(node_st* node, int depth, char dir)
{
	int n;
	if (!node) return;
	for (n = 0; n < depth; n++) putchar(' ');

	printf("%c[Name: %s, Group Number: %d | ", dir, node->name.c_str(), node->group);

	for (auto i = node->student_list.begin(); i != node->student_list.end(); ++i) cout << "Name: " << i->name << " " << "Group Number: " << i->group << " | ";

	printf("Rating of these students: %f] (%s)\n", node->value, node->red ? "red" : "black");

	Show(node->p1, depth + 2, '-');
	Show(node->p2, depth + 2, '+');
}


// вращение влево
//! \param index индеск вершины
//! \result новая вершина дерева
RBtree_rating::node_st* RBtree_rating::Rotate21(node_st* node)
{
	node_st* p2 = node->p2;
	node_st* p21 = p2->p1;
	p2->p1 = node;
	node->p2 = p21;
	return p2;
}

// вращение вправо
//! \param index индеск вершины
//! \result новая вершина дерева
RBtree_rating::node_st* RBtree_rating::Rotate12(node_st* node)
{
	node_st* p1 = node->p1;
	node_st* p12 = p1->p2;
	p1->p2 = node;
	node->p1 = p12;
	return p1;
}


// балансировка вершины
void RBtree_rating::BalanceInsert(node_st** root)
{
	node_st* p1, * p2, * px1, * px2;
	node_st* node = *root;
	if (node->red) return;
	p1 = node->p1;
	p2 = node->p2;
	if (p1 && p1->red) {
		px2 = p1->p2;				// задача найти две рядом стоящие крастне вершины
		if (px2 && px2->red) p1 = node->p1 = Rotate21(p1);
		px1 = p1->p1;
		if (px1 && px1->red) {
			node->red = true;
			p1->red = false;
			if (p2 && p2->red) {	// отделаемся перекраской вершин
				px1->red = true;
				p2->red = false;
				return;
			}
			*root = Rotate12(node);
			return;
		}
	}
	// тоже самое в другую сторону
	if (p2 && p2->red) {
		px1 = p2->p1;				// задача найти две рядом стоящие крастне вершины
		if (px1 && px1->red) p2 = node->p2 = Rotate12(p2);
		px2 = p2->p2;
		if (px2 && px2->red) {
			node->red = true;
			p2->red = false;
			if (p1 && p1->red) {	// отделаемся перекраской вершин
				px2->red = true;
				p1->red = false;
				return;
			}
			*root = Rotate21(node);
			return;
		}
	}
}


bool RBtree_rating::BalanceRemove1(node_st** root)
{
	node_st* node = *root;
	node_st* p1 = node->p1;
	node_st* p2 = node->p2;
	if (p1 && p1->red) {
		p1->red = false; return false;
	}
	if (p2 && p2->red) { // случай 1
		node->red = true;
		p2->red = false;
		node = *root = Rotate21(node);
		if (BalanceRemove1(&node->p1)) node->p1->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st* p21 = p2->p1;
	node_st* p22 = p2->p2;
	if (p21 && p21->red) mask |= 1;
	if (p22 && p22->red) mask |= 2;
	switch (mask)
	{
	case 0:		// случай 2 - if((!p21 || !p21->red) && (!p22 || !p22->red))
		p2->red = true;
		return true;
	case 1:
	case 3:		// случай 3 - if(p21 && p21->red)
		p2->red = true;
		p21->red = false;
		p2 = node->p2 = Rotate12(p2);
		p22 = p2->p2;
	case 2:		// случай 4 - if(p22 && p22->red)
		p2->red = node->red;
		p22->red = node->red = false;
		*root = Rotate21(node);
	}
	return false;
}

bool RBtree_rating::BalanceRemove2(node_st** root)
{
	node_st* node = *root;
	node_st* p1 = node->p1;
	node_st* p2 = node->p2;
	if (p2 && p2->red) { p2->red = false; return false; }
	if (p1 && p1->red) { // случай 1
		node->red = true;
		p1->red = false;
		node = *root = Rotate12(node);
		if (BalanceRemove2(&node->p2)) node->p2->red = false;
		return false;
	}
	unsigned int mask = 0;
	node_st* p11 = p1->p1;
	node_st* p12 = p1->p2;
	if (p11 && p11->red) mask |= 1;
	if (p12 && p12->red) mask |= 2;
	switch (mask) {
	case 0:		// случай 2 - if((!p12 || !p12->red) && (!p11 || !p11->red))
		p1->red = true;
		return true;
	case 2:
	case 3:		// случай 3 - if(p12 && p12->red)
		p1->red = true;
		p12->red = false;
		p1 = node->p1 = Rotate21(p1);
		p11 = p1->p1;
	case 1:		// случай 4 - if(p11 && p11->red)
		p1->red = node->red;
		p11->red = node->red = false;
		*root = Rotate12(node);
	}
	return false;
}


bool RBtree_rating::Find(double value)
{
	node_st* node = tree_root;
	while (node) {
		if (node->value == value) return true;
		node = node->value > value ? node->p1 : node->p2;
	}
	return false;
}


// рекурсивная часть вставки
//! \result true если изменений небыло или балансировка в данной вершине не нужна
bool RBtree_rating::Insert(Student student, node_st** root)
{
	node_st* node = *root;
	if (!node) *root = NewNode(student);
	else {
		if (student.rating == node->value)
		{

			node->student_list.push_back(student);

			return true;
		}
		if (Insert(student, student.rating < node->value ? &node->p1 : &node->p2)) return true;
		BalanceInsert(root);
	}
	return false;
}


// найти и убрать максимальный узел поддерева
//! \param root корень дерева в котором надо найти элемент
//! \retval res эелемент который был удалён
//! \result true если нужен баланс
bool RBtree_rating::GetMin(node_st** root, node_st** res)
{
	node_st* node = *root;
	if (node->p1) {
		if (GetMin(&node->p1, res)) return BalanceRemove1(root);
	}
	else {
		*root = node->p2;
		*res = node;
		return !node->red;
	}
	return false;
}


// рекурсивная часть удаления
//! \result true если нужен баланс
bool RBtree_rating::Remove(node_st** root, double value)
{
	node_st* t, * node = *root;
	if (!node) return false;
	if (node->value < value) {
		if (Remove(&node->p2, value))	return BalanceRemove2(root);
	}
	else if (node->value > value) {
		if (Remove(&node->p1, value))	return BalanceRemove1(root);
	}
	else {
		bool res;
		if (!node->p2) {
			*root = node->p1;
			res = !node->red;
		}
		else {
			res = GetMin(&node->p2, root);
			t = *root;
			t->red = node->red;
			t->p1 = node->p1;
			t->p2 = node->p2;
			if (res) res = BalanceRemove2(root);
		}
		DelNode(node);
		return res;
	}
	return 0;
}             // потом переделаю


// вывод дерева
void RBtree_rating::Show()
{
	printf("[tree_rating]\n");
	Show(tree_root, 0, '*');
}

// функция вставки
void RBtree_rating::Insert(Student student)
{
	Insert(student, &tree_root);
	if (tree_root) tree_root->red = false;
}

// удаление узла
void RBtree_rating::Remove(double value)
{
	Remove(&tree_root, value);
}

// снос дерева
void RBtree_rating::Clear()
{
	Clear(tree_root);
	tree_root = 0;
}


// проверка дерева (рекурсивная часть)
//! \param tree дерево
//! \param d    текущая чёрная глубина
//! \param h    эталонная чёрная глубина
//! \result 0 или код ошибки
RBtree_rating::check_code RBtree_rating::Check(node_st* tree, int d, int& h)
{
	if (!tree) {
		// количество чёрных вершин на любом пути одинаковое
		if (h < 0) h = d;
		return h == d ? ok : error_balance;
	}
	node_st* p1 = tree->p1;
	node_st* p2 = tree->p2;
	// красная вершина должна иметь чёрных потомков
	if (tree->red && (p1 && p1->red || p2 && p2->red)) return error_struct;
	if (p1 && tree->value<p1->value || p2 && tree->value>p2->value) return error_struct;
	if (!tree->red) d++;
	check_code n = Check(p1, d, h); if (n) return n;
	return Check(p2, d, h);
}


// проверка дерева
RBtree_rating::check_code RBtree_rating::Check()
{
	int d = 0;
	int h = -1;
	if (!tree_root) return ok;
	if (tree_root->red) return error_struct;
	return Check(tree_root, d, h);
}

// обход дерева и сверка значений с массивом (рекурсивная часть)
//! \param node  корень дерева
//! \param array массив для сверки
//! \param size  размер массива
bool RBtree_rating::TreeWalk(node_st* node, bool* array, int size)
{
	if (!node) return false;
	int value = node->value;
	if (value < 0 || value >= size || !array[value]) return true;
	array[value] = false;
	return TreeWalk(node->p1, array, size) || TreeWalk(node->p2, array, size);
}

// обход дерева и сверка значений с массивом
//! \param array массив для сверки
//! \param size  размер массива
bool RBtree_rating::TreeWalk(bool* array, int size)
{
	if (TreeWalk(tree_root, array, size)) return true;
	for (int n = 0; n < size; n++) if (array[n]) return true;
	return false;
}


//================================================================

#define SIZE 1000	//!< размер массива провеки

int main()
{
	int n, i;

	Hash_table test;
	test.insert({ "anton", 1, 1 });
	test.insert({ "artem", 2, 1 });
	test.insert({ "ivan", 2, 2 });
	test.insert({ "ilja", 3, 2 });
	test.insert({ "kirill", 3, 3 });
	test.insert({ "mifodij", 4, 3 });
	test.insert({ "evpidokl", 5, 3 });
	test.insert({ "seva", 4, 4 });
	test.insert({ "egor", 5, 5 });
	test.insert({ "johan", 5, 5 });
	test.insert({ "vadim", 1, 6 });
	test.insert({ "farid", 1, 7 });
	test.insert({ "farid", 2, 10 });
	test.insert({ "farid", 3, 11 });
	test.insert({ "schamil", 2, 8 });
	test.insert({ "evgenij", 2, 9 });
	test.insert({ "aleksei", 2, 10 });
	test.insert({ "abdul", 6, 0 });
	test.insert({ "hazbula", 6, 0.1 });
	test.insert({ "hazbula", 1, 55 });
	test.insert({ "abdurozik", 6, 0.2 });

	for (i = 1; i <= 6; i++)
	{
		for (auto j : test[i])
		{
			cout << "Name:" << " " << j.name << "| Group Number:" << " " << j.group << "| Rating:" << " " << j.rating << endl;
		}
	}

	cout << endl;

	string a = "Vishnevskij";
	string b = "Prohorov";
	string c = "Dolgov";
	string d = "Tishin";
	string e = "Agapov";
	string f = "Tomsov";
	string g = "Afanasiev";

	

	RBtree_rating tree_rating;

	for (i = 1; i <= 6; i++)
	{
		for (auto j : test[i])
		{
			tree_rating.Insert(j);
		}
	}

	tree_rating.Show();

	cout << endl;

	RBtree_name tree_name;

	for (i = 1; i <= 6; i++)
	{
		for (auto j : test[i])
		{
			tree_name.Insert(j);
		}
	}

	tree_name.Show();

	return 0;


}
