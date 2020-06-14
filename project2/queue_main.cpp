#include<iostream>
#include "myqueue.h"
#include<string>
#include<stdio.h>

using namespace std;

int index = -1;
int first = -1;
int last = -1;
int first1 = -1;

template<class T> myqueue<T>::myqueue()
{
        arr = new T[MAX_SIZE];
}

template<class T> void myqueue<T>::enqueue(T x)
{
	if(index >= MAX_SIZE-1)
	{
		cout<<"Error: Queue is Full\n";
	}
	else
	{
		if(empty())
			first = last = 0; 
		else
			last = (last+1)%MAX_SIZE;
		arr[last] = x;
		index++;
	}
}

template<class T> T myqueue<T>::dequeue()
{
	if(empty())
	{
		cout<<"Error: Queue is Empty\n";
		return 0;
	}
	else
	{
		first1 = first;
		first = (first+1)%MAX_SIZE;
		index--;
		return arr[first1];
	}
}

template<class T> T myqueue<T>::front()
{
	if(first == -1)
	{
		cout<<"Error: cannot return from empty queue";
		return 0;
	}
	return arr[first];
}

template<class T> int myqueue<T>::size()
{
        return index + 1;
}

template<class T> bool myqueue<T>::empty()
{
        if(index == -1)
                return true;
        return false;
}

int main(int argc, char** argv)
{
        string t;
        cin >> t;
        string command;
        if(t.compare("int")==0)
        {
                myqueue<int> q;
                int item;
                while(cin >> command)
                {
                        if(command.compare("enqueue")==0)
                        {
                                cin >> item;
                                q.enqueue(item);
                        }
                        else if(command.compare("dequeue")==0)
                                cout << q.dequeue() << endl;
                        else if(command.compare("front")==0)
                                cout << q.front() << endl;
                        else if(command.compare("size")==0)
                                cout << q.size() << endl;
                        else if(command.compare("empty")==0)
                                cout << q.empty() << endl;
                }
        }
        else if(t.compare("double")==0)
        {
                myqueue<double> q;
                double item;
                while(cin >> command)
                {
			if(command.compare("enqueue")==0)
                        {
                                cin >> item;
                                q.enqueue(item);
                        }
                        else if(command.compare("dequeue")==0)
                                cout << q.dequeue() << endl;
                        else if(command.compare("front")==0)
                                cout << q.front() << endl;
                        else if(command.compare("size")==0)
                                cout << q.size() << endl;
                        else if(command.compare("empty")==0)
                                cout << q.empty() << endl;
                }
        }
        else if(t.compare("char")==0)
        {
                myqueue<char> q;
                char item;
                while(cin >> command)
                {
			if(command.compare("enqueue")==0)
                        {
                                cin >> item;
                                q.enqueue(item);
                        }
                        else if(command.compare("dequeue")==0)
                                cout << q.dequeue() << endl;
                        else if(command.compare("front")==0)
                                cout << q.front() << endl;
                        else if(command.compare("size")==0)
                                cout << q.size() << endl;
                        else if(command.compare("empty")==0)
                                cout << q.empty() << endl;
                }
        }
        else
        {
                myqueue<string> q;
                string item;
                while(cin >> command)
                {
			if(command.compare("enqueue")==0)
                        {
                                cin >> item;
                                q.enqueue(item);
                        }
                        else if(command.compare("dequeue")==0)
                                cout << q.dequeue() << endl;
                        else if(command.compare("front")==0)
                                cout << q.front() << endl;
                        else if(command.compare("size")==0)
                                cout << q.size() << endl;
                        else if(command.compare("empty")==0)
                                cout << q.empty() << endl;
                }
        }
	cout<<endl;
        return 0;
}

