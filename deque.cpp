#include <iostream>

using namespace std;

class dequee
{
    int cap;
    int size;
    int front;
    int rear;
    int *arr;

    void resize()
    {
        int old_cap = cap;
        cap = cap * 2;
        int *data = new int[cap];
        for (int i = 0; i < old_cap; i++)
        {
            data[i] = arr[(front + i) % old_cap];
        }
        delete arr;
        arr = data;
        front = 0;
        rear = size - 1;
    }

public:
    dequee()
    {
        cap = 10;
        size = 0;
        front = 0;
        rear = -1;
        arr = new int[cap];
    }

    void insert_end(int d)
    {
        if (size == cap)
        {
            resize();
        }
        rear = (rear + 1) % cap;
        arr[rear] = d;
        size++;
    }

    void insert_front(int d)
    {
        if (size == cap)
        {
            resize();
        }
        front = (front - 1 + cap) % cap;
        arr[front] = d;
        size++;
    }

    void del_front()
    {
        if (size == 0)
        {
            return;
        }
        front = (front + 1) % cap;
        size--;
    }
    void del_end()
    {
        if (size == 0)
        {
            return;
        }
        rear = (rear - 1 + cap) % cap;
        size--;
    }

    void display()
    {
        // this is not the usual function:
        for (int i = 0; i < size; i++)
        {
            cout << arr[(front + i) % cap] << endl;
        }
    }
};

int main()
{
    dequee q;
    q.insert_end(15);
    q.insert_end(10);
    q.insert_end(20);

    q.insert_front(1);
    q.insert_front(2);
    q.insert_front(3);


    q.del_end();
    q.del_front();
    q.display();
}