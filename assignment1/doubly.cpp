#include<iostream>
#include<string>   
using namespace std;

template<typename obj>
struct dnode{
    obj data;
    dnode<obj> * prev;
    dnode<obj> * next;
    dnode(dnode<obj> * p, obj d, dnode<obj> * n) : data(d), prev(p), next(n){}
};

template<typename obj>
class dList{
    dnode<obj> * head;
    dnode<obj> * tail;

    public:

    dList(){
        head = nullptr;
        tail = nullptr;
    }

    
    ~dList(){
        while(head != nullptr){
            dnode<obj> * t = head;
            head = head->next;
            delete t;
        }
        tail = nullptr;
    }

    void swap(dnode<obj> * swap1, dnode<obj> * swap2){
        int find1 = 0;
        int find2 = 0;
        int i = 0;
        if(head == nullptr || head == tail){
            return;
        }
        for(dnode<obj> * cur = head; cur!=nullptr ; cur = cur->next){
            if(cur == swap1){
                find1 = 1;
                i = 1;
            }
            if(cur == swap2){
                find2 = 1;
            }
            if(i == 0 && cur == swap2){
                return; // swap2 is before swap1
            }
        }
        if(find1 == 0 || find2 == 0){
            return;
        }

        if(swap1->next == swap2){
            // adjacent
            if(head!=swap1)swap1->prev->next = swap2;
            if(tail!=swap2)swap2->next->prev = swap1;

            if(head == swap1){
                head = swap2;
            }
            if(tail == swap2){
                tail = swap1;
            }

            dnode<obj> * tmp = swap2->next;

            swap2->next = swap1;
            swap2->prev = swap1->prev;

            swap1->next = tmp;
            swap1->prev = swap2;
        }
        else{
            if(swap1!=head)swap1->prev->next = swap2;
            swap1->next->prev = swap2;

            swap2->prev->next = swap1;
            if(swap2!=tail)swap2->next->prev = swap1;

            if(head == swap1){
                head = swap2;
            }
            if(tail == swap2){
                tail = swap1;
            }

            dnode<obj> * tmp_n = swap1->next;
            dnode<obj> * tmp_p = swap1->prev;

            swap1->next = swap2->next;
            swap1->prev = swap2->prev;

            swap2->next = tmp_n;
            swap2->prev = tmp_p;
        }
    }

    void insert_end(obj value)
    {
        dnode<obj> * fresh = new dnode<obj>(nullptr, value, nullptr);

        if (head == nullptr)
        {
            head = fresh;
            tail = fresh;
            return;
        }
        tail->next = fresh;
        fresh->prev = tail;
        tail = fresh;
    }

    
    void mix(){
        if(head == nullptr || head == tail) return;   
        dnode<obj> * cur_n = head;
        dnode<obj> * cur_p = tail;
        dnode<obj> * tmp;
        do{
            swap(cur_n, cur_p);

            tmp = cur_n;
            cur_n = cur_p;
            cur_p = tmp;

            cur_n = cur_n->next;
            cur_p = cur_p->prev;
        }while(cur_n!=cur_p && cur_p->next != cur_n);   
    }

    
    void mix_2(){
        if(head == nullptr || head == tail) return;   
        dnode<obj> * cur_n = head;
        dnode<obj> * cur_p = tail;
        dnode<obj> * tmp;
        int i = 1;
        do{
            if(i%2 == 0){
                swap(cur_n, cur_p);
                tmp = cur_n;
                cur_n = cur_p;
                cur_p = tmp;
            }
            cur_n = cur_n->next;
            cur_p = cur_p->prev;
            i++;
        }while(cur_n!=cur_p && cur_p->next != cur_n);   
    }

    void display(){
        for(dnode<obj> * cur = head; cur!=nullptr ; cur=cur->next){
            cout<<cur->data<<endl;
        }
    }
};

int main(){
    
    dList<string> desks;
    desks.insert_end("Alice");
    desks.insert_end("Bob");
    desks.insert_end("Charlie");
    desks.insert_end("Dana");
    desks.insert_end("Eva");
    desks.insert_end("Frank");

    cout << "Task 1 - before:" << endl;
    desks.display();
    desks.mix();
    cout << "Task 1 - after (Frank, Eva, Dana, Charlie, Bob, Alice):" << endl;
    desks.display();

    
    dList<int> seats;
    for(int s = 1; s <= 9; s++){
        seats.insert_end(s);
    }

    cout << "\nTask 3 - before:" << endl;
    seats.display();
    seats.mix_2();
    cout << "Task 3 - after (1 8 3 6 5 4 7 2 9):" << endl;
    seats.display();

    return 0;
}