#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

// A simple stack implementation created to hold
// entries from a text file to solve a maze. The
// stack will be implemented generically using a 
// template for re-usability.

template <typename E>
class ArrayStack
{
	//TODO:		Throw exception on empty stack (top())
	//TODO:		Throw exception on empty stack (pop())

	enum {DEF_CAPACITY = 600}; // the default maximum entries

public:
	ArrayStack(int capacity = DEF_CAPACITY); // default constructor
	int size() const; // for obtaining the size of the stack
	bool empty() const; // for determining if the stack if empty
	E top() const; // for getting top element
	void push(E e); // add element to stack
	void pop(); // remove top element of stack

private:
	E* memData; // member data;
	int capacity; // stack capacity
	int topIndex; // index of top
};


// Constructor which allocates the 
// capacity of the stack.
template <typename E>
ArrayStack<E>::ArrayStack(int capacity) : memData(new E[capacity]), capacity(capacity), topIndex(-1){};

// For retrieving the size of the stack
template <typename E>
int ArrayStack<E>::size() const
{
	return topIndex + 1;
}

// For retrieving the top element
// off the stack.
template <typename E>
E ArrayStack<E>::top() const 
{
	return memData[topIndex];
}

// For determining if the stack 
// is empty.
template <typename E>
bool ArrayStack<E>::empty() const
{
	return topIndex < 0;
}

// For pushing elements to the top
// of the stack
template <typename E>
void ArrayStack<E>::push(E e) 
{
  topIndex += 1;
	memData[topIndex] = e;
}

template <typename E>
void ArrayStack<E>::pop() 
{
	--topIndex;
}

#endif // ARRAYSTACK_H