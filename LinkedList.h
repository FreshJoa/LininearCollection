#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <assert.h>

namespace aisdi
{

template <typename Type>
class LinkedList
{
public:
    friend class ConstIterator;
   // friend class Iterator;
    using difference_type = std::ptrdiff_t;//type to represent the difference between two iterators.
    using size_type = std::size_t;
    using value_type = Type;
    using pointer = Type*;
    using reference = Type&;
    using const_pointer = const Type*;
    using const_reference = const Type&;
    class ConstIterator;
    class Iterator;
    class Node;
    using iterator = Iterator;
    using const_iterator = ConstIterator;


    Node *head;
    Node *tail;
    Node *last;
    size_type size=0;




    LinkedList()
    {
        size=0;
        head=nullptr;
        tail=nullptr;
        //last= new Node;

    }
    LinkedList(std::initializer_list<Type> l)
    {
        head=nullptr;
        tail=nullptr;
        size=0;

        if(l.size()>0)
        {
            for(auto const& item:l)
            {
                append(item);
            }
            size=l.size();
        }
    }


    LinkedList(const LinkedList& other)
    {
        if ( other.head == nullptr )
        {
            head = nullptr;
            tail = nullptr;
          //  last=other.last;
            size = 0;
        }
        else
        {
            Node *target = other.head;
            while ( target != other.last )
            {
                append ( target->data );
                target = target->next;
            }
        }

    }

    LinkedList(LinkedList&& other)//  sematyka przeniesienia czyli przenosi listę na miejsce nowej a starą zostawia pustą
    {


        head = other.head;
        tail = other.tail;
       // last=other.last;
        size = other.size;


        other.head=nullptr;
        other.tail=nullptr;
       // other.last=nullptr;
        other.size=0;
    }



    ~LinkedList()
    {
        while(!this->isEmpty())
        {
            popLast();
        }
    }

    bool operator==(const LinkedList& other)const
    {
        if(this->size==other.size)
        {
            Node *tmp=new Node;
            Node *tmp_other=new Node;
            tmp=head;
            tmp_other=other.head;
            while(tmp==tmp_other && tmp->next != this->last && tmp_other->next != other->last)
            {
                tmp=tmp->next;
                tmp_other=tmp_other->next;
            }
            return true;

        }
        else
        {
            return false;
        }

        // return (this->head==other.head && this->size==other.size && this->tail==other.tail);

    }

    LinkedList& operator=(const LinkedList& other)
    {

        if(&other == this)
        {
            return *this;
        }
        if ( other.head == nullptr )
        {
            head = nullptr;
            tail = nullptr;
           // last=other.last;
            size = 0;
        }
        else
        {
             //last=other.last;

            Node *target = other.head;
            while ( target != other.last )
            {
                append ( target->data );
                target = target->next;
            }

        }


        return *this;

    }

    LinkedList& operator=(LinkedList&& other)
    {
        if(&other == this)
        {
            return *this;
        }
        head = other.head;
        tail = other.tail;
       // last=other.last;
        size = other.size;

        other.head=nullptr;
        other.tail=nullptr;
       // other.last=nullptr;
        other.size=0;

        return *this;

    }

    bool isEmpty() const
    {
        return size == 0 ;
    }

    size_type getSize() const
    {
        return size;
    }

    void append(const Type& item)
    {
        Node *new_ptr  = new Node;
        new_ptr->data  = item;
        if ( size == 0 )
        {
            new_ptr->next=last;
            new_ptr->prev=nullptr;
            head= new_ptr;
            tail=new_ptr;
        }
        else
        {
            new_ptr->prev=tail;
            tail->next=new_ptr;
            new_ptr->next=last;
            tail=new_ptr;
        }
        size++;


    }

    void prepend(const Type& item)
    {
        Node *new_ptr  = new Node;
        new_ptr->data  = item;
        if ( size == 0 )
        {

            new_ptr->next=last;
            new_ptr->prev=nullptr;
            head= new_ptr;
            tail=new_ptr;
        }
        else
        {
            new_ptr->next=head;
            head->prev=new_ptr;
            new_ptr->prev=nullptr;
            head=new_ptr;
        }
        size++;

    }

    void insert(const const_iterator& insertPosition, const Type& item)
    {
        if(head==insertPosition.cptr)
        {
            prepend(item);

//            Node *newhead=new Node;
//            newhead->data=item;
//            head->prev=newhead;
//            newhead->next=head;
//            newhead->prev=nullptr;
//            head=newhead;

        }

        //else if(tail==insertPosition.cptr)
        else if(last==insertPosition.cptr)
        {
            append(item);
//            Node *newtail=new Node;
//            newtail->data=item;
//            tail->next=newtail;
//            newtail->prev=tail;
//            newtail->next=nullptr;
//            tail=newtail;

        }
        else
        {
            Node *tmp = head;
            while(tmp!=insertPosition.cptr->prev)
            {
                tmp=tmp->next;
            }
            Node *new_node=new Node;
            new_node->data=item;
            tmp->next->prev=new_node;
            new_node->next=tmp->next;
            tmp->next=new_node;
            new_node->prev=tmp;

        }

        size++;

    }

    Type popFirst()
    {

        if(isEmpty())
        {
            throw std::runtime_error("");
        }
        Type tmp_data = head->data;

        if(size==1)
        {
            Node *tmp=head;
            tail=nullptr;
            head=nullptr;
            size=0;
            delete tmp;
            tmp = nullptr;
        }
        else
        {
            Node *tmp=head;
            head=tmp->next;
            head->prev=nullptr;
            size--;
            delete tmp;
            tmp = nullptr;

        }
        return tmp_data;
    }

    Type popLast()
    {

        if ( isEmpty() )
        {
            throw std::runtime_error("");
        }

        Type tmp_data = tail->data;

        if ( size == 1 )
        {
            Node *tmp=head;
            head=nullptr;
            tail=nullptr;
            delete tmp;
            tmp = nullptr;
            size=0;
        }

        if ( size > 1 )
        {
            Node *tmp=tail;
            tail = tmp->prev;
            tail->next=last;
            size--;
            delete tmp;
            tmp = nullptr;
        }
        return tmp_data;
    }

    void erase(const const_iterator& possition)
    {
        if ( isEmpty() )
        {
            throw std::runtime_error("");
        }
        if(last == possition.cptr   )
        {
            throw std::out_of_range("");
        }
        Node *tmp;


        if(size==1 && head==possition.cptr )// czy jeszcze trzeba tail==possition.cptr?
        {
            tmp=head;
            head=nullptr;
            tail=nullptr;
            size=0;
            delete tmp;

        }
        if(head==possition.cptr)
        {
            tmp=head;
            head=head->next;
            head->prev=nullptr;
            delete tmp;
            size--;

        }
        else if(tail==possition.cptr)
        {
            tmp=tail;
            tail=tail->prev;
            tail->next=last;
            delete tmp;
            size--;

        }
        else
        {
            tmp=head;
            while(tmp!=possition.cptr )
            {
                if(tmp==last )
                {
                    throw std::out_of_range("");

                }
                tmp=tmp->next;
            }

            tmp->next->prev=tmp->prev;
            tmp->prev->next=tmp->next;
            delete tmp;
            size--;
        }
    }

    void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
    {


        if(firstIncluded==lastExcluded)
        {

            return;
        }
        else
        {
            Node *tmp;
            tmp=head;
            while(tmp!=firstIncluded.cptr )
            {
                if( tmp==last)
                {
                    throw std::out_of_range("");

                }
                tmp=tmp->next;
            }

            while(tmp!=lastExcluded.cptr)
            {
                if(tmp==last)
                {
                    throw std::runtime_error("");
                }
                Node *old=tmp;
                tmp->next->prev=tmp->prev;
                tmp->prev->next=tmp->next;

                tmp=tmp->next;
                delete old;
                size--;
            }
        }

    }

    iterator begin()
    {
        iterator it=iterator(head, this);
        return it;
    }

    iterator end()
    {
        if(isEmpty())
        {
            return iterator(tail, this);
        }

        return iterator(last, this);

    }

    const_iterator cbegin() const
    {

        return const_iterator(head, this);
    }

    const_iterator cend() const
    {
        if(isEmpty())
        {
            return iterator(tail, this);
        }

        return iterator(last, this);
    }

    const_iterator begin() const
    {
        return cbegin();
    }

    const_iterator end() const
    {
        return cend();
    }
};
template <typename Type>
class LinkedList<Type>::Node
{
public:

    Node *next;
    Node *prev;
    Type data;
    Node()
    {
        next=nullptr;
        prev=nullptr;
    }
    Node( Type& item, Node* next_ptr= NULL, Node* prev_ptr = NULL) :data(item), next(next_ptr),prev(prev_ptr) {}

    bool operator==(const Node& other)const
    {
        //return (this->data==other.data && this->next=other.next && this->prev==other.prev);
        // return *this==other;
        return this == &other;
    }

};

template <typename Type>
class LinkedList<Type>::ConstIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;//Pusta klasa identyfikująca kategorię iteratora jako iteratora dwukierunkowego :

    using value_type = typename LinkedList::value_type;// is an alias of the first class template parameter (T).
    using difference_type = typename LinkedList::difference_type;// a signed integer type that can be used to identify distance between iterators
    using pointer = typename LinkedList::const_pointer;
    using reference = typename LinkedList::const_reference;
    using node=typename LinkedList::Node;


    //class Node;
    const node *cptr;
    const LinkedList *linked_list;
    explicit ConstIterator()
    {
        cptr=nullptr;
    }
    ConstIterator(node *new_ptr, const LinkedList *list_)
    {
        cptr=new_ptr;
        linked_list=list_;
    }

    ConstIterator& operator=(const ConstIterator& other)
    {
        if(&other == this)
        {
            return *this;
        }

        cptr=other.cptr;
        linked_list=other.linked_list;
        return *this;
    }



    reference operator*() const //Dopytaj
    {
        if(cptr == nullptr || cptr==linked_list->last )
        {
            throw std::out_of_range("");
        }
        return cptr->data;
    }

    ConstIterator& operator++()
    {
        if( linked_list->isEmpty())
        {
            throw std::out_of_range("");
        }

        if( *this == linked_list->end() )
        {
            throw std::out_of_range("");
        }
//        if( cptr == nullptr )//cptr==linked_list->begin() || cptr==linked_list->tail
//        {
//            throw std::out_of_range("");
//        }

        cptr = cptr->next;
        return *this;
    }

    ConstIterator operator++(int)
    {
        if( linked_list->isEmpty() )
        {
            throw std::out_of_range("");
        }
        if( *this == linked_list->end()   )
        {
            throw std::out_of_range("");
        }


        ConstIterator tmp(*this);
        cptr = cptr->next;

        return tmp;


    }



    ConstIterator& operator--()
    {
        if( linked_list->isEmpty())
        {
            throw std::out_of_range("");;
        }


        if( *this == linked_list->begin() )
        {
            throw std::out_of_range("");
        }

        if( *this == linked_list->end() && !linked_list->isEmpty())
        {
            cptr = linked_list->tail;
            return *this;
        }



        cptr = cptr->prev;
        return *this;

    }

    ConstIterator operator--(int)
    {
        if( linked_list->isEmpty())
        {
            throw std::out_of_range("");;
        }
        if( *this == linked_list->begin() )
        {
            throw std::out_of_range("");
        }


        ConstIterator tmp(*this);
        if( *this == linked_list->end() && !linked_list->isEmpty())
        {
            cptr = linked_list->tail;
            return tmp;
        }


//        if(cptr == nullptr  )
//        {
//            throw std::out_of_range("");
//        }
        cptr = cptr->prev;
        return tmp;

    }

    ConstIterator operator+(difference_type d) const//??
    {
//
        if( linked_list->isEmpty())
        {
            throw std::out_of_range("");
        }
        ConstIterator tmp(*this);
        for(auto i=0; i<d; i++)
        {
            if( *this == linked_list->end())
            {
                throw std::out_of_range("");
            }

            tmp.cptr++;

        }

        return *this;



    }

    ConstIterator operator-(difference_type d) const
    {

        if( linked_list->isEmpty())
        {
            throw std::runtime_error("");
        }

        ConstIterator tmp(*this);
        for(auto i=0; i<d; i++)
        {
            if( tmp == linked_list->end())
            {
                tmp.cptr = linked_list->tail;

            }
            if(tmp == linked_list->begin() )
            {
                throw std::out_of_range("");
            }
            else
            {
                tmp.cptr--;
            }

        }

        return tmp;
    }

    bool operator==(const ConstIterator& other) const
    {
        //return &other==this;
        return cptr==other.cptr && linked_list== other.linked_list;
    }

    bool operator!=(const ConstIterator& other) const
    {
        return cptr!=other.cptr && linked_list == other.linked_list;
    }
};

template <typename Type>
class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
{
public:
    using pointer = typename LinkedList::pointer;
    using reference = typename LinkedList::reference;
    //class Node;

    //Node *ptr;

    explicit Iterator()
    {

    }


    Iterator(Node *new_ptr, const LinkedList *list_) : ConstIterator(new_ptr, list_) {}



    Iterator(const ConstIterator& other): ConstIterator(other) {}

    Iterator& operator=(const ConstIterator& other)
    {
        ConstIterator::operator=( other);
        return *this;
    }

    Iterator& operator++()
    {
        ConstIterator::operator++();
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator result(*this);
        ConstIterator::operator++();
        return result;
    }
    Iterator& operator--()
    {
        ConstIterator::operator--();
        return *this;
    }

    Iterator operator--(int)
    {
        auto result = *this;
        ConstIterator::operator--();
        return result;
    }

    Iterator operator+(difference_type d) const
    {
        return ConstIterator::operator+(d);
    }

    Iterator operator-(difference_type d) const
    {
        return ConstIterator::operator-(d);
    }

    reference operator*() const
    {
        // ugly cast, yet reduces code duplication.
        return const_cast<reference>(ConstIterator::operator*());
    }
};

}

#endif // AISDI_LINEAR_LINKEDLIST_H

