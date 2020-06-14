#ifndef MYSTACK_H
#define MYSTACK_H
#define MAX_SIZE 10000

template <class T>
class mystack{
  private:
	int index;
	T *arr;
  public:
        mystack();
        void push(T x);
        T top();
        T pop();
        bool empty();
        int size();
};


template<class T> mystack<T>::mystack()
{
	arr = new T[MAX_SIZE];
	index = -1;
}

template<class T> void mystack<T>::push(T x)
{
	index++;
	arr[index] = x;
}

template<class T> T mystack<T>::pop()
{
	return arr[index--];
}

template<class T> T mystack<T>::top()
{
	return arr[index];
}

template<class T> int mystack<T>::size()
{
        return index + 1;
}

template<class T> bool mystack<T>::empty()
{
        if(index == -1)
                return true;
        return false;
}

#endif
