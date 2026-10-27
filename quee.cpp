// let me first make a circluar quee and then convert that into a priority one:
#include <iostream>
using namespace std;

class circular_que
{
    // let me implement it in the array;

    int size;
    int cap;
    int rear;  // it is one before the index where the incoming will be inserted
    int front; // it is eactly the index that will be moved
    int *arr;

    void resize()
    {
        int old_cap = cap;
        cap = cap * 2;
        int *data = new int[cap];
        for (int i = 0; i < size; i++)
        {
            data[i] = arr[(front + i) % old_cap];
        }
        delete[] arr;
        arr = data;
        front = 0;
        rear = size - 1;
    }

public:
    circular_que()
    {
        size = 0;
        cap = 10;
        rear = -1;
        front = 0;
        arr = new int[cap];
    }

public:
    void enquee(int d)
    {

        if (size == cap)
        {
            resize();
        }
        if (size == 0)
        {
            rear = (rear + 1) % cap;
            arr[rear] = d;
            size++;
            return;
        }

        int coming;
        int last;
        coming = prior(d);
        int ind = rear;
        int fake_size = size;
        last = prior(arr[ind]); // this is the last element

        while(fake_size > 0 && prior(arr[ind])<coming){
            fake_size--;
            ind = (ind - 1 + cap) % cap;
        }

        int next;
        for (int i = rear; i != ind; i = (i - 1 + cap) % cap)
        {
            next = (i + 1) % cap;
            arr[next] = arr[i];
        }

        arr[(ind + 1) % cap] = d;
        rear = (rear + 1) % cap;
        size++;
    }

    void dequee()
    {
        if (size == 0)
        {
            return;
        }
        front = (front + 1) % cap;
        size--;
    }

    void display()
    {
        // to display the list:
        for (int i = 0; i < size; i++)
        {
            cout << arr[(front + i) % cap] << endl;
        }
    }

    // now let me work on the priority quee
    int prior(int d)
    {
        // i have made three levels with the highest being the number from 0-9
        if (d >= 0 && d < 10)
        {
            return 3;
        }
        if (d >= 10 && d < 100)
        {
            return 2;
        }
        if (d >= 100)
        {
            return 1;
        }
    }
};
int main()
{
    circular_que q;
    q.enquee(100); q.enquee(99); q.enquee(10); q.enquee(9); q.enquee(0);
    q.display();
    // expected: 9, 0, 99, 10, 100
}