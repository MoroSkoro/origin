#include "MyList.h"

MyList::MyList(){ this-> a = NULL; };
MyList::~MyList(){ };
struct MyList::Node
{
    std::pair<std::string, size_t> data;
    struct Node* next;
};


    void MyList::push(std::pair<std::string, size_t> new_data)
    {
        struct Node* new_node = new Node;
        new_node->data.first = new_data.first;
        new_node->data.second = new_data.second;
        new_node->next = (this->a);
        (this->a) = new_node;
    }

    void MyList::printList()
    {
        struct Node* pp = new Node;
        pp = this->a;
        while (pp != NULL)
        {
            std::cout << (pp)->data.first << " - " << (pp)->data.second << std::endl;
            pp = (pp)->next;
        }
    }

    void MyList::printListInFile(std::ofstream &out)
    {
        struct Node* pp = new Node;
        pp = this->a;
        while (pp != NULL)
        {
            out << pp->data.first << " - " << pp->data.second << std::endl;
            pp = pp->next;
        }
    }
    struct MyList::Node* MyList::getTail(struct Node* cur)
    {
        while (cur != NULL &&
            cur->next != NULL)
            cur = cur->next;
        return cur;
    }

    struct MyList::Node* MyList::partition(struct Node* head,
        struct Node* end,
        struct Node** newHead,
        struct Node** newEnd)
    {
        struct Node* pivot = end;
        struct Node* prev = NULL,
            * cur = head, * tail = pivot;
        while (cur != pivot)
        {
            if (cur->data.second < pivot->data.second)
            {
                if ((*newHead) == NULL)
                    (*newHead) = cur;
                prev = cur;
                cur = cur->next;
            }
            else
            {
                if (prev)
                    prev->next = cur->next;
                struct Node* tmp = cur->next;
                cur->next = NULL;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            }
        }
        if ((*newHead) == NULL)
            (*newHead) = pivot;
        (*newEnd) = tail;
        return pivot;
    }

    struct MyList::Node* MyList::partition_by_first(struct Node* head,
        struct Node* end,
        struct Node** newHead,
        struct Node** newEnd)
    {
        struct Node* pivot = end;
        struct Node* prev = NULL,
            * cur = head, * tail = pivot;
        while (cur != pivot)
        {
            if ((cur->data.first < pivot->data.first) && (cur->data.second == pivot->data.second))
            {
                if ((*newHead) == NULL)
                    (*newHead) = cur;

                prev = cur;
                cur = cur->next;
            }
            else
            {
                if (prev)
                    prev->next = cur->next;
                struct Node* tmp = cur->next;
                cur->next = NULL;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            }
        }
        if ((*newHead) == NULL)
            (*newHead) = pivot;
        (*newEnd) = tail;
        return pivot;
    }

    struct MyList::Node* MyList::quickSortRecur(struct Node* head, struct Node* end)
    {
        if (!head || head == end)
            return head;
        Node* newHead = NULL, * newEnd = NULL;
        struct Node* pivot = partition(head, end,
            &newHead, &newEnd);
        if (newHead != pivot)
        {
            struct Node* tmp = newHead;
            while (tmp->next != pivot)
                tmp = tmp->next;
            tmp->next = NULL;
            newHead = quickSortRecur(newHead, tmp);
            tmp = getTail(newHead);
            tmp->next = pivot;
        }
        pivot->next = quickSortRecur(pivot->next,
            newEnd);
        return newHead;
    }

    struct MyList::Node* MyList::quickSortRecur_by_first(struct Node* head, struct Node* end)
    {
        if (!head || head == end)
            return head;
        Node* newHead = NULL, * newEnd = NULL;
        struct Node* pivot = partition_by_first(head, end,
            &newHead, &newEnd);
        if (newHead != pivot)
        {
            struct Node* tmp = newHead;
            while (tmp->next != pivot)
                tmp = tmp->next;
            tmp->next = NULL;
            newHead = quickSortRecur_by_first(newHead, tmp);
            tmp = getTail(newHead);
            tmp->next = pivot;
        }
        pivot->next = quickSortRecur_by_first(pivot->next,
            newEnd);
        return newHead;
    }

    void MyList::quickSort()
    {
        (this->a) = quickSortRecur(this->a, getTail(this->a));
        return;
    }

    void MyList::quickSort_by_first()
    {
        (this->a) = quickSortRecur_by_first(this->a,   getTail(this->a));
        return;
    }

    void MyList::removeDuplicates()
    {
        struct Node* ptr1, * ptr2, * dup;
        ptr1 = this->a;
        while (ptr1 != NULL &&
            ptr1->next != NULL)
        {
            ptr2 = ptr1;
            while (ptr2->next != NULL)
            {
                if (ptr1->data.first == ptr2->next->data.first)
                {
                    dup = ptr2->next;
                    ptr2->next = ptr2->next->next;
                    delete (dup);
                    ptr1->data.second++;
                }
                else
                    ptr2 = ptr2->next;
            }
            ptr1 = ptr1->next;
        }
    }


