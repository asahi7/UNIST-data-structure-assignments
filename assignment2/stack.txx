
//
// Assignment 2 CSE221 Fall 2016
//
template<class type>
Stack<type>::~Stack()
{
	delete[] array;
}

template<class type>
type& Stack<type>::Top()
{
	if(top == -1) std::cout << "No elements in the stack!" << std::endl;
    else return array[top];
}

template<class type>
void Stack<type>::Push(const type& item)
{
	if(top + 1 == capacity){
        capacity = capacity * 2;
        type* new_arr = new type[capacity];
        for(int i = 0; i <= top; i++){
            new_arr[i] = array[i];
        }
        delete[] array;
        array = new_arr;
    }
    array[++top] = item;
}

template<class type>
void Stack<type>::Pop()
{
	if(top == -1) {std::cout << "No elements in the stack!" << std::endl; return;}
    top--;
}

template<class type>
bool Stack<type>::IsEmpty() const
{
	return top == -1;
}
