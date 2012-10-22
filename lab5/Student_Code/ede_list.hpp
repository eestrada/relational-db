#ifndef _EDELIST_HPP_
#define _EDELIST_HPP_

namespace ede
{

template <class T >
class list 
{
private:
    struct llnode
    {
        T data;
        llnode *prev, *next;

        llnode(): data(T()), prev(NULL), next(NULL){};
        llnode(T value, llnode *prevnode, llnode *nextnode):
            data(value), prev(prevnode), next(nextnode){};
        friend class list<T>;
    };

    llnode *head, *tail;
    int nodecount;


public:

    // Constructors
    explicit list<T>(): head(NULL), tail(NULL), nodecount(0){};

    ~list<T>()
    {
        this->erase();
    };

    void erase()
    {
        while (head != NULL)
        {
          llnode* current = head;
          head = head->next;
          delete current;
        }
        tail = NULL;
        nodecount = 0;

    }

    virtual void push_front(T newval)
    {
        head = new llnode(newval, NULL, head);
        if (head->next != NULL) head->next->prev = head;
        if (tail == NULL)
             tail = head;
        ++nodecount; 
    };

    virtual void push_back(T newval)
    {
        if (tail != NULL)
        {
            tail->next = new llnode(newval, tail, NULL);
            tail = tail->next;
            ++nodecount;
        }
        else// List was empty.
        {
            push_front(newval);
        }
    };

    virtual bool pop_front()
    {
        if (head == NULL)
        {
            return false;
        }
        else
        {
            llnode* removed_node = head;
            head = head->next;
            delete removed_node;
            if (head != NULL)
            {
                head->prev = NULL;
            }
            else
            {
                tail = NULL;
            }
            --nodecount;

            return true;
        }
    };

    virtual bool pop_back()
    {
        if (tail == NULL)
        {
            return false;
        }
        else
        {
            llnode* removed_node = tail;
            tail = tail->prev;
            delete removed_node;
            if (tail != NULL)
            {
                tail->next = NULL;
            }
            else
            {
                head = NULL;
            }
            --nodecount;

            return true;
        }
    };

    virtual T front()
    {
        return head->data;
    };

    virtual T back()
    {
        return tail->data;
    };

    virtual int size()
    {
        return nodecount;
    };

    virtual bool empty()
    {
        return (nodecount == 0) ? true : false;
    };
};

};

#endif // define _EDELIST_HPP_

