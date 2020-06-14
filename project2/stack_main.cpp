#include "mystack.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
int index;
/*
template<class T> mystack<T>::mystack()
{
	arr = new T[MAX_SIZE];
	index = -1;
}

template<class T> void mystack<T>::push(T x)
{
	if(index <= MAX_SIZE-1)
	{
		index++;
		arr[index] = x;
	}
	else
		cout << "Error: Stack Overflow";
}

template<class T> T mystack<T>::pop()
{
        if(!mystack<T>::empty())
		return arr[index--];
        else
                cout << "Error: Stack is Empty";
}

template<class T> T mystack<T>::top()
{
        if(!mystack<T>::empty())
		return arr[index];
        else
                cout << "Error: Stack Underflow";
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
*/
int main(int argc, char** argv)
{
	string t;
	cin >> t;
	string command;
	if(t.compare("int")==0)
	{
		mystack<int> s;
		int item;
		while(cin >> command)
        	{
                	if(command.compare("push")==0)
                	{
                        	cin >> item;
                        	s.push(item);
                	}
                	else if(command.compare("pop")==0 && !s.empty())
				cout << s.pop() << endl;
                	else if(command.compare("top")==0 && !s.empty())
                        	cout << s.top() << endl;
                	else if(command.compare("size")==0)
                        	cout << s.size() << endl;
                	else if(command.compare("empty")==0)
                        	cout << s.empty() << endl;
        	}
	}
	else if(t.compare("double")==0)
	{
		mystack<double> s;
		double item;
		while(cin >> command)
        	{
                	if(command.compare("push")==0)
                	{
                        	cin >> item;
                        	s.push(item);
                	}
                	else if(command.compare("pop")==0)
                        	cout << s.pop() << endl;
                	else if(command.compare("top")==0)
                        	cout << s.top() << endl;
                	else if(command.compare("size")==0)
                        	cout << s.size() << endl;
               		else if(command.compare("empty")==0)
                        	cout << s.empty() << endl;
        	}
	}
	else if(t.compare("char")==0)
	{
		mystack<char> s;
		char item;
		while(cin >> command)
        	{
                	if(command.compare("push")==0)
                	{
                        	cin >> item;
                        	s.push(item);
                	}
                	else if(command.compare("pop")==0)
                        	cout << s.pop() << endl;
                	else if(command.compare("top")==0)
                        	cout << s.top() << endl;
                	else if(command.compare("size")==0)
                        	cout << s.size() << endl;
                	else if(command.compare("empty")==0)
                        	cout << s.empty() << endl;
        	}
	}
	else
	{
		mystack<string> s;
		string item;
		while(cin >> command)
        	{
                	if(command.compare("push")==0)
                	{
                        	cin >> item;
                        	s.push(item);
                	}
                	else if(command.compare("pop")==0)
                        	cout << s.pop() << endl;
                	else if(command.compare("top")==0)
                        	cout << s.top() << endl;
                	else if(command.compare("size")==0)
                        	cout << s.size() << endl;
                	else if(command.compare("empty")==0)
                        	cout << s.empty() << endl;
        	}
	}
	cout << endl;
	return 0;
}

