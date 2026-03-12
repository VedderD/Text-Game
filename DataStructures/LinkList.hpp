#pragma once

template<class T>
struct Link {
    T data;
    Link* next = nullptr;
};

template<class T>
class LinkList {
public:
    void Insert(size_t _targetIndex, T _value) {
        Link<T>* link = new Link<T>();
        link->data = _value;

        Link<T>** current = &m_head;
        for (size_t i = 0; *current && i < _targetIndex; i++, current = &((*current)->next)) {}

        link->next = *current;
        *current = link;
    }

    int CountFor() {
        Link<T>* current = m_head;
        int count = 0;
        for (; current; count++)
            current = current->next;
        return count;
    }

    int Count() {
        Link<T>* current = m_head;
        int count = 0;

        while (current) {
            count++;
            current = current->next;
            //current = (*current).next;
        }

        return count;
    }

    Link<T>* GetLinkAt(size_t _targetIndex) {
        Link<T>* current = m_head; 
        for (size_t i = 0;  current && i <= _targetIndex; i++, current = current->next)
            if (i == _targetIndex)
                return current;

        return nullptr;
    }
private:
    Link<T>* m_head;
};