#ifndef _LAB9_HPP_
#define _LAB9_HPP_

class node {

private:
    std::string value;
    unsigned length;
    struct node* next;

public:
    node(std::string);
    node* get_next() const;
    int get_length() const;
    std::string get_value() const;
    void set_next(node*);
    void set_length(int);
    void set_value(std::string);
};

class LL {

private:
    node* root;
    int length;
    std::string sorting;

public:
    LL();
    LL(const LL&);
    ~LL();
    node* get_root() const;
    int get_length() const;
    std::string get_sorting() const;
    void add(std::string);
    void remove(std::string);
    node* insert_by_value(node*, std::string);
    node* insert_by_length(node*, std::string);
    void sort_by_length(node* unsorted = nullptr);
    void sort_by_value(node* unsorted = nullptr);

    //Warning: this doesn't work and I don't know how to fix it. I don't know why, but it seems to be returning a type of LL.
    std::string& operator[](unsigned) const;
};

#endif