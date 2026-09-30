#include "linked_list.h"

template <typename t>
linked_list<t>::linked_list() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename t>
linked_list<t>::~linked_list() {
    clear();
}

template <typename t>
bool linked_list<t>::empty() const {
    return head == nullptr;
}

template <typename t>
int linked_list<t>::get_size() const {
    return size;
}

template <typename t>
node<t>* linked_list<t>::get_head() const {
    return head;
}

template <typename t>
node<t>* linked_list<t>::get_tail() const {
    return tail;
}

template <typename t>
void linked_list<t>::push_front(t data) {
    node<t>* new_node = new node<t>(data);

    if (empty()) {
        head = new_node;
        tail = new_node;
    }
    else {
        new_node->set_next(head);
        head->set_prev(new_node);
        head = new_node;
    }

    size++;
}

template <typename t>
void linked_list<t>::push_back(t data) {
    node<t>* new_node = new node<t>(data);

    if (empty()) {
        head = new_node;
        tail = new_node;
    }
    else {
        new_node->set_prev(tail);
        tail->set_next(new_node);
        tail = new_node;
    }

    size++;
}

template <typename t>
void linked_list<t>::pop_front() {
    if (empty())
        return;

    node<t>* temp = head;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        head = head->get_next();
        head->set_prev(nullptr);
    }

    delete temp;
    size--;
}

template <typename t>
void linked_list<t>::pop_back() {
    if (empty())
        return;

    node<t>* temp = tail;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        tail = tail->get_prev();
        tail->set_next(nullptr);
    }

    delete temp;
    size--;
}

template <typename t>
void linked_list<t>::insert(int position, t data) {
    if (position < 0 || position > size)
        return;

    if (position == 0) {
        push_front(data);
        return;
    }

    if (position == size) {
        push_back(data);
        return;
    }

    node<t>* current = head;

    for (int i = 0; i < position; i++)
        current = current->get_next();

    node<t>* new_node = new node<t>(data);

    new_node->set_prev(current->get_prev());
    new_node->set_next(current);

    current->get_prev()->set_next(new_node);
    current->set_prev(new_node);

    size++;
}

template <typename t>
void linked_list<t>::remove(int position) {
    if (position < 0 || position >= size)
        return;

    if (position == 0) {
        pop_front();
        return;
    }

    if (position == size - 1) {
        pop_back();
        return;
    }

    node<t>* current = head;

    for (int i = 0; i < position; i++)
        current = current->get_next();

    current->get_prev()->set_next(current->get_next());
    current->get_next()->set_prev(current->get_prev());

    delete current;
    size--;
}

template <typename t>
void linked_list<t>::clear() {
    while (!empty())
        pop_front();
}