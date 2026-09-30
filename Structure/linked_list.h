#pragma once

#include "node.h"

template <typename t>
class linked_list {
private:
    node<t>* head;
    node<t>* tail;
    int size;

public:
    linked_list();
    ~linked_list();

    bool empty() const;
    int get_size() const;

    node<t>* get_head() const;
    node<t>* get_tail() const;

    void push_front(t data);
    void push_back(t data);

    void pop_front();
    void pop_back();

    void insert(int position, t data);
    void remove(int position);

    void clear();
};

#include "linked_list.cpp"