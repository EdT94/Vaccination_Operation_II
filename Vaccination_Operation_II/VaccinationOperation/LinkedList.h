#ifndef VACOP_LINKEDLIST_H
#define VACOP_LINKEDLIST_H
#include <iostream>

template <class T>
class LinkedList        // used as array of appointments for vaccinee
{
    struct Node
    {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    LinkedList(const LinkedList<T>& linkedList) = delete;


    const LinkedList& operator=(LinkedList const& linkedList)
    {
        Node* nodeTo = this->head;
        Node* nodeFrom = linkedList->head;
        while (nodeFrom != nullptr)
        {
            nodeTo->data = nodeFrom->data;
            nodeTo = nodeTo->next;
            nodeFrom = nodeFrom->next;
        }
    }

    ~LinkedList();

    void insert(T);

    template <class T>
    Node* search(T value)
    {
        Node* node = this->head;
        while (node != nullptr)
        {
            if ((void*)node->data == (void*)value)
                return node;
            node = node->next;
        }

        return nullptr;
    }


    void display(std::ostream& out = std::cout) const
    {
        Node* node = this->head;
        while (node != nullptr)
        {
            out << *node->data << " ";
            node = node->next;
        }
    }

    bool deleteNode(T);

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<U>& linkedList);

private:
   

};

template <class U>
std::ostream& operator<<(std::ostream& os, const LinkedList<U>& linkedList)
{
    linkedList.display(os);
    return os;
}

template <class T>
void LinkedList<T>::insert(T data)
{
    Node* t = new Node(data);
    Node* tmp = this->head;
    if (tmp == nullptr)
    {
        this->head = t;
    }
    else
    {
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = t;
    }
}

template <class T>
bool LinkedList<T>::deleteNode(T data)
{
    Node* node = search(data);
    if (node == nullptr)
        return false;

    Node* tmp = this->head;

    if (tmp == node)
    {
        this->head = tmp->next;
        delete node;
        return true;
    }
    else
    {
        while (tmp->next != nullptr)
        {
            if (tmp->next == node)
            {
                tmp->next = node->next;
                delete node;
                return true;
            }
            tmp = tmp->next;
        }
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node* tmp = nullptr;
    while (this->head)
    {
        tmp = head;
        this->head = this->head->next;
        delete tmp;
    }
    this->head = nullptr;
}




#endif //VACOP_LINKEDLIST_H