#pragma once

#include <cstdio>
#include <iostream>
#include <utility>
#include <fstream>

class MyList {
public:
    MyList();
    ~MyList();

    struct Node;
private:
    struct Node* a;
public:

    void push(std::pair<std::string, size_t> new_data);
    void printList();
    void printListInFile(std::ofstream &out);

    struct Node* getTail(struct Node* cur);

    struct Node* partition(struct Node* head,
        struct Node* end,
        struct Node** newHead,
        struct Node** newEnd);

    struct Node* partition_by_first(struct Node* head,
        struct Node* end,
        struct Node** newHead,
        struct Node** newEnd);

    struct Node* quickSortRecur(struct Node* head, struct Node* end);

    struct Node* quickSortRecur_by_first(struct Node* head, struct Node* end);

    void quickSort();

    void quickSort_by_first();

    void removeDuplicates();

};

