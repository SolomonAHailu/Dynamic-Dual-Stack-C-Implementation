
























#ifndef DYNAMIC_DUAL_STACK_H
#define DYNAMIC_DUAL_STACK_H
#include <iostream>
#include <algorithm>
#include <cassert>
#include "Exception.h"

template <typename Type>
class Dynamic_dual_stack
{
private:
    int initial_capacity;
    int array_capacity;
    Type *array;
    int stack_size[2];

public:
    Dynamic_dual_stack(int n = 10);
    Dynamic_dual_stack(const Dynamic_dual_stack &other);
    ~Dynamic_dual_stack();

    int capacity() const;
    bool empty(int m) const;
    int size(int m) const;
    Type top(int m) const;

    void swap(Dynamic_dual_stack &other);
    Dynamic_dual_stack &operator=(const Dynamic_dual_stack &other);
    void push(int m, const Type &obj);
    Type pop(int m);
    void clear();

    // Friends
    template <typename T>
    friend std::ostream &operator<<(std::ostream &out, const Dynamic_dual_stack<T> &stack);
};

template <typename Type>
Dynamic_dual_stack<Type>::Dynamic_dual_stack(int n) : initial_capacity(std::max(1, n)),
                                                      array_capacity(initial_capacity),
                                                      array(new Type[initial_capacity])
{
    if (n <= 0)
    {
        initial_capacity = 1;
    }
    else
    {
        initial_capacity = n;
    }
    array_capacity = initial_capacity;
    stack_size[0] = 0;
    stack_size[1] = 0;
}

template <typename Type>
Dynamic_dual_stack<Type>::Dynamic_dual_stack(const Dynamic_dual_stack<Type> &other)
    : initial_capacity(other.initial_capacity),
      array_capacity(other.array_capacity),
      array(new Type[array_capacity])
{
    stack_size[0] = other.stack_size[0];
    stack_size[1] = other.stack_size[1];

    for (int i = 0; i < array_capacity; i++)
    {
        array[i] = other.array[i];
    }
}

template <typename Type>
Dynamic_dual_stack<Type>::~Dynamic_dual_stack()
{
    delete[] array;
}

template <typename Type>
int Dynamic_dual_stack<Type>::capacity() const
{
    return array_capacity;
}

template <typename Type>
bool Dynamic_dual_stack<Type>::empty(int m) const
{
    if (m != 0 && m != 1)
    {
        throw illegal_argument();
    }
    return stack_size[m] == 0;
}

template <typename Type>
int Dynamic_dual_stack<Type>::size(int m) const
{
    if (m != 0 && m != 1)
    {
        throw illegal_argument();
    }
    return stack_size[m];
}

template <typename Type>
Type Dynamic_dual_stack<Type>::top(int m) const
{
    if (m != 0 && m != 1)
    {
        throw illegal_argument();
    }
    if (stack_size[m] == 0)
    {
        throw underflow();
    }
    if (m == 0)
    {
        return array[stack_size[0] - 1];
    }
    else
    {
        return array[array_capacity - stack_size[1]];
    }
}

template <typename Type>
void Dynamic_dual_stack<Type>::swap(Dynamic_dual_stack<Type> &other)
{
    std::swap(initial_capacity, other.initial_capacity);
    std::swap(array_capacity, other.array_capacity);
    std::swap(array, other.array);
    std::swap(stack_size[0], other.stack_size[0]);
    std::swap(stack_size[1], other.stack_size[1]);
}

template <typename Type>
Dynamic_dual_stack<Type> &Dynamic_dual_stack<Type>::operator=(const Dynamic_dual_stack<Type> &other)
{
    Dynamic_dual_stack<Type> copy(other);
    swap(copy);
    return *this;
}

template <typename Type>
void Dynamic_dual_stack<Type>::push(int m, const Type &obj)
{
    if (m != 0 && m != 1)
    {
        throw illegal_argument();
    }
    if ((stack_size[0] + stack_size[1]) == array_capacity)
    {
        int new_array_capacity = 2 * array_capacity;
        if (new_array_capacity < initial_capacity)
        {
            new_array_capacity = initial_capacity;
        }
        Type *new_array = new Type[new_array_capacity];
        for (int i = 0; i < stack_size[0]; i++)
        {
            new_array[i] = array[i];
        }
        for (int i = 0; i < stack_size[1]; i++)
        {
            new_array[new_array_capacity - 1 - i] = array[array_capacity - 1 - i];
        }
        delete[] array;
        array = new_array;
        array_capacity = new_array_capacity;
    }
    if (m == 0)
    {
        array[stack_size[0]] = obj;
        stack_size[0]++;
    }
    else
    {
        array[array_capacity - stack_size[1] - 1] = obj;
        stack_size[1]++;
    }
}

template <typename Type>
Type Dynamic_dual_stack<Type>::pop(int m)
{
    if (m != 0 && m != 1)
    {
        throw illegal_argument();
    }
    if (stack_size[m] == 0)
    {
        throw underflow();
    }
    Type object_found;
    if (m == 0)
    {
        object_found = array[stack_size[0] - 1];
        stack_size[0]--;
    }
    else
    {
        int effective_address = array_capacity - stack_size[1];
        object_found = array[effective_address];
        stack_size[1]--;
    }
    int combined_stack_size = stack_size[0] + stack_size[1];
    if (combined_stack_size <= (array_capacity / 4))
    {
        int new_array_capacity = array_capacity / 2;
        if (new_array_capacity < initial_capacity)
        {
            new_array_capacity = initial_capacity;
        }
        Type *new_array = new Type[new_array_capacity];
        for (int i = 0; i < stack_size[0]; i++)
        {
            new_array[i] = array[i];
        }
        for (int i = 0; i < stack_size[1]; i++)
        {
            new_array[new_array_capacity - 1 - i] = array[array_capacity - 1 - i];
        }
        delete[] array;
        array = new_array;
        array_capacity = new_array_capacity;
    }
    return object_found;
}

template <typename Type>
void Dynamic_dual_stack<Type>::clear()
{
    stack_size[0] = 0;
    stack_size[1] = 0;
    if (array_capacity > initial_capacity)
    {
        delete[] array;
        array = new Type[initial_capacity];
        array_capacity = initial_capacity;
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Dynamic_dual_stack<T> &stack)
{
    for (int i = 0; i < stack.array_capacity; ++i)
    {
        if (i < stack.stack_size[0])
        {
            out << stack.array[i] << " ";
        }
        else if (i >= stack.array_capacity - stack.stack_size[1])
        {
            out << stack.array[i] << " ";
        }
        else
        {
            out << "- ";
        }
    }
    return out;
}
#endif // DYNAMIC_DUAL_STACK_H
