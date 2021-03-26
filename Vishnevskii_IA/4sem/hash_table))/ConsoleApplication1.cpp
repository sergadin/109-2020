// Copyright 2020 <Derezzed>

#ifndef INCLUDE_HASH_TABLE_HPP_
#define INCLUDE_HASH_TABLE_HPP_

#include<iostream>
#include<string>
#include <list>
#include <utility>
#include <vector>

struct Student {
    std::string name;
    int group;
    // double rating;
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

int main() {
    Hash_table test;
    test.insert({ "anton", 1 });
    test.insert({ "ivan", 2 });
    test.insert({ "kirill", 3 });
    test.insert({ "seva", 4 });
    test.insert({ "egor", 5 });
    test.insert({ "vadim", 1 });
    test.insert({ "farid", 1 });
    test.insert({ "schamil", 2 });
    test.insert({ "schamil", 2 });
    test.insert({ "schamil", 2 });

    for (auto i : test[2]) {
        std::cout << i.name << std::endl;
    }
    return 0;
}

#endif  // INCLUDE_HASH_TABLE_HPP_