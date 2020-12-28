#include <iostream>
#include <string.h>
//using namespace std;

const int M = 2;

template <class T>
class slot
{
public:
	std::string key_;
	T val_;
	
	slot()
	{
		//nothing
	}
	slot(std::string key, T val)
	{
		key_ = key;
		val_ = val;
	}
	~slot()
	{
		std::cout << "\"~slot()\" occured\n";
	}
	int sth()
	{
		return 0;
	}
};

template <class T>
class node
{
public:
	slot <T> *cur_;  // array of current slots
	int n_;          // number of current slots
	node <T> **next_node_;
	node <T> *prev_node_;

	node()
	{
		cur_ = new slot<T>[2 * M + 1];
		next_node_ = 0;
		prev_node_ = 0;
		n_ = 0;
	}
	~node()
	{
		std::cout << "\"~node()\" occured\n";
		if (cur_ != 0)
			delete[] cur_;
		n_ = 0;
		prev_node_ = 0;
		if (next_node_ != 0)
			delete[] next_node_;
	}
	int add_slot(std::string key, T val)
	{
		for (int i = 0; i <= n_; i++)
			if ((i == n_) || (key < cur_[i].key_))
			{
				for (int j = n_ - 1; j >= i; j--)
				{
					cur_[j + 1].key_ = cur_[j].key_;
					cur_[j + 1].val_ = cur_[j].val_;
				}
				cur_[i].key_ = key;
				cur_[i].val_ = val;
				n_++;
				return 0;
			}
	}
	void sth()
	{
		for (int i = 0; i < n_; i++)
		std::cout << cur_[i].key_ << " " << cur_[i].val_ << "\n";
	}
};

template <class T>
class B_tree
{
private:
	node <T> *root_;
public:
	B_tree()
	{
		root_ = new node <T>;
	}
	~B_tree()
	{
		delete_B_tree(root_);
	}
	int delete_B_tree(node <T> *root)
	{
		if (root->next_node_ != 0)
		for (int i = 0; i <= root_->n_; i++)
			delete_B_tree(root->next_node_[i]);
		delete root;
		return 0;
	}
	int add_slot_in(std::string key, T val, node <T> *cur_node)
	{
		if (cur_node->n_ == 0)
		{
			cur_node->add_slot(key, val);
			return 0;
		}
		for (int i = 0; i <= cur_node->n_; i++)
			if ((i == cur_node->n_) || (key < cur_node->cur_[i]->key_))
			{
				if (cur_node->next_node_ == 0)
					cur_node->add_slot(key, val);
				else
				{
					add_slot_in(key, val, cur_node->next_node[i]);
				}
				return 0;
			}
	}
	
};

int main(void)
{
	node <int> N;
	N.add_slot("stroka1", 1);
	N.add_slot("stroka2", 2);
	N.add_slot("stroka3", 3);
	N.sth();
	
	return 0;
}
