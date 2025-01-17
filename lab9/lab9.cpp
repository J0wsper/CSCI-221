#include <iostream>
#include <string>
#include "lab9.hpp"

//Constructor
node::node(std::string s) {
    this->value = s;
    this->length = 0;
    while (s[this->length] != '\0') {
        this->length++;
    }
    this->next = nullptr;
}

//Getters
node* node::get_next() const {
    return next;
} 

int node::get_length() const {
    return length;
}

std::string node::get_value() const {
    return value;
}

//Setters.
void node::set_length(int len) {
    length = len;
    return;
}

void node::set_next(node* next_node) {
    next = next_node;
    return;
}

void node::set_value(std::string val) {
    this->value = val;
}





//Linked list stuff below




LL::LL() {
    this->root = nullptr;
    this->length = 0;
    this->sorting = "length";
}

LL::LL(const LL& linked_list) {
    this->root = linked_list.get_root();
    this->length = linked_list.get_length();
}

LL::~LL() {
    node* curr = this->root;
    for (int i = 0; i < this->length; i++) {
        node* prev = curr;
        curr = curr->get_next();
        delete prev;
    }
    delete curr;
}

node* LL::get_root() const {
    return this->root;
}

int LL::get_length() const {
    return this->length;
}

std::string LL::get_sorting() const {
    return this->sorting;
}

void LL::add(std::string s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    //Something goes wrong here?
    node* new_node = new node(s);
    if (this->length == 0) {
        this->root = new_node;
        this->length++;
        return;
    }
    node* curr = this->root;
    node* prev = nullptr;
    while (curr != nullptr) {
        if (curr->get_length() >= len && this->sorting == "length") {

            //Root case.
            if (prev == nullptr) {
                this->root = new_node;
                new_node->set_next(curr);
                this->length++;
                return;
            }

            //Non-root case.
            else if (prev->get_length() <= len) {
                prev->set_next(new_node);
                new_node->set_next(curr);
                this->length++;
                return;
            }
        }
        else if (curr->get_value() >= s && this->sorting == "value") {
            
            //Root case.
            if (prev == nullptr) {
                this->root = new_node;
                new_node->set_next(curr);
                this->length++;
                return;
            }

            //Non-root case.
            else if (prev->get_value() <= s) {
                prev->set_next(new_node);
                new_node->set_next(curr);
                this->length++;
                return;
            }
        }
        prev = curr;
        curr = curr->get_next();
    }

    //End case.
    prev->set_next(new_node);
    this->length++;
    return;
}

void LL::remove(std::string s) {
    node* curr = this->root;
    node* prev = nullptr;
    std::string val = curr->get_value();

    //Root case
    if (val == s) {
        this->root = curr->get_next();
        this->length--;
        delete curr;
        return;
    }

    //Non-root case
    while (curr != nullptr) {
        val = curr->get_value();
        if (val == s) {
            prev->set_next(curr->get_next());
            this->length--;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->get_next();
    }
}

node* LL::insert_by_value(node* head, std::string value) {
    if (head == nullptr) {
        node* newnode = new node(value);
        newnode->set_next(nullptr);
        return newnode;
    }
    if (value < head->get_value()) {
        node* newnode = new node(value);
        newnode->set_next(head);
        return newnode;
    }
    node* newnode = insert_by_value(head->get_next(), value);
    head->set_next(newnode);
    return head;
}

node* LL::insert_by_length(node* head, std::string value) {
    int len = 0;
    while (value[len] != '\0') {
        len++;
    }
    if (head == nullptr) {
        node* newnode = new node(value);
        newnode->set_next(nullptr);
        return newnode;
    }
    if (len < head->get_length()) {
        node* newnode = new node(value);
        newnode->set_next(head);
        return newnode;
    }
    node* newnode = insert_by_length(head->get_next(), value);
    head->set_next(newnode);
    return head;
}

void LL::sort_by_length(node* unsorted) {
    if (unsorted == nullptr) {
        unsorted = this->root;
    }
    this->sorting = "length";
    node* new_head = nullptr;
    while (unsorted != nullptr) {
        new_head = insert_by_length(new_head, unsorted->get_value());
        unsorted = unsorted->get_next();
    }
    node* curr = this->root;
    node* prev = nullptr;
    while (curr != nullptr) {
        prev = curr;
        curr = curr->get_next();
        delete prev;
    }
    this->root = new_head;
}

void LL::sort_by_value(node* unsorted) {
    if (unsorted == nullptr) {
        unsorted = this->root;
    }
    this->sorting = "value";
    node* new_head = nullptr;
    while (unsorted != nullptr) {
        new_head = insert_by_value(new_head, unsorted->get_value());
        unsorted = unsorted->get_next();
    }
    node* curr = this->root;
    node* prev = nullptr;
    while (curr != nullptr) {
        prev = curr;
        curr = curr->get_next();
        delete prev;
    }
    delete curr;
    this->root = new_head;
}

//The operator is broken and I don't know how to fix it. Don't use it.
std::string& LL::operator[](unsigned i) const {
    if (i >= this->length) {
        std::string* s = new std::string;
        *s = "";
        return *s;
    }
    node* curr = this->root;
    unsigned index = 0;
    while (index < i) {
        curr = curr->get_next();
    }
    std::string* val = new std::string;
    *val = curr->get_value();
    return *val;
}