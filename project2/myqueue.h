#ifndef MYQUEUE_H
#define MYQUEUE_H
#define MAX_SIZE 10000

template <class T>
class myqueue{
  private:
	// Declare necessary variables and methods
  public:
	T* arr;
	myqueue();
    	void enqueue(T);
    	T front();
	T dequeue();
    	bool empty();
        int size();
};

#endif
