// this is the part of the assignment dealing with the task ralted with the doubly linke list:
#include<iostream>
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
        delete head;
        delete tail;
    }

    // i have to make the swap function
    void swap(dnode<obj> * swap1, dnode<obj> * swap2){
        // i hvae to confirm that the both the values are present in the list 
        // and then also make sure that the swap1 is before is the swap2
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
                return; // this means that the swap2 is before the swap1
                
            }
        }
        if(find1 == 0 || find2 == 0){
            return;
        }

        if(swap1->next == swap2){
            // means that they are adjacent
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
        // now we have to swap
        
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

        // list is empty so new node become head and tail both
        if (head == nullptr)
        {
            head = fresh;
            tail = fresh;
            return;
        }
        // otherwise just attach it after the current tail
        tail->next = fresh;
        fresh->prev = tail;
        tail = fresh;
    }

    // now i have to make a function to switch the firsts and the last:
    void mix(){
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
        }while(cur_n!=cur_p && cur_n->next != cur_p);
    }

    void mix_2(){
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
        }while(cur_n!=cur_p && cur_n->next != cur_p);
    }



    void display(){
        for(dnode<obj> * cur = head; cur!=nullptr ; cur=cur->next){
            cout<<cur->data<<endl;
        }
    }
};



int main(){
    dList<int> logs;
    logs.insert_end(10);
    logs.insert_end(20);
    logs.insert_end(30);
    logs.insert_end(70);
    logs.insert_end(90);
    logs.insert_end(100);
    logs.insert_end(40);
    logs.insert_end(50);
    logs.insert_end(60);
    logs.insert_end(80);

    logs.mix_2();
    logs.display();
}