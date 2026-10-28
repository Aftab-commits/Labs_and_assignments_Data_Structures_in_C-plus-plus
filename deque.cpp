#include <iostream>

using namespace std;

class deque
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
        delete[] arr;
        arr = data;
        front = 0;
        rear = size - 1;
    }

public:
    deque()
    {
        cap = 10;
        size = 0;
        front = 0;
        rear = -1;
        arr = new int[cap];
    }

    int prior(int d)
    {
        // we have three levels of priority:
        if (d < 10)
        {
            return 3; // highest prior
        }
        else if (d >= 10 && d < 100)
        {
            return 2;
        }
        else
        {
            return 1; // lowest
        }
    }

    void insert_end(int d)
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
        }
        else
        {
            int coming;
            int last;
            int ind = rear;

            coming = prior(d);

            last = prior(arr[ind]);

            int fake_size = size;
            if (coming > last)
            {
                while(fake_size > 0 && coming > prior(arr[ind]))
                {
                    ind = (ind - 1 + cap) % cap;
                    fake_size--;
                }
                int k = rear;
                while (k != ind)
                {
                    // we have to move the elements to the right
                    arr[(k + 1) % cap] = arr[k];
                    k = (k - 1 + cap) % cap;
                }
                arr[(ind+1)%cap] = d;
                rear = (rear + 1) % cap;
                size++;
            }
            else
            {
                rear = (rear + 1) % cap;
                arr[rear] = d;
                size++;
            }
        }
    }

    void insert_front(int d)
    {
        if (size == cap)
        {
            resize();
        }

        if (size == 0)
        {
            front = (front - 1 + cap) % cap;
            arr[front] = d;
            size++;
        }
        else{
            int coming;
            int last;
            int ind = front;
            int fake_size = size; 

            coming = prior(d);
            last = prior(arr[ind]);
            if(coming<last){
                while(fake_size>0 && coming<prior(arr[ind])){
                    ind = (ind+1)%cap;
                    fake_size--;
                }
                int k = front;
                while (k!=ind)
                {   
                    arr[(k-1+cap)%cap] = arr[k];
                    k = (k+1)%cap;
                }
                arr[(ind-1+cap)%cap] = d;
                front = (front-1+cap)%cap;
                size++;
            }
            else{
                front = (front - 1 + cap) % cap;
                arr[front] = d;
                size++;
            }
        }
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
    deque q;
    q.insert_end(15);
    q.insert_end(10);
    q.insert_end(20);

    q.insert_front(1110);
    q.insert_front(200);
    q.insert_front(100);
    q.insert_end(20);
    q.insert_end(9);
    q.insert_end(10);
    q.insert_end(15);
    q.insert_front(1);
    q.insert_front(2);

    q.del_end();
    q.del_front();
    q.display();
}