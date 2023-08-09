#include <iostream>
using namespace std;
template <typename T>
class Stack
{
private:
    T *arr;       // Pointer to array
    int top;      // Index of top element
    int capacity; // Maximum size of stack

public:
    Stack(int size = 100)
    {
        capacity = size;
        top = -1;
        arr = new T[capacity];
    }

    ~Stack()
    {
        delete[] arr;
    }

    void push(T value)
    {
        if (isFull())
        {
            cout << "Stack is full, cannot push more elements." << endl;
            return;
        }
        top++;
        arr[top] = value;
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty, cannot pop any elements." << endl;
            return T();
        }
        T element = arr[top];
        top--;
        return element;
    }

    T peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty, cannot peek any elements." << endl;
            return T();
        }
        return arr[top];
    }

    bool isEmpty()
    {
        return (top == -1);
    }

    void display()
    {
        if (isEmpty())
        {
            std::cout << "Stack is empty" << std::endl;
        }
        else
        {
            std::cout << "Stack: ";
            for (int i = top; i >= 0; i--)
            {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool isFull()
    {
        return (top == capacity - 1);
    }
};
