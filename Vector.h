#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <assert.h>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <stdio.h>
#include <string.h>
#include <iterator>

namespace aisdi
{

template <typename Type>
class Vector
{
public:
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using value_type = Type;
    using pointer = Type*;
    using reference = Type&;
    using const_pointer = const Type*;
    using const_reference = const Type&;
// using const_iterator=const Type*;
//using iterator=Type*;

    class ConstIterator;
    class Iterator;
    using iterator = Iterator;
    using const_iterator = ConstIterator;

    Type *array;
    size_type arr_size=0;
    size_type size=10;


    Vector()
    {
        array=new Type[size];
        arr_size=0;

    }

    Vector(std::initializer_list<Type> l)
    {
        size=l.size()*2;
        array=new Type[size];
        for(auto &item:l)
        {
            array[arr_size++]=item;
        }

    }

    Vector(const Vector& other)
    {

        size=other.size;
        array=new Type[size];
        for(size_type i=0; i<other.arr_size; i++)
        {
            array[i]=other.array[i];
        }
        arr_size=other.arr_size;


    }

    Vector(Vector&& other)
    {
        size=other.size;
        arr_size=other.arr_size;
        array = other.array;
        other.array=nullptr;
        other.size=0;


//    array=new Type[size];
//    for(size_t i=0; i<other.arr_size; i++){
//         array[i]=std::move(other.array[i]);
//    }
//    arr_size=other.arr_size;
//    other.arr_size=0;//?
//    other.size=0;//?

    }

    ~Vector()
    {
        delete []array;

    }

    Vector& operator=(const Vector& other)
    {
        if(this == &other)
            return *this;

        if (size < other.size)
        {
            size = other.size *2;
            changeSize();
        }
        for (auto i = 0u; i < other.size; i++)
            array[i] = other.array[i];
        arr_size=other.arr_size;

        return *this;
    }

    Vector& operator=(Vector&& other)
    {
        if(this == &other)
            return *this;
        size=other.size;
        arr_size=other.arr_size;
        array = other.array;
        other.array=nullptr;
        other.size=0;


//        array=new Type[size];
//        for(size_t i=0; i<other.arr_size; i++)
//        {
//            array[i]=std::move(other.array[i]);
//        }
//        arr_size=other.arr_size;
//        other.arr_size=0;//?
//        other.size=0;//?
        return *this;
    }


    bool isEmpty() const
    {
        return arr_size==0;
    }

    size_type getSize() const
    {
        return arr_size;
    }

    void append(const Type& item)
    {
        arr_size++;
        if(arr_size>=size*0.5)
        {
            size=arr_size*2;
            changeSize();
        }

        array[arr_size - 1]=item;

    }

    void prepend(const Type& item)
    {
        arr_size++;
        if(arr_size>=size*0.5)
        {
            size=arr_size*2;
            changeSize();
        }
        Type *tmp_array=new Type[size];
        tmp_array[0]=item;
        for(size_type i=0; i<arr_size-1; i++)
        {
            tmp_array[i+1]=array[i];
        }
        delete [] array;
        array=tmp_array;




    }

    void insert(const const_iterator& insertPosition, const Type& item)
    {
        arr_size++;
        if(arr_size>=size)
        {
            size=arr_size*2;
            changeSize();
        }

        size_type i=0;

        const auto indexPositionIndex = insertPosition.cvector_arr-array;


        Type tmp= array[indexPositionIndex];
        Type tmp2;
        array[indexPositionIndex]=item;



        while(i+indexPositionIndex+1 != arr_size-1)
        {
            tmp2=array[i+indexPositionIndex+1];
            array[i+indexPositionIndex+1]=tmp;
            tmp=tmp2;
            ++i;
        }


    }

    Type popFirst()
    {

        if(isEmpty())
        {
            throw std::runtime_error("");
        }

        size_type n=arr_size-1;
        const Type ret_object = array[0];
        for(size_type i=0; i < n ; i++)
        {

            array[i]=array[i+1];

        }
        arr_size--;

        if(arr_size<0.25*size)
        {
            size*=0.5;
            changeSize();
        }

        return ret_object;
    }

    Type popLast()
    {

        if(isEmpty())
        {
            throw std::runtime_error("");
        }

        Type ret_val = array[arr_size-1];
        arr_size--;

        if(arr_size<0.25*size)
        {
            size*=0.5;
            changeSize();
        }

        return ret_val;

    }

    void erase(const const_iterator& possition)
    {
        if(isEmpty())
        {
            throw std::runtime_error("");
        }

        size_type i=0;
        const auto indexPositionIndex = possition.cvector_arr-array;



        while(indexPositionIndex+1+i != arr_size)
        {

            array[i+indexPositionIndex]=array[i+1+indexPositionIndex];
            ++i;
        }
        arr_size--;



    }

    void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
    {
        if(isEmpty())
        {
            throw std::runtime_error("");
        }

        if(firstIncluded==lastExcluded)
        {
            return;

        }
        const auto indexPositionIndex = firstIncluded.cvector_arr-array;
        const auto indexLast=lastExcluded.cvector_arr-array;// przekmin czy nie lastExcluded

        size_type i=0;


        while(indexLast+i != arr_size)
        {
            array[indexPositionIndex +i]=array[indexLast+i];
            i++;

        }

        arr_size-=(lastExcluded.cvector_arr-firstIncluded.cvector_arr);
    }

    void changeSize()
    {
        Type *new_array=new Type[size];
        memcpy(new_array, array, size * sizeof(Type));//void * memcpy ( void * destination, const void * source, size_t num );


        delete [] array;//?
        array = new_array;


    }

    iterator begin()
    {

        return iterator(array, this);
    }

    iterator end()
    {

        return iterator(array+arr_size, this);
    }

    const_iterator cbegin() const
    {

        return iterator(array, this);
    }

    const_iterator cend() const
    {

        return iterator(array+arr_size, this);
    }

    const_iterator begin() const
    {
        return cbegin();
    }

    const_iterator end() const
    {
        return cend();
    }

    bool operator==(const Vector& other) const
    {
        if(arr_size != other.arr_size)
        {
            return false;
        }
        unsigned int i=0;
        while( i != arr_size)
        {
            if(array[i] != other.array[i])
            {
                return false;
            }
            i++;

        }
        return true;
        // return (this->array==other.array && this->arr_size==other.arr_size && this->size==other.size);
    }
};

template <typename Type>
class Vector<Type>::ConstIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename Vector::value_type;
    using difference_type = typename Vector::difference_type;
    using pointer = typename Vector::const_pointer;
    using reference = typename Vector::const_reference;
    Type *cvector_arr;
    const Vector *vect;

    explicit ConstIterator()
    {
        cvector_arr=nullptr;
    }

    ConstIterator(Type *vv, const Vector *vvect)
    {
        cvector_arr = vv;
        vect=vvect;
    }

    reference operator*() const
    {
        if(*this == vect->end())
        {
            throw std::out_of_range("");
        }
        return *cvector_arr;
    }

    ConstIterator& operator++()
    {
        if(*this == vect->end())
        {
            throw std::out_of_range("");
        }
        cvector_arr++;
        return *this;
    }

    ConstIterator operator++(int)
    {

        ConstIterator tmp(*this);
        if(*this == vect->end())
        {
            throw std::out_of_range("");
        }
        cvector_arr++;
        return tmp;
    }

    ConstIterator& operator--()
    {

        if(*this == vect->begin())
        {
            throw std::out_of_range("");
        }
        cvector_arr--;
        return *this;
    }

    ConstIterator operator--(int)
    {

        ConstIterator tmp(*this);
        if(*this == vect->begin())
        {
            throw std::out_of_range("");
        }
        cvector_arr--;
        return tmp;
    }

    ConstIterator operator+(difference_type d) const
    {

        ConstIterator tmp(*this);
        for(auto i=0; i<d; i++)
        {
            if(*this == vect->end())
            {
                throw std::out_of_range("");
            }
            tmp++;
        }

        return tmp;
    }

    ConstIterator operator-(difference_type d) const
    {

        ConstIterator tmp(*this);
        for(auto i=0; i<d; i++)
        {
            if(*this == vect->begin())
            {
                throw std::out_of_range("");
            }
            tmp--;
        }

        return tmp;
    }
    bool operator==(const Type& other) const
    {
        return &other==this->cvector_arr;
    }

    bool operator==(const ConstIterator& other) const
    {
        return other.cvector_arr==this->cvector_arr;
    }

    bool operator!=(const ConstIterator& other) const
    {
        return other.cvector_arr!=this->cvector_arr;
    }
};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
    using pointer = typename Vector::pointer;
    using reference = typename Vector::reference;


    explicit Iterator()
    {}

    Iterator(Type *vv, const Vector *vvect) : ConstIterator(vv, vvect)
    {
    }

    Iterator(const ConstIterator& other)
        : ConstIterator(other)
    {}


    Iterator& operator++()
    {
        ConstIterator::operator++();
        return *this;
    }

    Iterator operator++(int)
    {
        auto result = *this;
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

#endif // AISDI_LINEAR_VECTOR_H
