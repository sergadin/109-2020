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
		//std::cout << "\"~slot()\" occured\n";
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
		//std::cout << "\"~node()\" occured\n";
		if (cur_ != 0)
			delete[] cur_;
		cur_ = 0;
		n_ = 0;
		prev_node_ = 0;
		if (next_node_ != 0)
			delete[] next_node_;
		next_node_ = 0;
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
	int delete_B_tree(node <T> *cur_node)
	{
		if (cur_node->next_node_ != 0)
			for (int i = 0; i <= cur_node->n_; i++)
				delete_B_tree(cur_node->next_node_[i]);
		delete cur_node;
		return 0;
	}
	
	node <T> *add_slot_in(std::string key, T val, node <T> *cur_node)
	{
		if (cur_node->n_ == 0)
		{
			cur_node->add_slot(key, val);
			return cur_node;
		}
		for (int i = 0; i <= cur_node->n_; i++)
			if ((i == cur_node->n_) || (key < cur_node->cur_[i].key_))
			{
				if (cur_node->next_node_ == 0)
				{
					cur_node->add_slot(key, val);
					return cur_node;
				}
				else
					return add_slot_in(key, val, cur_node->next_node_[i]);
			}
	}
	void debug(node <T> *cur_node)
	{
		
		if (cur_node->n_ > (2 * M))
		{
			node <T> *left, *right;
			left = cur_node;
			right = new node <T>;
			left->n_ = right->n_ = M;
			for (int i = 0; i < M; i++)
				right->cur_[i] = left->cur_[M + 1 + i];
			if (left->next_node_ != 0)
			{
				right->next_node_ = new node <T>*[2 * M + 2];
				for (int i = 0; i <= M; i++)
					right->next_node_[i] = left->next_node_[M + 1 + i];
			}
			right->prev_node_ = left->prev_node_;
			if (left->prev_node_ == 0)
			{
				left->prev_node_ = new node <T>;
				right->prev_node_ = left->prev_node_;
				left->prev_node_->n_ = 1;
				left->prev_node_->cur_[0].key_ = left->cur_[M].key_;
				left->prev_node_->cur_[0].val_ = left->cur_[M].val_;
				left->prev_node_->next_node_ = new node <T>*[2 * M + 2];
				left->prev_node_->next_node_[0] = left;
				left->prev_node_->next_node_[1] = right;
				left->prev_node_->prev_node_ = 0;
				root_ = left->prev_node_;
			}
			else
			{
				for (int i = 0; i <= (left->prev_node_->n_); i++)
					if ((i == left->prev_node_->n_) || (left->cur_[M].key_ < left->prev_node_->cur_[i].key_))
					{
						for (int j = left->prev_node_->n_ - 1; j >= i; j--)
						{
							left->prev_node_->cur_[j + 1].key_ = left->prev_node_->cur_[j].key_;
							left->prev_node_->cur_[j + 1].val_ = left->prev_node_->cur_[j].val_;
						}
						left->prev_node_->cur_[i].key_ = left->cur_[M].key_;
						left->prev_node_->cur_[i].val_ = left->cur_[M].val_;
						for (int j = left->prev_node_->n_; j >= i + 1; j--)
							left->prev_node_->next_node_[j + 1] = left->prev_node_->next_node_[j];
						left->prev_node_->next_node_[i + 1] = right;
						left->prev_node_->n_++;
						break;
					}
			}
			debug(left->prev_node_);
		}
	}
	void add_slot(std::string key, T val)
	{
		debug(add_slot_in(key, val, root_));
	}
	
	void write_in(node <T> *cur_node, int n)
	{
		for (int j = 0; j < n; j++)
			std::cout << "* ";
		std::cout << ": ";
		for (int i = 0; i < cur_node->n_; i++)
		{
			std::cout << cur_node->cur_[i].key_ << " " << cur_node->cur_[i].val_ <<"; ";
		}
		std::cout << "\n";
		if (cur_node->next_node_ != 0)
			for (int i = 0; i <= cur_node->n_; i++)
				write_in(cur_node->next_node_[i], n + 1);
	}
	void write()
	{
		write_in(root_, 1);
	}
	
	node <T> *find_node(std::string key)
	{
		node <T> *res;
		res = root_;
		while(1)
		{
			int i = 0;
			int n = res->n_;
			for ( ; i < n; i++)
			{
				if (key == res->cur_[i].key_)
					return res;
				if (key < res->cur_[i].key_)
					if (res->next_node_ == 0)
						return 0;
					else
					{
						res = res->next_node_[i];
						break;
					}
			}
			if (i >= n)
				if (res->next_node_ == 0)
					return 0;
				else
					res = res->next_node_[i];
		}
	}
};

int main(void)
{
	B_tree <int> Tr;
	Tr.add_slot("stroka1", 1);
	Tr.add_slot("stroka5", 5);
	Tr.add_slot("stroka3", 3);
	Tr.add_slot("stroka4", 4);
	Tr.add_slot("stroka2", 2);
	Tr.add_slot("stroka115", 115);
	Tr.add_slot("stroka12", 12);
	Tr.add_slot("stroka22", 22);
	Tr.add_slot("stroka9", 9);
	Tr.add_slot("stroka91", 91);
	Tr.add_slot("stroka92", 92);
	Tr.add_slot("stroka93", 93);
	Tr.add_slot("stroka94", 94);
	Tr.add_slot("stroka95", 95);
	Tr.add_slot("stroka96", 96);
	Tr.add_slot("stroka97", 97);
	Tr.add_slot("stroka98", 98);
	
	Tr.write();
	std::cout << Tr.find_node("stroka1")->cur_[0].val_;
	return 0;
}
